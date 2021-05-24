#include "WebsocketServer.h"
#include <string>
#include <iostream>
#include <json.hpp>
#include "Analyst.h"
#include "DataManager.hpp"
#include "File.h"
#include <fstream>
#include <ctime>
WebsocketServer::WebsocketServer()
{
    m_connection_list.clear();
}
WebsocketServer::~WebsocketServer()
{
    for (con_list::iterator iter = m_connection_list.begin(); iter != m_connection_list.end();)
    {
        echo_server.close(iter->second->gethdl(), websocketpp::close::status::going_away, "");
        m_connection_list.erase(iter++);
    }
    echo_server.stop_perpetual();
    m_thread->join();
}

void WebsocketServer::OnOpen(server* s, WebsocketServer* pWebSocket, websocketpp::connection_hdl hdl)
{
    server::connection_ptr con = s->get_con_from_hdl(hdl);
    const std::string strRemote = con->get_remote_endpoint();
    con_list::iterator iter = pWebSocket->m_connection_list.find(strRemote);
    if (iter == pWebSocket->m_connection_list.end())
    {
        connection_metadata_server* pmetadata = new connection_metadata_server(hdl, strRemote);
        pWebSocket->m_connection_list.insert(make_pair(strRemote, pmetadata));
    }
    else
    {
        iter->second->sethdl(hdl);
    }
    std::cerr << "Server Started." << std::endl;
}

void WebsocketServer::OnClose(server* s, WebsocketServer* pWebSocket, websocketpp::connection_hdl hdl)
{
    server::connection_ptr con = s->get_con_from_hdl(hdl);
    const std::string strRemote = con->get_remote_endpoint();
    con_list::iterator iter = pWebSocket->m_connection_list.find(strRemote);
    if (iter != pWebSocket->m_connection_list.end())
    {
        pWebSocket->m_connection_list.erase(iter);
    }
    std::cerr << "Server Closed." << std::endl;
}

void WebsocketServer::OnMessage(server* s, WebsocketServer* pWebSocket, websocketpp::connection_hdl hdl, message_ptr msg)
{
    if (msg->get_opcode() == websocketpp::frame::opcode::text)
    {
        server::connection_ptr con = s->get_con_from_hdl(hdl);
        const std::string strRemote = con->get_remote_endpoint();
        std::cerr << strRemote << std::endl;
    }
    std::cerr << "on_message called with hdl: " << hdl.lock().get() << " and message: " << msg->get_payload() << std::endl;

    /*if (msg->get_payload() == "stop-listening")
    {
        s->stop_listening();
        return;
    }*/

    try
    {
        //s->send(hdl, msg->get_payload(), msg->get_opcode());//接收到的数据原路返回
        std::string message=msg->get_payload();
        
        auto decode = nlohmann::json::parse(message);//解析json
        if (decode.contains("action"))//判断存在action
        {
            if (decode.at("action") == "heartbeat") //收到心跳包
            {
                std::cerr << "Get Heartbeat Package!" << std::endl;
                return;
            }
            if (decode.at("action") == "send_review") //发送review
            {
                std::string homeworkId_str = decode.at("homework_id");
                if (sendReview(atol(homeworkId_str.c_str())))
                {
                    
                    std::string ret = "{\"action\":\"send_review\",\"homework_id\":" + to_string(decode.at("homework_id")) + "\"status\":\"success\"}";
                    s->send(hdl, ret, websocketpp::frame::opcode::text);
                    return;
                }
                else
                {
                    std::string ret = "{\"action\":\"send_review\",\"homework_id\":" + to_string(decode.at("homework_id")) + "\"status\":\"fail\"}";
                    s->send(hdl, ret, websocketpp::frame::opcode::text);
                    return;
                }
            }
            if (decode.at("action") == "send_notification")
            {
                if (decode.at("type") == "new_homework")
                {
                    long long assignmentId = std::atoll(std::string(decode.at("assignment_id")).c_str());
                    sendHomeworkNotification(assignmentId, 1);
                    return;
                }
            }
            if (decode.at("action") == "get_file")
            {
                //Init
                std::string hid = decode.at("homework_id");
                DataManager::Homework hm(std::atol(hid.c_str()));
                DataManager::Assignment as(hm.getAssignmentId());
                DataManager::Student st(hm.getStudentId());
                File file(st.getClassId(), st.getId(), as.getId());
                std::string fileName = decode.at("file_name");
                std::vector<std::string> fileContent;
                const int BUFFER_SIZE = 1024 * 1024; //1M
                std::ifstream ifs(file.getFilePath(fileName), std::ios::binary);
                ifs.seekg(0, ifs.end);
                int length = (int)ifs.tellg();
                if (ifs) {
                    ifs.seekg(0, ifs.beg);
                    std::string buffer(BUFFER_SIZE, '\0');
                    int offset = 0;
                    int readSize = std::min(BUFFER_SIZE, length - offset);
                    while (readSize > 0 && ifs.read(&buffer[0], readSize)) {
                        fileContent.push_back(buffer);
                        offset += readSize;
                        readSize = std::min(BUFFER_SIZE, length - offset);
                    }
                }
                ifs.close();
                //send Init Message
                srand((unsigned)time(0));
                std::string transferId = std::to_string(rand() % 1000000);

                std::string msgInit = "{\"action\":\"send_file\",\"transfer_id\":\"" + transferId + "\",\"homework_id\":\"" + std::to_string(hm.getId()) + "\",\"name\":\"" + fileName + "\",\"totol_part\":\"" + std::to_string(fileContent.size()) + "\",\"part_size\":\"" + std::to_string(BUFFER_SIZE) + "\",\"" + "size" + "\":\"" + std::to_string(length) + "\",\"class_id\":\"" + std::to_string(st.getClassId()) + "\",\"student_id\":\"" + std::to_string(st.getId()) + "\",\"homework_id\":\"" + std::to_string(as.getId()) + "\",\"status\":\"start\"}";
                //std::string msgInit = "{\"action\":\"send_file\",\"transfer_id\":\"" + transferId + "\",\"homework_id\":\"" + std::to_string(hm.getId()) + "\",\"file_name\":\"" + fileName + "\",\"status\":\"start\"}";
                s->send(hdl, msgInit, websocketpp::frame::opcode::text);
                Sleep(100);
                //s->send(hdl, "12345", websocketpp::frame::opcode::text);
                //send file
                std::string msgFile;
                for (int i = 0; i != fileContent.size(); i++)
                {
                    msgFile = "{\"action\":\"send_file\",\"transer_id\":\"" + transferId + "\",\"part\":\"" + std::to_string(i) + "\",\"content\":\"" + fileContent[i] + "\"}";
                    s->send(hdl, fileContent[i], websocketpp::frame::opcode::binary);
                    //Sleep(50);
                }
                msgInit = "{\"action\":\"send_file\",\"status\":\"finish\"}";
                s->send(hdl, msgInit, websocketpp::frame::opcode::text);
            }
        }

    }
    catch (const websocketpp::lib::error_code& e)
    {
        std::cout << "Echo failed because: " << e << "(" << e.message() << ")" << std::endl;
    }
}

void WebsocketServer::start(int port)
{
    try
    {
        // Set logging settings
        echo_server.set_access_channels(websocketpp::log::alevel::all);
        echo_server.clear_access_channels(websocketpp::log::alevel::frame_payload);
        // Initialize Asio
        echo_server.init_asio();
        echo_server.start_perpetual();
        echo_server.set_open_handler(bind(&WebsocketServer::OnOpen, &echo_server, this, ::_1));
        echo_server.set_close_handler(bind(&WebsocketServer::OnClose, &echo_server, this, ::_1));
        echo_server.set_message_handler(bind(&WebsocketServer::OnMessage, &echo_server, this, ::_1, ::_2));

        // Listen on port 9002
        echo_server.listen(port);
        // Start the server accept loop
        echo_server.start_accept();
        // Start the ASIO io_service run loop
        //echo_server.run();
        m_thread = websocketpp::lib::make_shared<websocketpp::lib::thread>(&server::run, &echo_server);
    }
    catch (websocketpp::exception const& e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "other exception" << std::endl;
    }
}
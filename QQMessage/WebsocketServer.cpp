#include "WebsocketServer.h"
#include <websocketpp/impl/connection_impl.hpp>
#include <websocketpp/config/core.hpp>
#include <websocketpp/connection.hpp>
#include <websocketpp/endpoint.hpp>
#include <websocketpp/close.hpp>
#include <websocketpp/uri.hpp>
#include <map>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iostream>


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

void WebsocketServer::on_open(server* s, WebsocketServer* pWebSocket, websocketpp::connection_hdl hdl)
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
}

void WebsocketServer::on_close(server* s, WebsocketServer* pWebSocket, websocketpp::connection_hdl hdl)
{
    server::connection_ptr con = s->get_con_from_hdl(hdl);
    const std::string strRemote = con->get_remote_endpoint();
    con_list::iterator iter = pWebSocket->m_connection_list.find(strRemote);
    if (iter != pWebSocket->m_connection_list.end())
    {
        pWebSocket->m_connection_list.erase(iter);
    }
}

void WebsocketServer::on_message(server* s, WebsocketServer* pWebSocket, websocketpp::connection_hdl hdl, message_ptr msg)
{
    if (msg->get_opcode() == websocketpp::frame::opcode::text)
    {
        server::connection_ptr con = s->get_con_from_hdl(hdl);
        const std::string strRemote = con->get_remote_endpoint();
        std::cout << strRemote << std::endl;
    }
    std::cout << "on_message called with hdl: " << hdl.lock().get() << " and message: " << msg->get_payload() << std::endl;

    if (msg->get_payload() == "stop-listening")
    {
        s->stop_listening();
        return;
    }

    try
    {
        //s->send(hdl, msg->get_payload(), msg->get_opcode());//接收到的数据原路返回
        //TODO: 回应消息
        std::string s = msg->get_payload();
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
        echo_server.set_open_handler(bind(&on_open, &echo_server, this, ::_1));
        echo_server.set_close_handler(bind(&on_close, &echo_server, this, ::_1));
        echo_server.set_message_handler(bind(&on_message, &echo_server, this, ::_1, ::_2));

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
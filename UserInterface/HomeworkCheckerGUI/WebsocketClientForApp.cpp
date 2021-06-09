#include "WebsocketClientForApp.h"
#include <fstream>
#include <json.hpp>
#include <thread>

#ifdef _WIN32
#include <windows.h>
using namespace std;
string WebsocketClientForApp::GbkToUtf8(const char* src_str)
{
	int len = MultiByteToWideChar(CP_ACP, 0, src_str, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, src_str, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	string strTemp = str;
	if (wstr) delete[] wstr;
	if (str) delete[] str;
	return strTemp;
}

string WebsocketClientForApp::Utf8ToGbk(const char* src_str)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, src_str, -1, NULL, 0);
	wchar_t* wszGBK = new wchar_t[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, src_str, -1, wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char* szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
	string strTemp(szGBK);
	if (wszGBK) delete[] wszGBK;
	if (szGBK) delete[] szGBK;
	return strTemp;
}
#endif

bool completeFileTransfer = false;//捕获是否下载完成

WebsocketClientForApp::WebsocketClientForApp()
{
	enableSendHeartbeat = false;
	m_WebsocketClient.clear_access_channels(websocketpp::log::alevel::all);  // 开启全部接入日志级别
	m_WebsocketClient.clear_error_channels(websocketpp::log::elevel::all);   // 开启全部错误日志级别

	m_WebsocketClient.init_asio();       // 初始化asio
	m_WebsocketClient.start_perpetual(); // 避免请求为空时退出，实际上，也是避免asio退出

	// 独立运行client::run()的线程，主要是避免阻塞
	m_Thread = websocketpp::lib::make_shared<websocketpp::lib::thread>(&client::run, &m_WebsocketClient);

	m_OnOpenFunc = nullptr;
	m_OnFailFunc = nullptr;
	m_OnCloseFunc = nullptr;
	m_MessageFunc = nullptr;
}

WebsocketClientForApp::~WebsocketClientForApp()
{
	m_WebsocketClient.stop_perpetual();
	enableSendHeartbeat = false;
	if (m_ConnectionMetadataPtr != nullptr && m_ConnectionMetadataPtr->get_status() == "Open")
	{
		websocketpp::lib::error_code ec;
		m_WebsocketClient.close(m_ConnectionMetadataPtr->get_hdl(), websocketpp::close::status::going_away, "", ec); // 关闭连接

		if (ec) {
			std::cout << "> Error initiating close: " << ec.message() << std::endl;
		}
	}

	//m_SendHeartbeat.join();
	m_Thread->join();
}

bool WebsocketClientForApp::Connect(std::string const& url)
{
	if (url != "") lastURL = url;
	websocketpp::lib::error_code ec;

	// 创建connect的共享指针，注意，此时创建并没有实际建立
	client::connection_ptr con = m_WebsocketClient.get_connection(lastURL, ec);

	if (ec) {
		std::cout << "> Connect initialization error: " << ec.message() << std::endl;
		return false;
	}

	// 创建连接的metadata信息，并保存
	connection_metadata_app::ptr metadata_ptr = websocketpp::lib::make_shared<connection_metadata_app>(con->get_handle(), lastURL);
	m_ConnectionMetadataPtr = metadata_ptr;

	// 注册连接打开的Handler
	//con->set_open_handler(websocketpp::lib::bind(
	//	&connection_metadata_app::on_open,
	//	metadata_ptr,
	//	&m_WebsocketClient,
	//	websocketpp::lib::placeholders::_1
	//));
	con->set_open_handler(websocketpp::lib::bind(
		&WebsocketClientForApp::OnOpen,
		this,
		&m_WebsocketClient,
		websocketpp::lib::placeholders::_1
	));

	// 注册连接失败的Handler
	//con->set_fail_handler(websocketpp::lib::bind(
	//	&connection_metadata_app::on_fail,
	//	metadata_ptr,
	//	&m_WebsocketClient,
	//	websocketpp::lib::placeholders::_1
	//));
	con->set_fail_handler(websocketpp::lib::bind(
		&WebsocketClientForApp::OnFail,
		this,
		&m_WebsocketClient,
		websocketpp::lib::placeholders::_1
	));

	// 注册连接关闭的Handler
	//con->set_close_handler(websocketpp::lib::bind(
	//	&connection_metadata_app::on_close,
	//	metadata_ptr,
	//	&m_WebsocketClient,
	//	websocketpp::lib::placeholders::_1
	//));
	con->set_close_handler(websocketpp::lib::bind(
		&WebsocketClientForApp::OnClose,
		this,
		&m_WebsocketClient,
		websocketpp::lib::placeholders::_1
	));

	// 注册连接接收消息的Handler
	//con->set_message_handler(websocketpp::lib::bind(
	//	&connection_metadata_app::on_message,
	//	metadata_ptr,
	//	websocketpp::lib::placeholders::_1,
	//	websocketpp::lib::placeholders::_2
	//));
	con->set_message_handler(websocketpp::lib::bind(
		&WebsocketClientForApp::OnMessage,
		this,
		websocketpp::lib::placeholders::_1,
		websocketpp::lib::placeholders::_2
	));

	// 进行连接
	m_WebsocketClient.connect(con);

	//std::cout << "Websocket连接成功" << std::endl;

	// 注意，不能在Websocket连接完成之后马上就发送消息，不然会出现Invalid State的错误，
	// 导致消息发送不成功，所以在连接成功之后，主线程休眠1秒
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	enableSendHeartbeat = true;
	//m_SendHeartbeat = std::thread(&WebsocketClientForApp::sendHeartbeat, this);

	return true;
}

bool WebsocketClientForApp::Close(std::string reason)
{
	websocketpp::lib::error_code ec;

	if (m_ConnectionMetadataPtr != nullptr)
	{
		int close_code = websocketpp::close::status::normal;
		// 关闭连接
		m_WebsocketClient.close(m_ConnectionMetadataPtr->get_hdl(), close_code, reason, ec);
		if (ec) {
			std::cerr << "> Error initiating close: " << ec.message() << std::endl;
			return false;
		}
		//std::cout << "关闭Websocket连接成功" << std::endl;
	}
	return true;
}

bool WebsocketClientForApp::Send(std::string message)
{
	websocketpp::lib::error_code ec;

	if (m_ConnectionMetadataPtr != nullptr)
	{
		// 连接发送数据
		m_WebsocketClient.send(m_ConnectionMetadataPtr->get_hdl(), message, websocketpp::frame::opcode::text, ec);
		if (ec)
		{
			std::cerr << "> Error sending message: " << ec.message() << std::endl;
			std::string errorMessage = ec.message();
			return false;
		}
		std::cout << u8"发送数据成功" << std::endl;
	}

	return true;
}

connection_metadata_app::ptr WebsocketClientForApp::GetConnectionMetadataPtr()
{
	return m_ConnectionMetadataPtr;
}

void WebsocketClientForApp::OnOpen(client* c, websocketpp::connection_hdl hdl)
{
	if (m_OnOpenFunc != nullptr)
	{
		m_OnOpenFunc();
	}
}

void WebsocketClientForApp::OnFail(client* c, websocketpp::connection_hdl hdl)
{
	std::cerr << "Client Connect Failed." << std::endl << "Re-connecting..." << std::endl;
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	Sleep(1000);
#else
	sleep(1);
#endif
	Connect("");
}

void WebsocketClientForApp::OnClose(client* c, websocketpp::connection_hdl hdl)
{
	std::cerr << "Client Closed." << std::endl;
}
namespace _WSCFA_
{
	long long transferId, homeworkId, totol_part, part_size, size, offset;
	std::string name;
	std::filesystem::path filePath, workPath;
	std::ofstream ofs;
}
void WebsocketClientForApp::OnMessage(websocketpp::connection_hdl, client::message_ptr msg)
{
	if (msg->get_opcode() == websocketpp::frame::opcode::text)
	{
		std::string message = msg->get_payload();
		auto decode = nlohmann::json::parse(message);

		if (decode.count("action"))
		{
			if (decode.at("action") == "send_file")
			{
				if (decode.at("status") == "start")
				{
					completeFileTransfer = false;
					_WSCFA_::offset = 0;
					_WSCFA_::transferId = std::atoll(std::string(decode.at("transfer_id")).c_str());
					_WSCFA_::homeworkId = std::atoll(std::string(decode.at("homework_id")).c_str());
					_WSCFA_::totol_part = std::atoll(std::string(decode.at("totol_part")).c_str());
					_WSCFA_::part_size = std::atoll(std::string(decode.at("part_size")).c_str());
					_WSCFA_::size = std::atoll(std::string(decode.at("size")).c_str());
					_WSCFA_::name = decode.at("name");
#ifdef _WIN32
					_WSCFA_::name = Utf8ToGbk(_WSCFA_::name.c_str());
#endif

					_WSCFA_::filePath = rootPath;
					_WSCFA_::filePath.append(std::string(decode.at("class_id"))).append(std::string(decode.at("student_id"))).append(std::string(decode.at("homework_id")));
					_WSCFA_::workPath = _WSCFA_::filePath;
					_WSCFA_::filePath.append(_WSCFA_::name);
					create_directories(_WSCFA_::workPath);
					_WSCFA_::ofs = std::ofstream(_WSCFA_::filePath, std::ios::binary);
					return;
				}
				if (decode.at("status") == "finish")
				{
					_WSCFA_::ofs.close();
					completeFileTransfer = true;
				}
			}
		}
	}
	if (msg->get_opcode() == websocketpp::frame::opcode::binary)
	{
		std::string message = msg->get_payload();
		getFilePart(message);
	}
	else
	{
		std::string message = websocketpp::utility::to_hex(msg->get_payload());
	}
}

void WebsocketClientForApp::SetOnOpenFunc(OnOpenFunc func)
{
	m_OnOpenFunc = func;
}

void WebsocketClientForApp::SetOnFailFunc(OnFailFunc func)
{
	m_OnFailFunc = func;
}

void WebsocketClientForApp::SetOnCloseFunc(OnCloseFunc func)
{
	m_OnCloseFunc = func;
}

void WebsocketClientForApp::SetMessageFunc(OnMessageFunc func)
{
	m_MessageFunc = func;
}

void WebsocketClientForApp::getFilePart(std::string msg)
{

	long long writeSize = std::min(_WSCFA_::part_size, _WSCFA_::size - _WSCFA_::offset);
	_WSCFA_::ofs.write(msg.c_str(), writeSize);
	_WSCFA_::offset += writeSize;
	writeSize = std::min(_WSCFA_::part_size, _WSCFA_::size - _WSCFA_::offset);
}

void WebsocketClientForApp::sendReview(long homeworkId)
{
	std::string msg = "{\"action\":\"send_review\",\"homework_id\":\"" + std::to_string(homeworkId) + "\"}";
	Send(msg);
}

void WebsocketClientForApp::getFile(long homeworkId, std::filesystem::path fileName)
{
	completeFileTransfer = false;
	std::string msg = "{\"action\":\"get_file\",\"homework_id\":\"" + std::to_string(homeworkId) + "\",\"file_name\":\"" + fileName.string() + "\"}";
#ifdef _WIN32
    Send(GbkToUtf8(msg.c_str()));
#else
    Send(msg.c_str());
#endif
	while (true)
	{
#ifdef _WIN32
		Sleep(1);
#else
        usleep(1000);
#endif
		if (completeFileTransfer)
		{
			std::cout << "file ok" << std::endl;
			break;
		}
	}
}

void WebsocketClientForApp::sendHeartbeat()
{
	while (true && enableSendHeartbeat)
	{
#ifdef _WIN32
        Sleep(5000);
#else
        sleep(5);
#endif
		std::string msg = "{\"action\":\"heartbeat\",\"time\":\"" + std::to_string(std::time(0)) + "\"}";
		Send(msg);
	}
}

void WebsocketClientForApp::sendNewHomeworkNotification(long assignmentId)
{
	std::string msg = "{\"action\":\"send_notification\",\"type\":\"new_homework\",\"assignment_id\":\"" + std::to_string(assignmentId) + "\"}";
	Send(msg);
}

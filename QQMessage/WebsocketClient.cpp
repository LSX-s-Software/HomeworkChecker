#include "WebsocketClient.h"

WebsocketClient::WebsocketClient()
{
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

WebsocketClient::~WebsocketClient()
{
	m_WebsocketClient.stop_perpetual();

	if (m_ConnectionMetadataPtr != nullptr && m_ConnectionMetadataPtr->get_status() == "Open")
	{
		websocketpp::lib::error_code ec;
		m_WebsocketClient.close(m_ConnectionMetadataPtr->get_hdl(), websocketpp::close::status::going_away, "", ec); // 关闭连接

		if (ec) {
			std::cout << "> Error initiating close: " << ec.message() << std::endl;
		}
	}

	m_Thread->join();
}

bool WebsocketClient::Connect(std::string const& url)
{
	websocketpp::lib::error_code ec;

	// 创建connect的共享指针，注意，此时创建并没有实际建立
	client::connection_ptr con = m_WebsocketClient.get_connection(url, ec);

	if (ec) {
		std::cout << "> Connect initialization error: " << ec.message() << std::endl;
		return false;
	}

	// 创建连接的metadata信息，并保存
	connection_metadata::ptr metadata_ptr = websocketpp::lib::make_shared<connection_metadata>(con->get_handle(), url);
	m_ConnectionMetadataPtr = metadata_ptr;

	// 注册连接打开的Handler
	//con->set_open_handler(websocketpp::lib::bind(
	//	&connection_metadata::on_open,
	//	metadata_ptr,
	//	&m_WebsocketClient,
	//	websocketpp::lib::placeholders::_1
	//));
	con->set_open_handler(websocketpp::lib::bind(
		&WebsocketClient::OnOpen,
		this,
		&m_WebsocketClient,
		websocketpp::lib::placeholders::_1
	));

	// 注册连接失败的Handler
	//con->set_fail_handler(websocketpp::lib::bind(
	//	&connection_metadata::on_fail,
	//	metadata_ptr,
	//	&m_WebsocketClient,
	//	websocketpp::lib::placeholders::_1
	//));
	con->set_fail_handler(websocketpp::lib::bind(
		&WebsocketClient::OnFail,
		this,
		&m_WebsocketClient,
		websocketpp::lib::placeholders::_1
	));

	// 注册连接关闭的Handler
	//con->set_close_handler(websocketpp::lib::bind(
	//	&connection_metadata::on_close,
	//	metadata_ptr,
	//	&m_WebsocketClient,
	//	websocketpp::lib::placeholders::_1
	//));
	con->set_close_handler(websocketpp::lib::bind(
		&WebsocketClient::OnClose,
		this,
		&m_WebsocketClient,
		websocketpp::lib::placeholders::_1
	));

	// 注册连接接收消息的Handler
	//con->set_message_handler(websocketpp::lib::bind(
	//	&connection_metadata::on_message,
	//	metadata_ptr,
	//	websocketpp::lib::placeholders::_1,
	//	websocketpp::lib::placeholders::_2
	//));
	con->set_message_handler(websocketpp::lib::bind(
		&WebsocketClient::OnMessage,
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

	return true;
}

bool WebsocketClient::Close(std::string reason)
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

bool WebsocketClient::Send(std::string message)
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
		//std::cout << "发送数据成功" << std::endl;
	}

	return true;
}

connection_metadata::ptr WebsocketClient::GetConnectionMetadataPtr()
{
	return m_ConnectionMetadataPtr;
}

void WebsocketClient::OnOpen(client* c, websocketpp::connection_hdl hdl)
{
	if (m_OnOpenFunc != nullptr)
	{
		m_OnOpenFunc();
	}
}

void WebsocketClient::OnFail(client* c, websocketpp::connection_hdl hdl)
{
	if (m_OnFailFunc != nullptr)
	{
		m_OnFailFunc();
	}
}

void WebsocketClient::OnClose(client* c, websocketpp::connection_hdl hdl)
{
	if (m_OnCloseFunc != nullptr)
	{
		m_OnCloseFunc();
	}
}

void WebsocketClient::OnMessage(websocketpp::connection_hdl, client::message_ptr msg)
{
	if (msg->get_opcode() == websocketpp::frame::opcode::text)
	{
		std::string message = msg->get_payload();
		//std::cout << "收到来自服务器的消息：" << message << std::endl;

		if (m_MessageFunc != nullptr)
		{
			m_MessageFunc(message);
		}
	}
	else
	{
		std::string message = websocketpp::utility::to_hex(msg->get_payload());
	}
}

void WebsocketClient::SetOnOpenFunc(OnOpenFunc func)
{
	m_OnOpenFunc = func;
}

void WebsocketClient::SetOnFailFunc(OnFailFunc func)
{
	m_OnFailFunc = func;
}

void WebsocketClient::SetOnCloseFunc(OnCloseFunc func)
{
	m_OnCloseFunc = func;
}

void WebsocketClient::SetMessageFunc(OnMessageFunc func)
{
	m_MessageFunc = func;
}


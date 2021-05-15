#include "WebsocketClient.h"

WebsocketClient::WebsocketClient()
{
	m_WebsocketClient.clear_access_channels(websocketpp::log::alevel::all);  // ����ȫ��������־����
	m_WebsocketClient.clear_error_channels(websocketpp::log::elevel::all);   // ����ȫ��������־����

	m_WebsocketClient.init_asio();       // ��ʼ��asio
	m_WebsocketClient.start_perpetual(); // ��������Ϊ��ʱ�˳���ʵ���ϣ�Ҳ�Ǳ���asio�˳�

	// ��������client::run()���̣߳���Ҫ�Ǳ�������
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
		m_WebsocketClient.close(m_ConnectionMetadataPtr->get_hdl(), websocketpp::close::status::going_away, "", ec); // �ر�����

		if (ec) {
			std::cout << "> Error initiating close: " << ec.message() << std::endl;
		}
	}

	m_Thread->join();
}

bool WebsocketClient::Connect(std::string const& url)
{
	websocketpp::lib::error_code ec;

	// ����connect�Ĺ���ָ�룬ע�⣬��ʱ������û��ʵ�ʽ���
	client::connection_ptr con = m_WebsocketClient.get_connection(url, ec);

	if (ec) {
		std::cout << "> Connect initialization error: " << ec.message() << std::endl;
		return false;
	}

	// �������ӵ�metadata��Ϣ��������
	connection_metadata::ptr metadata_ptr = websocketpp::lib::make_shared<connection_metadata>(con->get_handle(), url);
	m_ConnectionMetadataPtr = metadata_ptr;

	// ע�����Ӵ򿪵�Handler
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

	// ע������ʧ�ܵ�Handler
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

	// ע�����ӹرյ�Handler
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

	// ע�����ӽ�����Ϣ��Handler
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

	// ��������
	m_WebsocketClient.connect(con);

	//std::cout << "Websocket���ӳɹ�" << std::endl;

	// ע�⣬������Websocket�������֮�����Ͼͷ�����Ϣ����Ȼ�����Invalid State�Ĵ���
	// ������Ϣ���Ͳ��ɹ������������ӳɹ�֮�����߳�����1��
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	return true;
}

bool WebsocketClient::Close(std::string reason)
{
	websocketpp::lib::error_code ec;

	if (m_ConnectionMetadataPtr != nullptr)
	{
		int close_code = websocketpp::close::status::normal;
		// �ر�����
		m_WebsocketClient.close(m_ConnectionMetadataPtr->get_hdl(), close_code, reason, ec);
		if (ec) {
			std::cerr << "> Error initiating close: " << ec.message() << std::endl;
			return false;
		}
		//std::cout << "�ر�Websocket���ӳɹ�" << std::endl;
	}

	return true;
}

bool WebsocketClient::Send(std::string message)
{
	websocketpp::lib::error_code ec;

	if (m_ConnectionMetadataPtr != nullptr)
	{
		// ���ӷ�������
		m_WebsocketClient.send(m_ConnectionMetadataPtr->get_hdl(), message, websocketpp::frame::opcode::text, ec);
		if (ec)
		{
			std::cerr << "> Error sending message: " << ec.message() << std::endl;
			std::string errorMessage = ec.message();
			return false;
		}
		//std::cout << "�������ݳɹ�" << std::endl;
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
		//std::cout << "�յ����Է���������Ϣ��" << message << std::endl;

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


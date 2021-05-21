#include "WebsocketClientForApp.h"
#include <fstream>
#include <json.hpp>

extern bool completeFileTransfer;

WebsocketClientForApp::WebsocketClientForApp()
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

WebsocketClientForApp::~WebsocketClientForApp()
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

bool WebsocketClientForApp::Connect(std::string const& url)
{
	websocketpp::lib::error_code ec;

	// ����connect�Ĺ���ָ�룬ע�⣬��ʱ������û��ʵ�ʽ���
	client::connection_ptr con = m_WebsocketClient.get_connection(url, ec);

	if (ec) {
		std::cout << "> Connect initialization error: " << ec.message() << std::endl;
		return false;
	}

	// �������ӵ�metadata��Ϣ��������
	connection_metadata_app::ptr metadata_ptr = websocketpp::lib::make_shared<connection_metadata_app>(con->get_handle(), url);
	m_ConnectionMetadataPtr = metadata_ptr;

	// ע�����Ӵ򿪵�Handler
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

	// ע������ʧ�ܵ�Handler
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

	// ע�����ӹرյ�Handler
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

	// ע�����ӽ�����Ϣ��Handler
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

	// ��������
	m_WebsocketClient.connect(con);

	//std::cout << "Websocket���ӳɹ�" << std::endl;

	// ע�⣬������Websocket�������֮�����Ͼͷ�����Ϣ����Ȼ�����Invalid State�Ĵ���
	// ������Ϣ���Ͳ��ɹ������������ӳɹ�֮�����߳�����1��
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	return true;
}

bool WebsocketClientForApp::Close(std::string reason)
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

bool WebsocketClientForApp::Send(std::string message)
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
	if (m_OnFailFunc != nullptr)
	{
		m_OnFailFunc();
	}
}

void WebsocketClientForApp::OnClose(client* c, websocketpp::connection_hdl hdl)
{
	if (m_OnCloseFunc != nullptr)
	{
		m_OnCloseFunc();
	}
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
	std::string msg = "{\"action\":\"get_file\",\"homework_id\":\"" + std::to_string(homeworkId) + "\",\"file_name\":\"" + fileName.string() + "\"}";
	Send(msg);
}

#define ASIO_STANDALONE
#define _WEBSOCKETPP_CPP11_RANDOM_DEVICE_
#define _WEBSOCKETPP_CPP11_TYPE_TRAITS_
#pragma once

// ������TLS Client
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

// ����TLS Client
// #include <websocketpp/config/asio_client.hpp>
// #include <websocketpp/client.hpp>

#include <websocketpp/common/thread.hpp>
#include <websocketpp/common/memory.hpp>

#include <string>
#include <locale>
#include <codecvt>

typedef websocketpp::client<websocketpp::config::asio_client> client;

//�ַ�ת��
//static std::wstring string_to_wstring(const std::string& s)
//{
//	using default_convert = std::codecvt<wchar_t, char, std::mbstate_t>;
//	static std::wstring_convert<default_convert>conv(new default_convert("CHS"));
//	return conv.from_bytes(s);
//}
//static std::string wstring_to_string(const std::wstring& s)
//{
//	using default_convert = std::codecvt<wchar_t, char, std::mbstate_t>;
//	static std::wstring_convert<default_convert>conv(new default_convert("CHS"));
//	return conv.to_bytes(s);
//}
//static std::string ansi_to_utf8(const std::string& s)
//{
//	static std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
//	return conv.to_bytes(string_to_wstring(s));
//}
//static std::string utf8_to_ansi(const std::string& s)
//{
//	static std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
//	return wstring_to_string(conv.from_bytes(s));
//}

//�ص�����

/// <summary>
/// �������Ӻ�ִ��
/// </summary>
typedef std::function<void()> OnOpenFunc;
/// <summary>
/// ����ʧ�ܺ�ִ��
/// </summary>
typedef std::function<void()> OnFailFunc;
/// <summary>
/// ���ӹرպ�ִ��
/// </summary>
typedef std::function<void()> OnCloseFunc;
/// <summary>
/// ��ȡ��Ϣ��ִ��
/// </summary>
typedef std::function<void(const std::string& message)> OnMessageFunc;

/// <summary>
/// �������ӵ�metadata
/// </summary>
class connection_metadata {
public:
	typedef websocketpp::lib::shared_ptr<connection_metadata> ptr;

	connection_metadata(websocketpp::connection_hdl hdl, std::string url)
		: m_Hdl(hdl)
		, m_Status("Connecting")
		, m_Url(url)
		, m_Server("N/A")
	{}

	websocketpp::connection_hdl get_hdl() const
	{
		return m_Hdl;
	}

	std::string get_status() const
	{
		return m_Status;
	}
private:
	websocketpp::connection_hdl m_Hdl;  // websocketpp��ʾ���ӵı��
	std::string m_Status;               // �����Զ�״̬
	std::string m_Url;                  // ���ӵ�URI
	std::string m_Server;               // ��������Ϣ
	std::string m_Error_reason;         // ����ԭ��
};

/// <summary>
/// Ws�ͻ���
/// </summary>
class WebsocketClient
{
public:
	/// <summary>
	/// ���캯��
	/// </summary>
	WebsocketClient();
	/// <summary>
	/// ����������
	/// </summary>
	virtual~WebsocketClient();

public:
	/// <summary>
	/// ��ʼ����
	/// </summary>
	/// <param name="url">��ַ
	/// ws://ip:port
	/// </param>
	/// <returns>���ӽ��</returns>
	bool Connect(std::string const& url);
	/// <summary>
	/// �����ر�����
	/// </summary>
	/// <param name="reason">�ر�ԭ��</param>
	/// <returns>�رս��</returns>
	bool Close(std::string reason = "");
	/// <summary>
	/// ������Ϣ
	/// </summary>
	/// <param name="message">��Ϣ����</param>
	/// <returns>���ͽ��</returns>
	bool Send(std::string message);

	connection_metadata::ptr GetConnectionMetadataPtr();

	void OnOpen(client* c, websocketpp::connection_hdl hdl);
	void OnFail(client* c, websocketpp::connection_hdl hdl);
	void OnClose(client* c, websocketpp::connection_hdl hdl);
	void OnMessage(websocketpp::connection_hdl, client::message_ptr msg);


	void SetOnOpenFunc(OnOpenFunc func);
	void SetOnFailFunc(OnFailFunc func);
	void SetOnCloseFunc(OnCloseFunc func);
	void SetMessageFunc(OnMessageFunc func);
private:
	connection_metadata::ptr m_ConnectionMetadataPtr;
	client m_WebsocketClient;
	websocketpp::lib::shared_ptr<websocketpp::lib::thread> m_Thread; // �߳�

	OnOpenFunc m_OnOpenFunc;
	OnFailFunc m_OnFailFunc;
	OnCloseFunc m_OnCloseFunc;
	OnMessageFunc m_MessageFunc; 
};
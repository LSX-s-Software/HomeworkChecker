#define ASIO_STANDALONE
#define _WEBSOCKETPP_CPP11_RANDOM_DEVICE_
#define _WEBSOCKETPP_CPP11_TYPE_TRAITS_
#pragma once

// 不包含TLS Client
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

// 包含TLS Client
// #include <websocketpp/config/asio_client.hpp>
// #include <websocketpp/client.hpp>

#include <websocketpp/common/thread.hpp>
#include <websocketpp/common/memory.hpp>

#include <string>
#include <locale>
#include <codecvt>

typedef websocketpp::client<websocketpp::config::asio_client> client;

//字符转换
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

//回调函数

/// <summary>
/// 建立连接后执行
/// </summary>
typedef std::function<void()> OnOpenFunc;
/// <summary>
/// 连接失败后执行
/// </summary>
typedef std::function<void()> OnFailFunc;
/// <summary>
/// 连接关闭后执行
/// </summary>
typedef std::function<void()> OnCloseFunc;
/// <summary>
/// 获取消息后执行
/// </summary>
typedef std::function<void(const std::string& message)> OnMessageFunc;

/// <summary>
/// 保存连接的metadata
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
	websocketpp::connection_hdl m_Hdl;  // websocketpp表示连接的编号
	std::string m_Status;               // 连接自动状态
	std::string m_Url;                  // 连接的URI
	std::string m_Server;               // 服务器信息
	std::string m_Error_reason;         // 错误原因
};

/// <summary>
/// Ws客户端
/// </summary>
class WebsocketClient
{
public:
	/// <summary>
	/// 构造函数
	/// </summary>
	WebsocketClient();
	/// <summary>
	/// 虚析构函数
	/// </summary>
	virtual~WebsocketClient();

public:
	/// <summary>
	/// 开始连接
	/// </summary>
	/// <param name="url">地址
	/// ws://ip:port
	/// </param>
	/// <returns>连接结果</returns>
	bool Connect(std::string const& url);
	/// <summary>
	/// 主动关闭连接
	/// </summary>
	/// <param name="reason">关闭原因</param>
	/// <returns>关闭结果</returns>
	bool Close(std::string reason = "");
	/// <summary>
	/// 发送消息
	/// </summary>
	/// <param name="message">消息内容</param>
	/// <returns>发送结果</returns>
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
	websocketpp::lib::shared_ptr<websocketpp::lib::thread> m_Thread; // 线程

	OnOpenFunc m_OnOpenFunc;
	OnFailFunc m_OnFailFunc;
	OnCloseFunc m_OnCloseFunc;
	OnMessageFunc m_MessageFunc; 
};
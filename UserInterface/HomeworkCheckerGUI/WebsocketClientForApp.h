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
#include <filesystem>
#include <thread>

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
class connection_metadata_app {
public:
	typedef websocketpp::lib::shared_ptr<connection_metadata_app> ptr;

	connection_metadata_app(websocketpp::connection_hdl hdl, std::string url)
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
class WebsocketClientForApp
{
public:
	/// <summary>
	/// 构造函数
	/// </summary>
	WebsocketClientForApp();
	/// <summary>
	/// 析构函数
	/// </summary>
	virtual~WebsocketClientForApp();

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

	connection_metadata_app::ptr GetConnectionMetadataPtr();
	std::filesystem::path rootPath;

	void OnOpen(client* c, websocketpp::connection_hdl hdl);
	void OnFail(client* c, websocketpp::connection_hdl hdl);
	void OnClose(client* c, websocketpp::connection_hdl hdl);
	void OnMessage(websocketpp::connection_hdl, client::message_ptr msg);

	void SetOnOpenFunc(OnOpenFunc func);
	void SetOnFailFunc(OnFailFunc func);
	void SetOnCloseFunc(OnCloseFunc func);
	void SetMessageFunc(OnMessageFunc func);
	/// <summary>
	/// 向学生发送批改结果
	/// </summary>
	/// <param name="homeworkId">作业提交ID</param>
	void sendReview(long homeworkId);
	/// <summary>
	/// 获取文件
	/// </summary>
	/// <param name="homeworkId">作业提交ID</param>
	/// <param name="fileName">文件名(请确保有效)</param>
	void getFile(long homeworkId, std::filesystem::path fileName);
	/// <summary>
	/// 发送新作业提醒
	/// </summary>
	/// <param name="assignmentId">作业布置ID</param>
	void sendNewHomeworkNotification(long assignmentId);

#ifdef _WIN32
	static std::string GbkToUtf8(const char* src_str);
	static std::string Utf8ToGbk(const char* src_str);
#else
	static int GbkToUtf8(char* str_str, size_t src_len, char* dst_str, size_t dst_len);
	static int Utf8ToGbk(char* src_str, size_t src_len, char* dst_str, size_t dst_len);
#endif

private:

	bool enableSendHeartbeat;

	connection_metadata_app::ptr m_ConnectionMetadataPtr;
	client m_WebsocketClient;
	websocketpp::lib::shared_ptr<websocketpp::lib::thread> m_Thread; // 线程

	OnOpenFunc m_OnOpenFunc;
	OnFailFunc m_OnFailFunc;
	OnCloseFunc m_OnCloseFunc;
	OnMessageFunc m_MessageFunc;

	void getFilePart(std::string msg);

	std::string lastURL;

	std::thread m_SendHeartbeat;
	/// <summary>
	/// 发送心跳包
	/// </summary>
	void sendHeartbeat();
};
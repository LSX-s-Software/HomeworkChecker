#pragma once
#include "Analyst.h"
#include "WebsocketServer.h"

/// <summary>
/// 静态类
/// <para>管理QQ消息</para>
/// </summary>
class QQMessage {
public:
	/// <summary>
	/// 回调函数Open
	/// </summary>
	static void onOpen();
	/// <summary>
	/// 回调函数Close
	/// </summary>
	static void onClose();
	/// <summary>
	/// 回调函数Fail
	/// </summary>
	static void onFail();
	/// <summary>
	/// 回调函数Message
	/// </summary>
	/// <param name="message">获取的消息</param>
	static void readMessage(const std::string& message);
	/// <summary>
	/// 初始化连接
	/// </summary>
	/// <param name="url">连接ip:端口</param>
	static void _Init(std::string url = "127.0.0.1:6700");
	/// <summary>
	/// 关闭连接
	/// </summary>
	static void _Stop();
};


#pragma once
#include <string>
/// <summary>
/// 私聊消息发送
/// </summary>
class PrivateMessageSender
{
private:
	/// <summary>
	/// 发送的信息
	/// </summary>
	std::string data;
	/// <summary>
	/// 接收者qq
	/// </summary>
	long long targetId;
public:
	/// <summary>
	/// 初始化消息发送
	/// </summary>
	/// <param name="targetId">接收者qq</param>
	/// <param name="data">内容</param>
	PrivateMessageSender(long long targetId, std::string data);
	/// <summary>
	/// 设置发送的消息
	/// </summary>
	/// <param name="data">内容</param>
	void setContent(std::string data);
	/// <summary>
	/// 发送
	/// </summary>
	void send();
};
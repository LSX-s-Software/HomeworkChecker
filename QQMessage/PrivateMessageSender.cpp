#include "PrivateMessageSender.h"
#include "WebsocketClient.h"
/// <summary>
/// ws客户端 位于QQMessage
/// </summary>
extern WebsocketClient wsClient;

PrivateMessageSender::PrivateMessageSender(long long targetId, std::string data) :targetId(targetId), data(data) {}

void PrivateMessageSender::setContent(std::string data)
{
	this->data = data;
}

void PrivateMessageSender::send()
{
	std::string tmp = R"({"action": "send_private_msg", "params": { "user_id": )" + std::to_string(targetId) + R"(, "message": ")" + data + R"(" }, "echo": 0})";
	wsClient.Send(tmp);
	return;
}
#pragma once
#include <string>
class PrivateMessageSender
{
private:
	std::string data;
	long long targetId;
public:
	PrivateMessageSender(long long targetId, std::string data);

	void setContent(std::string data);

	void send();
};
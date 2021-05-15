#pragma once
#include <string>
#include "WebsocketClient.h"

enum class PeerStatus {
	IDLE,
	REGISTER,
	HOMEWORK
};

enum class RegStatus {
	START,
	CLASS,
	NUM,
	NAME,
	CONFIRM
};

struct RegInfo
{
	RegStatus status = RegStatus::START;
	std::string name;
	long long classId;
	long long schoolId;
};

class PrivateMessageSender;

bool isNum(std::string str);

void delSpaceAhead(std::u16string& x);


void AnaText(std::u16string data, long long qq_id);

void RegCommand(std::u16string data, long long qq_id);
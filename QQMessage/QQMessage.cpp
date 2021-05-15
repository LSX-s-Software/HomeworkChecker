#include <string>
#include <iostream>
#include <map>
#include <json.hpp>

#include "Exception.h"
#include "PrivateMessageGetter.h"

#include "QQMessage.h"
#include "Tools.h"

std::string connectUrl;
std::map<long long, PeerStatus> status;
std::map<long long, RegInfo> regStatus;
std::map<long long, long long> getSchoolId;

WebsocketClient wsClient;

void QQMessage::onOpen()
{
	std::cerr << "Connected." << std::endl;
	return;
}
void QQMessage::onClose()
{
	std::cerr << "Closed." << std::endl;
	return;
}
void QQMessage::onFail()
{
	std::cerr << "Failed." << std::endl;
	return;
}

void QQMessage::readMessage(const std::string& message)
{
	auto decode = nlohmann::json::parse(message);
	if (decode.contains("post_type"))
	{
		if (decode.at("post_type") == "meta_event") return; //heartbeat
		if (decode.at("post_type") == "message")
		{
			if (decode.at("message_type") == "private")
			{
				PrivateMessageGetter getter(decode);
				AnaText(Tools::to_utf16(getter.getRawData()), getter.getSenderId());
			}

		}
	}
	return;
}

void QQMessage::_Init(std::string url)
{
	connectUrl = "ws://" + url;

	wsClient.SetOnOpenFunc(onOpen);
	wsClient.SetOnCloseFunc(onClose);
	wsClient.SetOnFailFunc(onFail);
	wsClient.SetMessageFunc(readMessage);

	if (wsClient.Connect(connectUrl) == false) throw WsConnectError("Connect to " + connectUrl + " failed.");

}

void QQMessage::_Stop()
{
	wsClient.Close("close connection");
}

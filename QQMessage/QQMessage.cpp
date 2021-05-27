#include <string>
#include <iostream>
#include <map>
#include <json.hpp>

#include "Exception.h"
#include "PrivateMessageGetter.h"

#include "QQMessage.h"
#include "Tools.h"
/// <summary>
/// 连接url
/// </summary>
std::string connectUrl;
/// <summary>
/// 一级菜单状态记录【qq号，状态】
/// </summary>
std::map<long long, PeerStatus> status;
/// <summary>
/// 二级菜单 注册 状态记录【qq号，注册信息】
/// </summary>
std::map<long long, RegInfo> regStatus;
/// <summary>
/// 本地学生信息，可判断是否注册【qq号，id号】
/// </summary>
std::map<long long, StuInfo> getStuInfo;
/// <summary>
/// 本地保存作业提交详情
/// </summary>
std::map<long long, HomeworkInfo> getHomeworkInfo;
/// <summary>
/// 本地保存作业提交id，提交后销毁
/// </summary>
std::map<long long, long long>getSubmitId;
/// <summary>
/// ws客户端
/// </summary>
WebsocketClient wsClient;
WebsocketServer wsServer;

void QQMessage::onOpen()
{
	std::cerr << "Client Connected." << std::endl;
	return;
}
void QQMessage::onClose()
{
	std::cerr << "Client Closed." << std::endl << "Re-connecting..." << std::endl;
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	Sleep(15000);
#else
	sleep(15);
#endif
	wsClient.Connect("");
	return;
}
void QQMessage::onFail()
{
	std::cerr << "Client Connect Failed." << std::endl << "Re-connecting..." << std::endl;
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	Sleep(1000);
#else
	sleep(1);
#endif
	wsClient.Connect("");
	return;
}

void QQMessage::readMessage(const std::string& message)
{
	auto decode = nlohmann::json::parse(message);//解析json
	if (decode.contains("post_type"))//判断存在post_type
	{
		if (decode.at("post_type") == "meta_event") return; //收到心跳包
		if (decode.at("post_type") == "message")
		{
			if (decode.at("message_type") == "private")//收到私聊消息
			{
				PrivateMessageGetter getter(decode);//获取消息
				AnaText(Tools::to_utf16(getter.getRawData()), getter.getSenderId());//对消息文本分析
			}

		}
	}
	if (decode.contains("notice_type"))
	{
		if (decode.at("notice_type") == "offline_file")
		{
			AnaFile(decode.at("file").at("name"), decode.at("file").at("url"), decode.at("user_id"));
		}
	}
	return;
}

void QQMessage::_InitClient(std::string url)
{
	connectUrl = "ws://" + url;
	//设置回调函数
	wsClient.SetOnOpenFunc(onOpen);
	wsClient.SetOnCloseFunc(onClose);
	wsClient.SetOnFailFunc(onFail);
	wsClient.SetMessageFunc(readMessage);

	if (wsClient.Connect(connectUrl) == false) throw WsConnectError("Connect to " + connectUrl + " failed.");

}

void QQMessage::_InitServer(int port)
{
	wsServer.start(port);
}

void QQMessage::_Stop()
{
	wsClient.Close("close connection");
}

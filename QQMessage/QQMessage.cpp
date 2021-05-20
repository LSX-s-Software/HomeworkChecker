#include <string>
#include <iostream>
#include <map>
#include <json.hpp>

#include "Exception.h"
#include "PrivateMessageGetter.h"

#include "QQMessage.h"
#include "Tools.h"
/// <summary>
/// ����url
/// </summary>
std::string connectUrl;
/// <summary>
/// һ���˵�״̬��¼��qq�ţ�״̬��
/// </summary>
std::map<long long, PeerStatus> status;
/// <summary>
/// �����˵� ע�� ״̬��¼��qq�ţ�ע����Ϣ��
/// </summary>
std::map<long long, RegInfo> regStatus;
/// <summary>
/// ����ѧ����Ϣ�����ж��Ƿ�ע�᡾qq�ţ�id�š�
/// </summary>
std::map<long long, StuInfo> getStuInfo;
/// <summary>
/// ���ر�����ҵ�ύ����
/// </summary>
std::map<long long, HomeworkInfo> getHomeworkInfo;
/// <summary>
/// ���ر�����ҵ�ύid���ύ������
/// </summary>
std::map<long long, long long>getSubmitId;
/// <summary>
/// ws�ͻ���
/// </summary>
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
	auto decode = nlohmann::json::parse(message);//����json
	if (decode.contains("post_type"))//�жϴ���post_type
	{
		if (decode.at("post_type") == "meta_event") return; //�յ�������
		if (decode.at("post_type") == "message")
		{
			if (decode.at("message_type") == "private")//�յ�˽����Ϣ
			{
				PrivateMessageGetter getter(decode);//��ȡ��Ϣ
				AnaText(Tools::to_utf16(getter.getRawData()), getter.getSenderId());//����Ϣ�ı�����
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

void QQMessage::_Init(std::string url)
{
	connectUrl = "ws://" + url;
	//���ûص�����
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

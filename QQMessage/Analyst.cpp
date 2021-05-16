#include <string>
#include <iostream>
#include <map>
#include <sstream>
#include "Tools.h"
#include "PrivateMessageSender.h"
#include "Analyst.h"

extern std::string connectUrl;
extern std::map<long long, PeerStatus> status;
extern std::map<long long, RegInfo> regStatus;
extern std::map<long long, long long> getSchoolId;

extern WebsocketClient wsClient;

void RegCommand(std::u16string data, long long qq_id);
void HomCommand(std::u16string data, long long qq_id);

void AnaText(std::u16string data, long long qq_id)
{
	typedef std::pair<long long, PeerStatus> pair;
	std::u16string subCom, retInfo;

	bool registered = false;

	if (!status.count(qq_id)) status.insert(pair(qq_id, PeerStatus::IDLE));//��ӵ�ǰ״̬

	if (!getSchoolId.count(qq_id))
	{
		//TODO:Check for SId in databse
		if (1)
		{
			registered = true;
			long long sid;
			getSchoolId.insert(std::pair<long long, long long>(qq_id, sid));
		}
	}
	else registered = true;


	if (status[qq_id] == PeerStatus::REGISTER)//ע����
	{
		subCom = data;
		Tools::delSpaceAhead(subCom);
		RegCommand(subCom, qq_id);
		return;
	}

	if (status[qq_id] == PeerStatus::HOMEWORK)//�ύ��ҵ��
	{
		subCom = data;
		Tools::delSpaceAhead(subCom);
		HomCommand(subCom, qq_id);
		return;
	}

	if (data.substr(0, 2) == u"ע��")//��ʼע��
	{
		if (registered)
		{
			PrivateMessageSender sender(qq_id, u8"����ע��");
			sender.send();
			return;
		}
		subCom = Tools::delFirstCom(data, 2);
		status[qq_id] = PeerStatus::REGISTER;
		RegCommand(subCom, qq_id);
		return;
	}

	if (!registered)//δע��
	{
		PrivateMessageSender sender(qq_id, u8"δע���˺ţ�������ע���Կ�ʼ");
		sender.send();
		return;
	}

	if (status[qq_id] == PeerStatus::IDLE)
	{
		if (data.substr(0, 6) == u"��ѯ������Ϣ")//TODO:��ѯ������Ϣ ���ݿ� ���ذ༶����ʦ��������ѧ��
		{
			return;
		}

		
		if (data.substr(0, 4) == u"��ѯ��ҵ")//TODO:��ѯ��ҵ��n����״̬��0δ��� 1���ύ 2�����ġ��������������ҵ���ݣ����ģ�������
		{
			std::string homewordId_str = Tools::to_utf8(Tools::delFirstCom(data, 4));
			if (!Tools::isNum(homewordId_str))
			{
				PrivateMessageSender sender(qq_id, u8"��ҵ�б�����");//TODO: vector ���� δ��ɣ�
				{

				}
				sender.send();
				return;
			}
#include <stdlib.h>
			int homeworkID = atoi(homewordId_str.c_str());
			
			int homeworkStatus=0;
			if (homeworkStatus == -1)//����ҵ
			{
				PrivateMessageSender sender(qq_id, u8"���޸���ҵ��������");
				sender.send();
				return;
			}
			if (homeworkStatus == 0)//δ�ύ
			{
				
				return;
			}
			if (homeworkStatus == 1)//���ύ
			{

				return;
			}
			if (homeworkStatus == 2)//������
			{

				return;
			}
			return;
		}

		if (data.substr(0, 4) == u"�ύ��ҵ" || data.substr(0, 4) == u"�޸���ҵ")
		{
			std::string homewordId_str = Tools::to_utf8(Tools::delFirstCom(data, 4));
			if (!Tools::isNum(homewordId_str))
			{
				PrivateMessageSender sender(qq_id, u8"δ֪���������");
				sender.send();
				return;
			}
#include <stdlib.h>
			int homeworkID = atoi(homewordId_str.c_str());

			int homeworkStatus=0;
			if (homeworkStatus == -1)//����ҵ
			{
				PrivateMessageSender sender(qq_id, u8"���޸���ҵ��������");
				sender.send();
				return;
			}
			if (homeworkStatus == 0)//δ�ύ
			{

				return;
			}
			if (homeworkStatus == 1)//���ύ
			{

				return;
			}
			if (homeworkStatus == 2)//������
			{

				return;
			}
			return;
		}
	}


	PrivateMessageSender sender(qq_id, u8"δ֪���������");
	sender.send();
	return;
}

void RegCommand(std::u16string data, long long qq_id)
{
	typedef std::pair<long long, RegInfo> pair;
	RegInfo regInfo;
	if (!regStatus.count(qq_id))
	{
		regStatus.insert(pair(qq_id, regInfo));
	}

	regInfo = regStatus[qq_id];

	if (regInfo.status == RegStatus::START)
	{
		PrivateMessageSender sender1(qq_id, u8"��ʼע�ᣬ������γ�������");
		sender1.send();
		regInfo.status = RegStatus::CLASS;
		regStatus[qq_id] = regInfo;
		return;
	}

	if (regInfo.status == RegStatus::CLASS)
	{
		std::u16string classCode = data.substr(0, data.find_first_of(u" "));
		if (0)//TODO: Check for classId in database
		{
			PrivateMessageSender sender(qq_id, u8"δ֪�γ������룬������");
			sender.send();
			return;
		}
		long long getclassId = 123;

		std::string classInfo = u8"������Ŀγ̣�xxxxx\\r\\n�ο���ʦ��yyyyyy\\r\\n\\r\\n����������";

		PrivateMessageSender sender(qq_id, classInfo);
		sender.send();
		regInfo.status = RegStatus::NAME;
		regInfo.classId = getclassId;
		regStatus[qq_id] = regInfo;
		return;
	}

	if (regInfo.status == RegStatus::NAME)
	{
		std::u16string name = data.substr(0, data.find_first_of(u" "));
		PrivateMessageSender sender(qq_id, u8"������ѧ��");
		sender.send();
		regInfo.status = RegStatus::NUM;
		regInfo.name = Tools::to_utf8(name);
		regStatus[qq_id] = regInfo;
		return;
	}

	if (regInfo.status == RegStatus::NUM)
	{
		std::string schoolID_str = Tools::to_utf8(data.substr(0, data.find_first_of(u" ")));

		if (!Tools::isNum(schoolID_str)||schoolID_str.length()>18)
		{
			PrivateMessageSender sender(qq_id, u8"ѧ�Ÿ�ʽ����������");
			sender.send();
			return;
		}
#include <stdlib.h>
		long long schoolID = atoll(schoolID_str.c_str());

		regInfo.status = RegStatus::CONFIRM;
		regInfo.schoolId = schoolID;
		regStatus[qq_id] = regInfo;

		std::string classInfo = u8"����ע����Ϣ����\r\n������" + regInfo.name + u8"\r\nѧ�ţ�" + std::to_string(regInfo.schoolId) + u8"\r\n\r\n���롰ȷ�ϡ����ύ";
		PrivateMessageSender sender(qq_id, classInfo);
		sender.send();
		return;
	}

	if (regInfo.status == RegStatus::CONFIRM)
	{
		std::u16string command = data.substr(0, data.find_first_of(u" "));
		if (command != u"ȷ��")
		{
			PrivateMessageSender sender(qq_id, u8"��ȡ��ע��");
			sender.send();
			regStatus.erase(qq_id);
			status[qq_id] = PeerStatus::IDLE;
			return;
		}
		//TODO: Send register info

		PrivateMessageSender sender(qq_id, u8"ע��ɹ�");
		sender.send();
		regStatus.erase(qq_id);
		status[qq_id] = PeerStatus::IDLE;
		getSchoolId[qq_id] = regInfo.schoolId;
		return;
	}
}

void HomCommand(std::u16string data, long long qq_id)
{
	
}
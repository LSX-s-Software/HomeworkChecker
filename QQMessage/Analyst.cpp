#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <map>
#include <sstream>
#include <stdlib.h>
#include "Tools.h"
#include "PrivateMessageSender.h"
#include "Analyst.h"
#include <DataManager.hpp>
#include "File.h"
#include <ctime>
#include <regex>

extern std::string connectUrl;
extern std::map<long long, PeerStatus> status;
extern std::map<long long, RegInfo> regStatus;
extern std::map<long long, StuInfo> getStuInfo;
extern std::map<long long, HomeworkInfo> getHomeworkInfo;

extern WebsocketClient wsClient;

void RegCommand(std::u16string data, long long qq_id);
void HomCommand(std::u16string data, long long qq_id);
/// <summary>
/// ת����ҵ״̬
/// </summary>
/// <param name="id">״̬id</param>
/// <returns></returns>
std::string getHomeworkStatus(int id)
{
	if (id == 0) return u8"δ�ύ";
	if (id == 1) return u8"���ύ";
	if (id == 2) return u8"������";
	return u8"δ֪״̬";
}
/// <summary>
/// �ַ����ָ�
/// </summary>
/// <param name="s">ԭʼ�ַ���</param>
/// <param name="seperator">�ָ��� �ɶ��</param>
/// <returns>�ָ����ַ����б�</returns>
std::vector<std::string> split(const std::string& s, const std::string& seperator) {
	std::vector<std::string> result;
	typedef std::string::size_type string_size;
	string_size i = 0;

	while (i != s.size()) {
		//�ҵ��ַ������׸������ڷָ�������ĸ��
		int flag = 0;
		while (i != s.size() && flag == 0) {
			flag = 1;
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[i] == seperator[x]) {
					++i;
					flag = 0;
					break;
				}
		}

		//�ҵ���һ���ָ������������ָ���֮����ַ���ȡ����
		flag = 0;
		string_size j = i;
		while (j != s.size() && flag == 0) {
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[j] == seperator[x]) {
					flag = 1;
					break;
				}
			if (flag == 0)
				++j;
		}
		if (i != j) {
			result.push_back(s.substr(i, j - i));
			i = j;
		}
	}
	return result;
}

/// <summary>
/// �ַ����ָ�
/// </summary>
/// <param name="s">ԭʼ�ַ���</param>
/// <param name="seperator">�ָ��� �ɶ��</param>
/// <returns>�ָ����ַ����б�</returns>
std::vector<std::u16string> split(const std::u16string& s, const std::u16string& seperator) {
	std::vector<std::u16string> result;
	typedef std::u16string::size_type string_size;
	string_size i = 0;

	while (i != s.size()) {
		//�ҵ��ַ������׸������ڷָ�������ĸ��
		int flag = 0;
		while (i != s.size() && flag == 0) {
			flag = 1;
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[i] == seperator[x]) {
					++i;
					flag = 0;
					break;
				}
		}

		//�ҵ���һ���ָ������������ָ���֮����ַ���ȡ����
		flag = 0;
		string_size j = i;
		while (j != s.size() && flag == 0) {
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[j] == seperator[x]) {
					flag = 1;
					break;
				}
			if (flag == 0)
				++j;
		}
		if (i != j) {
			result.push_back(s.substr(i, j - i));
			i = j;
		}
	}
	return result;
}

/// <summary>
/// ��ȡ�ļ����б�
/// </summary>
/// <param name="raw">����url | �ָ�</param>
/// <returns>�����ļ��� �ո�ָ�</returns>
std::string getHomeworkFilename(std::string raw)
{
	std::vector<std::u16string> rawList = split(Tools::to_utf16(raw), u"|");
	std::string result;
	for (auto& iter : rawList)
	{
		std::filesystem::path file = iter;
		result += (file.filename().string()+"  ");
	}
	return result;
}

/// <summary>
/// TimeStampת��Ϊ����ʱ��
/// </summary>
/// <param name="timeStamp"></param>
/// <returns>����ʱ���ַ���</returns>
std::string TimeConvert(std::string timeStamp)
{
	std::stringstream ss;
	time_t timeTemp;
	ss << timeStamp;
	ss >> timeTemp;
	char temp[50];
	struct tm* timeSet = gmtime(&timeTemp);
	strftime(temp, 50, "%Y-%m-%d %H:%M:%S", timeSet);
	return temp;
}
std::string TimeConvert(long timeStamp)
{
	std::stringstream ss;
	time_t timeTemp;
	ss << timeStamp;
	ss >> timeTemp;
	char temp[50];
	struct tm* timeSet = gmtime(&timeTemp);
	strftime(temp, 50, "%Y-%m-%d %H:%M:%S", timeSet);
	return temp;
}

DataManager::CompleteHomeworkList getCH(long long qq_id,long long assignmentId)
{
	std::vector<DataManager::CompleteHomeworkList> homeworklist = DataManager::getHomeworkListByStuId(getStuInfo[qq_id].studentId, getStuInfo[qq_id].classId);
	DataManager::CompleteHomeworkList ch;
	for (auto& iter : homeworklist)//���ҵ�ǰ��ҵid
	{
		if (iter.assignment.getId() == assignmentId)
		{
			ch = iter;
			return ch;
		}
	}
	throw DataManager::DMException::TARGET_NOT_FOUND();
}

void AnaText(std::u16string data, long long qq_id)
{
	typedef std::pair<long long, PeerStatus> pair;
	std::u16string subCom, retInfo;

	//��ӵ�ǰ״̬
	if (!status.count(qq_id)) status.insert(pair(qq_id, PeerStatus::IDLE));
	//���ػ�ѧ������
	if ((status[qq_id] != PeerStatus::REGISTER)&&!getStuInfo.count(qq_id) && (status[qq_id] != PeerStatus::UNREG)) 
	{
		try
		{
			DataManager::Student st(std::to_string(qq_id));
			StuInfo stuinfo;
			stuinfo.studentId = st.getId();
			stuinfo.studentNum = atoll(st.getSchoolNum().c_str());
			stuinfo.classId = st.getClassId();
			getStuInfo.insert(std::pair<long long, StuInfo>(qq_id, stuinfo));
		}
		catch (DataManager::DMException::TARGET_NOT_FOUND)
		{
			status[qq_id] = PeerStatus::UNREG;
		}
	}

	//ע����
	if (status[qq_id] == PeerStatus::REGISTER)
	{
		subCom = data;
		Tools::delSpaceAhead(subCom);
		RegCommand(subCom, qq_id);
		return;
	}

	//�ύ��ҵ��
	if (status[qq_id] == PeerStatus::HOMEWORK)
	{
		subCom = data;
		Tools::delSpaceAhead(subCom);
		HomCommand(subCom, qq_id);
		return;
	}

	//��ʼע��
	if (data.substr(0, 2) == u"ע��")
	{
		if (status[qq_id] == PeerStatus::UNREG)
			status[qq_id] = PeerStatus::REGISTER;
		if (getStuInfo.count(qq_id))
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

	//δע��
	if (status[qq_id] == PeerStatus::UNREG)//δע��
	{
		PrivateMessageSender sender(qq_id, u8"δע���˺ţ������롰ע�ᡱ�Կ�ʼ");
		sender.send();
		return;
	}

	//����״̬
	if (status[qq_id] == PeerStatus::IDLE)
	{
		//��ѯ������Ϣ
		if (data.substr(0, 6) == u"��ѯ������Ϣ"|| data.substr(0, 6) == u"��ȡ������Ϣ")
		{
			DataManager::Student st((int)getStuInfo[qq_id].studentId);
			DataManager::Class cl(st.getClassId());
			std::string send = u8"���ĸ�����Ϣ����\n\r������" + st.getName() + u8"\nѧ�ţ�" + st.getSchoolNum() + u8"\n�༶��" + cl.getName() + u8"\n��ʦ��"; //TODO: teacher's name
			PrivateMessageSender sender(qq_id, send);
			sender.send();
			return;
		}

		//��ѯ��ҵ���б�
		if (data.substr(0, 4) == u"��ѯ��ҵ"|| data.substr(0, 4) == u"��ȡ��ҵ")
		{
			std::string assignmentId_str = Tools::to_utf8(Tools::delFirstCom(data, 4));
			if (!Tools::isNum(assignmentId_str))//δ��⵽����
			{
				std::string message;
					std::vector<DataManager::CompleteHomeworkList> homeworklist = DataManager::getHomeworkListByStuId(getStuInfo[qq_id].studentId, getStuInfo[qq_id].classId);
					if (homeworklist.size() != 0)
					{
						for (auto& iter : homeworklist)
						{
							int status = iter.homework.getStatus();
							message += (u8"����ҵ " + std::to_string(iter.assignment.getId()) + u8"��  " + getHomeworkStatus(status) + u8"  ");
							if (status == 0)//δ�ύ
							{
								message += (u8"��ֹʱ�䣺" + TimeConvert(iter.assignment.getDeadline()));
							}
							if (status == 2)//������
							{
								message += u8"������" + std::to_string(iter.homework.getScore());
							}
							message += "\r\n";
						}
					}
					else
						message = u8"������ҵ";
				PrivateMessageSender sender(qq_id, u8"��ҵ�б�����\r\n" + message);
				sender.send();
				return;
			}
			//���������ѯ
			int assignmentId = atoi(assignmentId_str.c_str());
			std::string message;
			try
			{
				
				DataManager::CompleteHomeworkList ch = getCH(qq_id, assignmentId);
				
				int homeworkStatus = ch.homework.getStatus();
				if (homeworkStatus == 0)//δ�ύ
				{
					message += (u8"����ҵ " + std::to_string(ch.assignment.getId()) + u8"��  " + getHomeworkStatus(homeworkStatus))+ u8"\r\n";
					message += (u8"����ҵ���ݡ�\r\n" + ch.assignment.getDescription() + u8"\r\n");
					message += (u8"����ֹʱ�䡿  " + TimeConvert(ch.assignment.getDeadline()) + u8"\r\n");
					PrivateMessageSender sender(qq_id, message);
					sender.send();
					return;
				}
				if (homeworkStatus == 1)//���ύ
				{
					message += (u8"����ҵ " + std::to_string(ch.assignment.getId()) + u8"��  " + getHomeworkStatus(homeworkStatus)) + u8"\n\n";
					message += (u8"����ҵ���ݡ�\r\n" + ch.assignment.getDescription() + u8"\r\n");
					message += (u8"������ʱ�䡿  " + TimeConvert(ch.assignment.getDeadline()) + u8"\n\n");
					message += (u8"����ҵ�����б�\r\n" + getHomeworkFilename(ch.homework.getContentURL())+u8"\r\n");
					message += (u8"����ҵ�����б�\r\n" + getHomeworkFilename(ch.homework.getAttachmentURL()) + u8"\r\n");
					PrivateMessageSender sender(qq_id, message);
					sender.send();
					return;
				}
				if (homeworkStatus == 2)//������
				{
					message += (u8"����ҵ " + std::to_string(ch.assignment.getId()) + u8"��  " + getHomeworkStatus(homeworkStatus)) + u8"\n\n";
					message += (u8"����ҵ���ݡ�\r\n" + ch.assignment.getDescription() + u8"\r\n");
					message += (u8"������ʱ�䡿  " + TimeConvert(ch.assignment.getDeadline()) + u8"\n\n");
					message += (u8"�������� " + std::to_string(ch.homework.getScore()) + u8"\r\n");
					message += (u8"�����\r\n" + ch.homework.getComments() + u8"\n\n");
					message += (u8"����ҵ�����б�\r\n" + getHomeworkFilename(ch.homework.getContentURL()) + u8"\r\n");
					message += (u8"����ҵ�����б�\r\n" + getHomeworkFilename(ch.homework.getAttachmentURL()) + u8"\r\n");
					PrivateMessageSender sender(qq_id, message);
					sender.send();
					return;
				}
			}
			catch(DataManager::DMException::TARGET_NOT_FOUND)//����ҵ
			{
				PrivateMessageSender sender(qq_id, u8"���޸���ҵ��������");
				sender.send();
				return;
			}
			catch (std::exception)
			{
				PrivateMessageSender sender(qq_id, u8"δ֪����������");
				sender.send();
				return;
			}
			return;
		}

		//�ύ��ҵ
		if (data.substr(0, 4) == u"�ύ��ҵ")
		{
			std::string assignmentId_str = Tools::to_utf8(Tools::delFirstCom(data, 4));
			if (!Tools::isNum(assignmentId_str)|| assignmentId_str=="")
			{
				PrivateMessageSender sender(qq_id, u8"δ֪���������");
				sender.send();
				return;
			}
			int assignmentId = atoi(assignmentId_str.c_str());
			try
			{
				try
				{
					DataManager::CompleteHomeworkList ch = getCH(qq_id, assignmentId);

					status[qq_id] = PeerStatus::HOMEWORK;
					DataManager::Student st(getStuInfo[qq_id].studentId);
					if (std::time(0) > ch.assignment.getDeadline())
					{
						PrivateMessageSender sender(qq_id, u8"��ҵ�ύ�ѽ�ֹ");
						sender.send();
						status[qq_id] = PeerStatus::IDLE;
						return;
					}
					PrivateMessageSender sender(qq_id, u8"���½���ҵ");
					sender.send();

					HomeworkInfo info;
					info.classId = st.getClassId();
					info.homeworkId = assignmentId;
					info.studentId = getStuInfo[qq_id].studentId;
					info.studentNum = atoll(st.getSchoolNum().c_str());
					getHomeworkInfo.insert(std::pair<long long, HomeworkInfo>(qq_id, info));
					PrivateMessageSender sender2(qq_id, u8"��ʼ�ύ��ҵ" + std::to_string(info.homeworkId) + u8"\r\n���������롰ȷ���ύ�����ύ�����롰ȡ���ύ����ȡ��");
					sender2.send();
					
					File file(info);
					std::string filelist=file.getFileList();
					if (filelist != u8"�����ļ�")
					{
						PrivateMessageSender sender(qq_id, u8"�Ѽ�⵽�ݸ�\n"+filelist);
						sender.send();
					}

					return;
				}
				catch (DataManager::DMException::TARGET_EXISTED)
				{
					PrivateMessageSender sender(qq_id, u8"������ҵ�Ѵ���");
					sender.send();
					return;
				}

			}
			catch (DataManager::DMException::TARGET_NOT_FOUND)
			{
				status[qq_id] = PeerStatus::IDLE;
				PrivateMessageSender sender(qq_id, u8"���޸���ҵ��������");
				sender.send();
				return;
			}
		}

		//TODO: �޸���ҵ
	}

	//TODO: ����
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

	if (data.substr(0,4) == u"ȡ��ע��")
	{
		PrivateMessageSender sender(qq_id, u8"��ȡ��ע��");
		sender.send();
		regStatus.erase(qq_id);
		status[qq_id] = PeerStatus::IDLE;
		return;
	}
	//TODO: ����
	if (regInfo.status == RegStatus::START)
	{
		PrivateMessageSender sender1(qq_id, u8"��ʼע�ᣬ���롰ȡ��ע�ᡱ�����˳�ע��\n\n������γ�������");
		sender1.send();
		regInfo.status = RegStatus::CLASS;
		regStatus[qq_id] = regInfo;
		return;
	}

	if (regInfo.status == RegStatus::CLASS)
	{
		std::u16string classCode = data.substr(0, data.find_first_of(u" "));
		try
		{
			//DataManager::Class cl(Tools::to_utf8(classCode)); //TODO: ������
			DataManager::Class cl(1);
			std::string classInfo = u8"���������룺"+cl.getName()+u8"\n\n����������";

			PrivateMessageSender sender(qq_id, classInfo);
			sender.send();
			regInfo.status = RegStatus::NAME;
			regInfo.classId = cl.getId();
			regStatus[qq_id] = regInfo;
			return;
		}
		
		catch(DataManager::DMError)
		{
			PrivateMessageSender sender(qq_id, u8"δ֪�γ������룬������");
			sender.send();
			return;
		}
		
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
		
		try
		{
			DataManager::Student st(std::to_string(regInfo.schoolId), std::to_string(qq_id), regInfo.name);
		}
		catch(DataManager::DMError)
		{
			PrivateMessageSender sender(qq_id, u8"ע��ʧ�ܣ�������");
			sender.send();
			regStatus.erase(qq_id);
			status[qq_id] = PeerStatus::UNREG;
		}
		PrivateMessageSender sender(qq_id, u8"ע��ɹ�");
		sender.send();
		regStatus.erase(qq_id);
		status[qq_id] = PeerStatus::IDLE;
		return;
	}
}

void HomCommand(std::u16string data, long long qq_id)
{
	//TODO: ����
	if (data == u"ȡ��"|| data == u"ȡ���ύ")
	{
		PrivateMessageSender sender(qq_id, u8"����ȡ���ύ��ҵ" + std::to_string(getHomeworkInfo[qq_id].homeworkId)+u8"\n��ǰ�ݸ��ѱ���");
		sender.send();
		status[qq_id] = PeerStatus::IDLE;
		getHomeworkInfo.erase(qq_id);
		return;
	}
	if (data.substr(0, 4) == u"ɾ���ļ�")
	{
		std::u16string tmp = Tools::delFirstCom(data, 2);
		std::vector<std::u16string> delList = split(tmp, u"|");
		for (auto& iter : delList)
		{
			File file(getHomeworkInfo.at(qq_id));
			PrivateMessageSender sender(qq_id, file.delFile(iter));
			sender.send();
		}
		return;
	}
	if (data.substr(0, 2) == u"ɾ��")
	{
		std::u16string tmp = Tools::delFirstCom(data, 2);
		std::vector<std::u16string> delList = split(tmp, u"|");
		for (auto& iter : delList)
		{
			File file(getHomeworkInfo.at(qq_id));
			PrivateMessageSender sender(qq_id, file.delFile(iter));
			sender.send();
		}
		return;
	}
	if (data == u"ȫ��ɾ��"|| data == u"����ļ�")
	{
		File file(getHomeworkInfo.at(qq_id));
		file.delAll();
		PrivateMessageSender sender(qq_id, u8"�ļ������");
		sender.send();
		return;
	}
	if (data == u"��ȡ�ļ��б�"|| data == u"��ѯ�ļ��б�")
	{
		File file(getHomeworkInfo[qq_id]);
		PrivateMessageSender sender(qq_id, file.getFileList());
		sender.send();
		return;
	}
	if (data.substr(0, 2) == u"��ȡ" || data.substr(0, 4) == u"��ѯ")
	{
		std::u16string tmp = Tools::delFirstCom(data, 2);
		File file(getHomeworkInfo[qq_id]);
		PrivateMessageSender sender(qq_id, file.getFile(tmp));
		sender.send();
		return;
	}
	if (data.substr(0, 4) == u"��ȡ�ļ�" || data.substr(0, 4) == u"��ѯ�ļ�")
	{
		std::u16string tmp = Tools::delFirstCom(data, 4);
		File file(getHomeworkInfo[qq_id]);
		PrivateMessageSender sender(qq_id, file.getFile(tmp));
		sender.send();
		return;
	}
	
	if (data == u"�ύ��ҵ"|| data == u"ȷ���ύ"|| data == u"�ύ")
	{
		File file(getHomeworkInfo[qq_id]);
		DataManager::Homework hm(getStuInfo[qq_id].studentId, getHomeworkInfo[qq_id].homeworkId);
		if (file.save(hm.getId()))//�ϴ��ɹ�
		{
			hm.submit(file.getContentFile(), file.getAttachmentFile());
			status[qq_id] = PeerStatus::IDLE;
			PrivateMessageSender sender(qq_id, u8"�ύ�ɹ�");
			sender.send();
			return;
		}
		else
		{
			DataManager::deleteHomework(hm.getId());
			PrivateMessageSender sender(qq_id, u8"�ύʧ��");
			sender.send();
			return;
		}
	}

	try
	{
		std::regex findURL("url=(.*?)\\]");
		std::regex findCQ("\\[(.*?)\\]");
		std::sregex_token_iterator endURL;
		std::sregex_token_iterator endCQ;
		std::string msg = Tools::to_utf8(data);
		std::string tmp = msg;
		for (std::sregex_token_iterator posURL(tmp.cbegin(), tmp.cend(), findURL, 1), posCQ(tmp.cbegin(), tmp.cend(), findCQ, 1); posURL != endURL; ++posURL, ++posCQ)
		{
			File fl(getHomeworkInfo[qq_id]);
			std::string fileName = fl.storePic(posURL->str());
			msg.replace(msg.find(posCQ->str()), posCQ->str().length(), fileName);
			PrivateMessageSender sender(qq_id, u8"ͼƬ��" + fileName + u8" �ѱ���");
			sender.send();
		}

		File file(getHomeworkInfo[qq_id]);
		std::string fileName = file.storeText(msg);
		PrivateMessageSender sender(qq_id, u8"�ı���" + fileName + u8" �ѱ���");
		sender.send();
		return;
	}
	catch (...)
	{
		PrivateMessageSender sender(qq_id, u8"����ʧ�ܣ�������");
		sender.send();
		return;
	}
}

void AnaFile(std::string name, std::string url, long long qq_id)
{
	if (status[qq_id] == PeerStatus::HOMEWORK)
	{
		File fl(getHomeworkInfo[qq_id]);
		std::string filename = fl.downFile(url, name);
		if (filename != "")
		{
			PrivateMessageSender sender(qq_id, u8"�ļ���" + filename + u8" �ѽ���");
			sender.send();
			return;
		}
		else
		{
			PrivateMessageSender sender(qq_id, u8"�ļ�����ʧ�ܣ�������");
			sender.send();
			return;
		}
	}
	else
	{
		PrivateMessageSender sender(qq_id, u8"����ҵģʽ�²������ύ�ļ�");
		sender.send();
		return;
	}
}
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

std::string getHomeworkFilename(std::string raw)
{
	std::vector<std::u16string> rawList = split(Tools::to_utf16(raw), u"|");
	std::string result;
	for (auto& iter : rawList)
	{
		std::filesystem::path file = iter;
		result += (file.filename().string()+"\ \ ");
	}
	return result;
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
			DataManager::Student st = DataManager::getStudent(std::to_string(qq_id));
			StuInfo stuinfo;
			stuinfo.studentId = st.getId();
			stuinfo.studentNum = atoll(st.getSchoolNum().c_str());
			stuinfo.classId = st.getClassId();
			getStuInfo.insert(std::pair<long long, StuInfo>(qq_id, stuinfo));
		}
		catch (DataManager::DMExcetion::TARGET_NOT_FOUND)
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
		PrivateMessageSender sender(qq_id, u8"δע���˺ţ�������ע���Կ�ʼ");
		sender.send();
		return;
	}

	//����״̬
	if (status[qq_id] == PeerStatus::IDLE)
	{
		//��ѯ������Ϣ
		if (data.substr(0, 6) == u"��ѯ������Ϣ"|| u"��ȡ������Ϣ")
		{
			DataManager::Student st = DataManager::getStudent((int)getStuInfo[qq_id].studentId);
			DataManager::Class cl = DataManager::getClass(st.getClassId());
			std::string send = u8"���ĸ�����Ϣ����\n\r������" + st.getName() + u8"\n\rѧ�ţ�" + st.getSchoolNum() + u8"\n\r�༶��" + cl.getName() + u8"\n\r��ʦ��"; //TODO: teacher's name
			PrivateMessageSender sender(qq_id, send);
			sender.send();
			return;
		}

		//��ѯ��ҵ���б�
		if (data.substr(0, 4) == u"��ѯ��ҵ"|| u"��ȡ��ҵ")//TODO:��ѯ��ҵ��n����״̬��0δ��� 1���ύ 2�����ġ��������������ҵ���ݣ����ģ�������
		{
			std::string homewordId_str = Tools::to_utf8(Tools::delFirstCom(data, 4));
			if (!Tools::isNum(homewordId_str))//δ��⵽����
			{
				std::string message;
					std::vector<DataManager::Homework> homeworklist = DataManager::getHomeworkListByStuId(getStuInfo[qq_id].studentId, getStuInfo[qq_id].classId);
					if (homeworklist.size() != 0)
					{
						for (auto& iter : homeworklist)
						{
							int status = iter.getStatus();//TODO: ddl��ʾ
							message += (u8"����ҵ " + std::to_string(iter.getId()) + u8"��  " + getHomeworkStatus(status));
							if (status == 2)//������
							{
								message += u8"������" + std::to_string(iter.getScore());
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
#include <stdlib.h>
			int homeworkID = atoi(homewordId_str.c_str());
			std::string message;
			try
			{
				DataManager::Homework homework = DataManager::getHomework(homeworkID);
				int homeworkStatus = homework.getStatus();
				if (homeworkStatus == 0)//δ�ύ
				{
					message += (u8"����ҵ " + std::to_string(homework.getId()) + u8"��  " + getHomeworkStatus(homeworkStatus))+ u8"\r\n";
					message += (u8"����ҵ���ݡ�\r\n");//TODO: ��ȡassi�������ҵ���ݡ�ddl
					message += (u8"������ʱ�䡿");
					PrivateMessageSender sender(qq_id, message);
					sender.send();
					return;
				}
				if (homeworkStatus == 1)//���ύ
				{
					message += (u8"����ҵ " + std::to_string(homework.getId()) + u8"��  " + getHomeworkStatus(homeworkStatus)) + u8"\r\n";
					message += (u8"����ҵ���ݡ�\r\n");//TODO: ��ȡassi�������ҵ���ݡ�ddl
					message += (u8"������ʱ�䡿\r\n");
					message += (u8"����ҵ�����б�\r\n" + getHomeworkFilename(homework.getContentURL())+u8"\r\n");
					message += (u8"����ҵ�����б�\r\n" + getHomeworkFilename(homework.getAttachmentURL()) + u8"\r\n");
					PrivateMessageSender sender(qq_id, message);
					sender.send();
					return;
				}
				if (homeworkStatus == 2)//������
				{
					message += (u8"����ҵ " + std::to_string(homework.getId()) + u8"��  " + getHomeworkStatus(homeworkStatus)) + u8"\r\n";
					message += (u8"����ҵ���ݡ�\r\n");//TODO: ��ȡassi�������ҵ���ݡ�ddl
					message += (u8"������ʱ�䡿 ");
					message += (u8"�������� " + std::to_string(homework.getScore()) + u8"\r\n");
					message += (u8"�����\r\n" + homework.getComments() + u8"\r\n");
					message += (u8"����ҵ�����б�\r\n" + getHomeworkFilename(homework.getContentURL()) + u8"\r\n");
					message += (u8"����ҵ�����б�\r\n" + getHomeworkFilename(homework.getAttachmentURL()) + u8"\r\n");
					PrivateMessageSender sender(qq_id, message);
					sender.send();
					return;
				}
			}
			catch(DataManager::DMExcetion::TARGET_NOT_FOUND)//����ҵ
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
		if (data.substr(0, 4) == u"�ύ��ҵ" || data.substr(0, 4) == u"�޸���ҵ")
		{
			std::string homewordId_str = Tools::to_utf8(Tools::delFirstCom(data, 4));
			if (!Tools::isNum(homewordId_str))
			{
				PrivateMessageSender sender(qq_id, u8"δ֪���������");
				sender.send();
				return;
			}
			int homeworkID = atoi(homewordId_str.c_str());
			try
			{
				status[qq_id] = PeerStatus::HOMEWORK;
				
				if (data.substr(0, 2) != u"�ύ")
				{
					try
					{
						DataManager::Homework hw((int)getStuInfo[qq_id].studentId, homeworkID);
					}
					catch (DataManager::DMExcetion::TARGET_EXISTED)
					{

					}
				}

				DataManager::Homework hw((int)getStuInfo[qq_id].studentId, homeworkID);
				DataManager::Student st = DataManager::getStudent((int)getStuInfo[qq_id].studentId);
				HomeworkInfo info;
				info.classId = st.getClassId();
				info.homeworkId = homeworkID;
				info.studentId = getStuInfo[qq_id].studentId;
				info.studentNum = atoll(st.getSchoolNum().c_str());
				info.submitId = hw.getId();
				getHomeworkInfo[qq_id] = info;
				if (homeworkStatus == 0)//δ�ύ
				{
					DataManager::Homework hw((int)getStuInfo[qq_id].studentId, homeworkID);
					DataManager::Student st = DataManager::getStudent((int)getStuInfo[qq_id].studentId);
					HomeworkInfo info;
					info.classId = st.getClassId();
					info.homeworkId = homeworkID;
					info.studentId = getStuInfo[qq_id].studentId;
					info.studentNum = atoll(st.getSchoolNum().c_str());
					info.submitId = hw.getId();
					getHomeworkInfo[qq_id] = info;
					PrivateMessageSender sender(qq_id, u8"��ʼ�ύ��ҵ" + std::to_string(info.homeworkId) + u8"\r\n���롰�ύ�����ύ�����롰ȡ������ɾ��");
					sender.send();
					return;
				}
				if (homeworkStatus == 1)//���ύ
				{
					status[qq_id] = PeerStatus::HOMEWORK;
					DataManager::Homework hw((int)getStuInfo[qq_id].studentId, homeworkID);
					DataManager::Student st = DataManager::getStudent((int)getStuInfo[qq_id].studentId);
					HomeworkInfo info;
					info.classId = st.getClassId();
					info.homeworkId = homeworkID;
					info.studentId = getStuInfo[qq_id].studentId;
					info.studentNum = atoll(st.getSchoolNum().c_str());
					info.submitId = hw.getId();
					getHomeworkInfo[qq_id] = info;
					//HomCommand(data, qq_id);
					return;
				}
				if (homeworkStatus == 2)//������
				{
					status[qq_id] = PeerStatus::HOMEWORK;
					DataManager::Homework hw((int)getStuInfo[qq_id].studentId, homeworkID);
					DataManager::Student st = DataManager::getStudent((int)getStuInfo[qq_id].studentId);
					HomeworkInfo info;
					info.classId = st.getClassId();
					info.homeworkId = homeworkID;
					info.studentId = getStuInfo[qq_id].studentId;
					info.studentNum = atoll(st.getSchoolNum().c_str());
					info.submitId = hw.getId();
					getHomeworkInfo[qq_id] = info;
					HomCommand(data, qq_id);
					return;
				}
				return;
			}
			catch (DataManager::DMExcetion::TARGET_NOT_FOUND)
			{
				status[qq_id] = PeerStatus::IDLE;
				PrivateMessageSender sender(qq_id, u8"���޸���ҵ��������");
				sender.send();
				return;
			}
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
		
		try
		{
			DataManager::Student st(std::to_string(regInfo.schoolId), std::to_string(qq_id), regInfo.name);
		}
		catch(DataManager::DMError& e)
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
	if (data.substr(0, 2) == u"ȡ��")
	{
		PrivateMessageSender sender(qq_id, u8"����ȡ���ύ��ҵ" + std::to_string(getHomeworkInfo[qq_id].homeworkId));
		sender.send();
		status[qq_id] = PeerStatus::IDLE;
		getHomeworkInfo.erase(qq_id);
		return;
	}
	if (data.substr(0, 2) == u"ɾ��")
	{
		std::u16string tmp = Tools::delFirstCom(data, 2);
		File file(getHomeworkInfo.at(qq_id));
		PrivateMessageSender sender(qq_id, file.delFile(tmp));
		sender.send();
		return;
	}
	if (data.substr(0, 6) == u"��ȡ�ļ��б�")
	{
		File file(getHomeworkInfo[qq_id]);
		PrivateMessageSender sender(qq_id, file.getFileList());
		sender.send();
		return;
	}
	if (data.substr(0, 4) == u"��ȡ�ļ�")
	{
		std::u16string tmp = Tools::delFirstCom(data, 4);
		File file(getHomeworkInfo[qq_id]);
		PrivateMessageSender sender(qq_id, file.getFile(tmp));
		sender.send();
		return;
	}
	
	File file(getHomeworkInfo[qq_id]);
	std::string fileName = file.storeText(Tools::to_utf8(data));
	PrivateMessageSender sender(qq_id, u8"�ı���"+fileName+u8"\ �ѱ���");
	sender.send();
	return;
}
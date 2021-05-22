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

std::string helper = u8"��ע�᡿\n���û�ͨ��ע���ύ�����༶����ʵ������ѧ�ţ���Ϣһ���ύ��ѧ���޷������޸ġ�\nע���п�ͨ��ȡ�������˳�ע�ᡣ\n\n����\nע��\n[Rr]eg\n[Rr]egister\n--------\n��������Ϣ��\nע��ɹ���ɲ�ѯ����Ϣ������������ѧ�š��༶����ʦ��\n\n����\n��ѯ������Ϣ\n��ȡ������Ϣ\n[Gg]etinfo\n--------\n����ҵ�б�\n�û��ɲ�ѯ����������ҵ��������ҵID����ҵ״̬����ֹʱ�䡢����\n\n����\n��ѯ��ҵ\n��ȡ��ҵ\n[Gg]et\n[Gg]ethomework\n--------\n����ҵ���顿\n�û�ͨ��ָ����ҵID��ѯ��ǰ��ҵ�顣\n\n����\n��ҵID����ҵ״̬����ҵ���ݡ���ֹʱ��\n����������\n��ҵ�����б���ҵ�����б�\n\n����\n��ѯ��ҵ {��ҵID}\n��ȡ��ҵ {��ҵID}\n[Gg]et {��ҵID}\n[Gg]ethomework {��ҵID}\n--------\n���ύ��ҵ��\n�û�ͨ��ָ����ҵID�����ύģʽ�����ύ��ҵ�Զ��޸ġ�\n��ϸ���������롰���� �ύģʽ���鿴��\n\n����\n�ύ��ҵ {��ҵID}\n[Ss]ubmit {��ҵID}\n--------\n���޸���ҵ��\n�û�ͨ��ָ����ҵID�����ύģʽ��δ�ύ��ҵ�Զ��½���\n��ϸ���������롰���� �ύģʽ���鿴��\n\n����\n�޸���ҵ {��ҵID}\n[Mm]odify {��ҵID}\n--------\n��������\n��ʾ���ĵ�\n���������Ϣ�����롰���� �ύ���鿴\n\n����\n����\n[Hh]elp";
std::string regHelper = u8"��������ע��ģʽ��\nע����Ҫ��д�༶�����롢ѧ��������ѧ��\n--------\n��ȡ��ע�᡿\nɾ����������д��Ϣ������Ϊδע��״̬\n\n����\nȡ��\n[Cc]ancel\n";
std::string subHelper = u8"���ύ���ݡ�\n�ı���ͼƬ��ֱ���ڶԻ��������뷢�ͣ��ڱ��طֱ𱣴�Ϊtxt�ļ���ͼƬ�ļ�\n--------\n���ļ��б�\n��ѯ����ҵ�´��ڵ��ļ�������ļ���(����չ��)\n\n����\n��ȡ���б�\n��ѯ�ļ��б�\n[Gg]etlist\n--------\n����ѯ�ļ���\n�û�ͨ��ָ���ļ���(����չ��)�������ļ�����\nĿǰ�ɷ����ı��ļ��������ļ�\n\n����\n��ȡ {�ļ���}\n��ȡ�ļ� {�ļ���}\n��ѯ {�ļ���}\n��ѯ�ļ� {�ļ���}\n[Gg]et {�ļ���}\n--------\n��ɾ���ļ���\n�û�ͨ��ָ���ļ���(����չ��)��ɾ���ļ�\n��ʹ��|�ָ����ָ�����ļ���������ɾ��\n\n����\nɾ���ļ� {�ļ���1|�ļ���2|...}\nɾ�� {�ļ���1|�ļ���2|...}\n[Dd]elete {�ļ���1|�ļ���2|...}\n--------\n��ɾ�������ļ���\n��ո���ҵ�������ļ�\n��ע�⣺�ò����޷��ָ�\n\n����\nȫ��ɾ��\nɾ��ȫ��\n����ļ�\n[Dd]eleteall\n--------\n��ȡ���ύ��\n�˳��ύģʽ�����ļ�����Ϊ�ݸ�\n�κ��޸Ķ����᷵�ظ���ʦ\n\n����\nȡ��\nȡ���ύ\n[Cc]ancel\n--------\n�������ύ��\n������ҵ�����ʦ�ύ\n\n����\n�ύ\n�ύ��ҵ\nȷ���ύ\n[Ss]ubmit";
std::string homHelper1 = u8"���������ύģʽ��\n�����ύ ��ҵ ";
std::string homHelper2 = u8"\n--------\n���ύ���ݡ�\n�ı���ͼƬ��ֱ���ڶԻ��������뷢�ͣ��ڱ��طֱ𱣴�Ϊtxt�ļ���ͼƬ�ļ�\n--------\n���ļ��б�\n��ѯ����ҵ�´��ڵ��ļ�������ļ���(����չ��)\n\n����\n��ȡ���б�\n��ѯ�ļ��б�\n[Gg]etlist\n--------\n����ѯ�ļ���\n�û�ͨ��ָ���ļ���(����չ��)�������ļ�����\nĿǰ�ɷ����ı��ļ��������ļ�\n\n����\n��ȡ {�ļ���}\n��ȡ�ļ� {�ļ���}\n��ѯ {�ļ���}\n��ѯ�ļ� {�ļ���}\n[Gg]et {�ļ���}\n--------\n��ɾ���ļ���\n�û�ͨ��ָ���ļ���(����չ��)��ɾ���ļ�\n��ʹ��|�ָ����ָ�����ļ���������ɾ��\n\n����\nɾ���ļ� {�ļ���1|�ļ���2|...}\nɾ�� {�ļ���1|�ļ���2|...}\n[Dd]elete {�ļ���1|�ļ���2|...}\n--------\n��ɾ�������ļ���\n��ո���ҵ�������ļ�\n��ע�⣺�ò����޷��ָ�\n\n����\nȫ��ɾ��\nɾ��ȫ��\n����ļ�\n[Dd]eleteall\n--------\n��ȡ���ύ��\n�˳��ύģʽ�����ļ�����Ϊ�ݸ�\n�κ��޸Ķ����᷵�ظ���ʦ\n\n����\nȡ��\nȡ���ύ\n[Cc]ancel\n--------\n�������ύ��\n������ҵ�����ʦ�ύ\n\n����\n�ύ\n�ύ��ҵ\nȷ���ύ\n[Ss]ubmit";


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
	std::vector<DataManager::CompleteHomeworkList> homeworklist = DataManager::getHomeworkListByStuId((long)getStuInfo[qq_id].studentId, (long)getStuInfo[qq_id].classId);
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
	if (data == u"ע��"|| data == u"reg" || data == u"register"|| data == u"Register"|| data == u"Reg")
	{
		if (status[qq_id] == PeerStatus::UNREG)
			status[qq_id] = PeerStatus::REGISTER;
		if (getStuInfo.count(qq_id))
		{
			PrivateMessageSender sender(qq_id, u8"����ע��\n���롰��ѯ������Ϣ���Բ�ѯ");
			sender.send();
			return;
		}
		subCom = Tools::delFirstCom(data, 2);
		status[qq_id] = PeerStatus::REGISTER;
		RegCommand(subCom, qq_id);
		return;
	}

	if (data == u"����" || data == u"Help" || data == u"help")
	{
		PrivateMessageSender sender(qq_id, helper);
		sender.send();
		return;
	}

	if (data == u"���� �ύģʽ" || data == u"Help �ύģʽ" || data == u"help �ύģʽ" || data == u"help submit" || data == u"Help Submit")
	{
		PrivateMessageSender sender(qq_id, subHelper);
		sender.send();
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
		if (data==u"��ѯ������Ϣ"|| data == u"��ȡ������Ϣ" || data == u"getinfo" || data == u"Getinfo")
		{
			DataManager::Student st((int)getStuInfo[qq_id].studentId);
			DataManager::Class cl(st.getClassId());
			std::string send = u8"���ĸ�����Ϣ����\n\n������" + st.getName() + u8"\nѧ�ţ�" + st.getSchoolNum() + u8"\n�༶��" + cl.getName(); 
			if (cl.getLocation() != u8"")
			{
				send += (u8"\n�Ͽεص㣺" + cl.getLocation());
			}
			if (cl.getTime() != u8"")
			{
				send += (u8"\n�Ͽ�ʱ�䣺" + cl.getTime());
			}
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
					std::vector<DataManager::CompleteHomeworkList> homeworklist = DataManager::getHomeworkListByStuId((long)getStuInfo[qq_id].studentId, (long)getStuInfo[qq_id].classId);
					if (homeworklist.size() != 0)
					{
						for (auto& iter : homeworklist)
						{
							int status = iter.homework.getStatus();
							message += (u8"����ҵ " + std::to_string(iter.assignment.getId()) + u8"��  " + getHomeworkStatus(status) + u8"  ");
							if (status == 0)//δ�ύ
							{
								if (std::time(0) > iter.assignment.getDeadline())
								{
									message += (u8"�ѽ�ֹ�ύ");
								}
								else
								{
									message += (u8"��ֹʱ�䣺" + TimeConvert(iter.assignment.getDeadline()));
								}
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
					message += (u8"����ֹʱ�䡿  " + TimeConvert(ch.assignment.getDeadline()) + u8"\n\n");
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
					message += (u8"����ֹʱ�䡿  " + TimeConvert(ch.assignment.getDeadline()) + u8"\n\n");
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
		if (data.substr(0, 11) == u"gethomework" || data.substr(0, 11) == u"Gethomework")
		{
			std::string assignmentId_str = Tools::to_utf8(Tools::delFirstCom(data, 11));
			if (!Tools::isNum(assignmentId_str))//δ��⵽����
			{
				std::string message;
				std::vector<DataManager::CompleteHomeworkList> homeworklist = DataManager::getHomeworkListByStuId((long)getStuInfo[qq_id].studentId, (long)getStuInfo[qq_id].classId);
				if (homeworklist.size() != 0)
				{
					for (auto& iter : homeworklist)
					{
						int status = iter.homework.getStatus();
						message += (u8"����ҵ " + std::to_string(iter.assignment.getId()) + u8"��  " + getHomeworkStatus(status) + u8"  ");
						if (status == 0)//δ�ύ
						{
							if (std::time(0) > iter.assignment.getDeadline())
							{
								message += (u8"�ѽ�ֹ�ύ");
							}
							else
							{
								message += (u8"��ֹʱ�䣺" + TimeConvert(iter.assignment.getDeadline()));
							}
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
					message += (u8"����ҵ " + std::to_string(ch.assignment.getId()) + u8"��  " + getHomeworkStatus(homeworkStatus)) + u8"\r\n";
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
					message += (u8"����ֹʱ�䡿  " + TimeConvert(ch.assignment.getDeadline()) + u8"\n\n");
					message += (u8"����ҵ�����б�\r\n" + getHomeworkFilename(ch.homework.getContentURL()) + u8"\r\n");
					message += (u8"����ҵ�����б�\r\n" + getHomeworkFilename(ch.homework.getAttachmentURL()) + u8"\r\n");
					PrivateMessageSender sender(qq_id, message);
					sender.send();
					return;
				}
				if (homeworkStatus == 2)//������
				{
					message += (u8"����ҵ " + std::to_string(ch.assignment.getId()) + u8"��  " + getHomeworkStatus(homeworkStatus)) + u8"\n\n";
					message += (u8"����ҵ���ݡ�\r\n" + ch.assignment.getDescription() + u8"\r\n");
					message += (u8"����ֹʱ�䡿  " + TimeConvert(ch.assignment.getDeadline()) + u8"\n\n");
					message += (u8"�������� " + std::to_string(ch.homework.getScore()) + u8"\r\n");
					message += (u8"�����\r\n" + ch.homework.getComments() + u8"\n\n");
					message += (u8"����ҵ�����б�\r\n" + getHomeworkFilename(ch.homework.getContentURL()) + u8"\r\n");
					message += (u8"����ҵ�����б�\r\n" + getHomeworkFilename(ch.homework.getAttachmentURL()) + u8"\r\n");
					PrivateMessageSender sender(qq_id, message);
					sender.send();
					return;
				}
			}
			catch (DataManager::DMException::TARGET_NOT_FOUND)//����ҵ
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
		if (data.substr(0, 3) == u"get" || data.substr(0, 3) == u"Get")
		{
			std::string assignmentId_str = Tools::to_utf8(Tools::delFirstCom(data, 3));
			if (!Tools::isNum(assignmentId_str))//δ��⵽����
			{
				std::string message;
				std::vector<DataManager::CompleteHomeworkList> homeworklist = DataManager::getHomeworkListByStuId((long)getStuInfo[qq_id].studentId, (long)getStuInfo[qq_id].classId);
				if (homeworklist.size() != 0)
				{
					for (auto& iter : homeworklist)
					{
						int status = iter.homework.getStatus();
						message += (u8"����ҵ " + std::to_string(iter.assignment.getId()) + u8"��  " + getHomeworkStatus(status) + u8"  ");
						if (status == 0)//δ�ύ
						{
							if (std::time(0) > iter.assignment.getDeadline())
							{
								message += (u8"�ѽ�ֹ�ύ");
							}
							else
							{
								message += (u8"��ֹʱ�䣺" + TimeConvert(iter.assignment.getDeadline()));
							}
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
					message += (u8"����ҵ " + std::to_string(ch.assignment.getId()) + u8"��  " + getHomeworkStatus(homeworkStatus)) + u8"\r\n";
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
					message += (u8"����ֹʱ�䡿  " + TimeConvert(ch.assignment.getDeadline()) + u8"\n\n");
					message += (u8"����ҵ�����б�\r\n" + getHomeworkFilename(ch.homework.getContentURL()) + u8"\r\n");
					message += (u8"����ҵ�����б�\r\n" + getHomeworkFilename(ch.homework.getAttachmentURL()) + u8"\r\n");
					PrivateMessageSender sender(qq_id, message);
					sender.send();
					return;
				}
				if (homeworkStatus == 2)//������
				{
					message += (u8"����ҵ " + std::to_string(ch.assignment.getId()) + u8"��  " + getHomeworkStatus(homeworkStatus)) + u8"\n\n";
					message += (u8"����ҵ���ݡ�\r\n" + ch.assignment.getDescription() + u8"\r\n");
					message += (u8"����ֹʱ�䡿  " + TimeConvert(ch.assignment.getDeadline()) + u8"\n\n");
					message += (u8"�������� " + std::to_string(ch.homework.getScore()) + u8"\r\n");
					message += (u8"�����\r\n" + ch.homework.getComments() + u8"\n\n");
					message += (u8"����ҵ�����б�\r\n" + getHomeworkFilename(ch.homework.getContentURL()) + u8"\r\n");
					message += (u8"����ҵ�����б�\r\n" + getHomeworkFilename(ch.homework.getAttachmentURL()) + u8"\r\n");
					PrivateMessageSender sender(qq_id, message);
					sender.send();
					return;
				}
			}
			catch (DataManager::DMException::TARGET_NOT_FOUND)//����ҵ
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

		//�ύ&�޸���ҵ
		if (data.substr(0, 4) == u"�ύ��ҵ"|| data.substr(0, 4) == u"�޸���ҵ")
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

				DataManager::CompleteHomeworkList ch = getCH(qq_id, assignmentId);

				status[qq_id] = PeerStatus::HOMEWORK;
				DataManager::Student st((long)getStuInfo[qq_id].studentId);
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
				if (getHomeworkInfo.count(qq_id))
					getHomeworkInfo.erase(qq_id);
				getHomeworkInfo.insert(std::pair<long long, HomeworkInfo>(qq_id, info));
				PrivateMessageSender sender2(qq_id, u8"��ʼ�ύ��ҵ" + std::to_string(info.homeworkId) + u8"\r\n���������롰ȷ���ύ�����ύ�����롰ȡ���ύ����ȡ��");
				sender2.send();

				File file(info);
				std::string filelist = file.getFileList();
				if (filelist != u8"�����ļ�")
				{
					PrivateMessageSender sender(qq_id, u8"�Ѽ�⵽�ݸ�\n" + filelist);
					sender.send();
				}

				return;
			}
			catch (DataManager::DMException::TARGET_NOT_FOUND)
			{
				status[qq_id] = PeerStatus::IDLE;
				PrivateMessageSender sender(qq_id, u8"���޸���ҵ��������");
				sender.send();
				return;
			}
		}
		if (data.substr(0, 6) == u"Submit" || data.substr(0, 6) == u"submit" || data.substr(0, 6) == u"Modify" || data.substr(0, 6) == u"modify")
		{
			std::string assignmentId_str = Tools::to_utf8(Tools::delFirstCom(data, 6));
			if (!Tools::isNum(assignmentId_str) || assignmentId_str == "")
			{
				PrivateMessageSender sender(qq_id, u8"δ֪���������");
				sender.send();
				return;
			}
			int assignmentId = atoi(assignmentId_str.c_str());
			try
			{

				DataManager::CompleteHomeworkList ch = getCH(qq_id, assignmentId);

				status[qq_id] = PeerStatus::HOMEWORK;
				DataManager::Student st((long)getStuInfo[qq_id].studentId);
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
				if (getHomeworkInfo.count(qq_id))
					getHomeworkInfo.erase(qq_id);
				getHomeworkInfo.insert(std::pair<long long, HomeworkInfo>(qq_id, info));
				PrivateMessageSender sender2(qq_id, u8"��ʼ�ύ��ҵ" + std::to_string(info.homeworkId) + u8"\r\n���������롰ȷ���ύ�����ύ�����롰ȡ���ύ����ȡ��");
				sender2.send();

				File file(info);
				std::string filelist = file.getFileList();
				if (filelist != u8"�����ļ�")
				{
					PrivateMessageSender sender(qq_id, u8"�Ѽ�⵽�ݸ�\n" + filelist);
					sender.send();
				}

				return;
			}
			catch (DataManager::DMException::TARGET_NOT_FOUND)
			{
				status[qq_id] = PeerStatus::IDLE;
				PrivateMessageSender sender(qq_id, u8"���޸���ҵ��������");
				sender.send();
				return;
			}
		}
	}

	PrivateMessageSender sender(qq_id, u8"δ֪���������\n���롰�������Ի�������б�");
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

	if (data == u"ȡ��ע��" || data == u"ȡ��" || data == u"Cancel" || data == u"cancel")
	{
		PrivateMessageSender sender(qq_id, u8"��ȡ��ע��");
		sender.send();
		regStatus.erase(qq_id);
		status[qq_id] = PeerStatus::IDLE;
		return;
	}
	if (data == u"����" || data == u"Help" || data == u"help")
	{
		PrivateMessageSender sender(qq_id, regHelper);
		sender.send();
		return;
	}
	if (regInfo.status == RegStatus::START)
	{
		PrivateMessageSender sender1(qq_id, u8"��ʼע�ᣬ���롰ȡ���������˳�ע��\n\n������γ�������");
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
			DataManager::Class cl(Tools::to_utf8(classCode)); 
			//DataManager::Class cl(1);
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
	if (data == u"ȡ��"|| data == u"ȡ���ύ"|| data == u"Cancel"||data == u"cancel")
	{
		PrivateMessageSender sender(qq_id, u8"����ȡ���ύ��ҵ" + std::to_string(getHomeworkInfo[qq_id].homeworkId)+u8"\n��ǰ�ݸ��ѱ���");
		sender.send();
		status[qq_id] = PeerStatus::IDLE;
		getHomeworkInfo.erase(qq_id);
		return;
	}
	if (data == u"����" || data == u"Help" || data == u"help")
	{
		PrivateMessageSender sender(qq_id, homHelper1+std::to_string(getHomeworkInfo[qq_id].homeworkId)+homHelper2);
		sender.send();
		return;
	}
	if (data == u"ȫ��ɾ��" || data == u"����ļ�" || data == u"Deleteall" || data == u"deleteall")
	{
		File file(getHomeworkInfo.at(qq_id));
		file.delAll();
		PrivateMessageSender sender(qq_id, u8"�ļ������");
		sender.send();
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
	if (data.substr(0, 6) == u"Delete" || data.substr(0, 6) == u"delete")
	{
		std::u16string tmp = Tools::delFirstCom(data, 6);
		std::vector<std::u16string> delList = split(tmp, u"|");
		for (auto& iter : delList)
		{
			File file(getHomeworkInfo.at(qq_id));
			PrivateMessageSender sender(qq_id, file.delFile(iter));
			sender.send();
		}
		return;
	}
	if (data == u"��ȡ�ļ��б�"|| data == u"��ѯ�ļ��б�" || data == u"Getlist" || data == u"getlist")
	{
		File file(getHomeworkInfo[qq_id]);
		PrivateMessageSender sender(qq_id, file.getFileList());
		sender.send();
		return;
	}
	if (data.substr(0, 3) == u"Get" || data.substr(0, 3) == u"get")
	{
		std::u16string tmp = Tools::delFirstCom(data, 3);
		File file(getHomeworkInfo[qq_id]);
		PrivateMessageSender sender(qq_id, file.getFile(tmp));
		sender.send();
		return;
	}
	if (data.substr(0, 2) == u"��ȡ" || data.substr(0, 2) == u"��ѯ")
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
	
	if (data == u"�ύ��ҵ" || data == u"ȷ���ύ" || data == u"�ύ" || data == u"Submit" || data == u"submit")
	{
		File file(getHomeworkInfo[qq_id]);
		try
		{
			DataManager::Homework hm((long)getStuInfo[qq_id].studentId, (long)getHomeworkInfo[qq_id].homeworkId);
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
		catch (DataManager::DMException::TARGET_EXISTED)
		{
			long long submitId = file.getSubmitId();
			DataManager::Homework hm((long)submitId);
			if (file.save(submitId))//�ϴ��ɹ�
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
		catch (...)
		{
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

bool sendReview(long homeworkId)
{
	std::string msg = u8"δ֪��Ϣ";
	try
	{
		DataManager::Homework hm(homeworkId);
		DataManager::Assignment as(hm.getAssignmentId());
		DataManager::Student st(hm.getStudentId());

		long long qq_id = atoll(st.getQQ().c_str());
		std::string msg = u8"���ύ����ҵ " + std::to_string(as.getId()) + u8"������\n\n�������� " + std::to_string(hm.getScore()) + u8"\n�����\n" + hm.getComments();
		PrivateMessageSender sender(qq_id, msg);
		sender.send();
		return true;
	}
	catch (...)
	{
		return false;
	}
}
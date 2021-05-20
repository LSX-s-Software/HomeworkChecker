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
/// 转换作业状态
/// </summary>
/// <param name="id">状态id</param>
/// <returns></returns>
std::string getHomeworkStatus(int id)
{
	if (id == 0) return u8"未提交";
	if (id == 1) return u8"已提交";
	if (id == 2) return u8"已批改";
	return u8"未知状态";
}
/// <summary>
/// 字符串分隔
/// </summary>
/// <param name="s">原始字符串</param>
/// <param name="seperator">分隔符 可多个</param>
/// <returns>分隔后字符串列表</returns>
std::vector<std::string> split(const std::string& s, const std::string& seperator) {
	std::vector<std::string> result;
	typedef std::string::size_type string_size;
	string_size i = 0;

	while (i != s.size()) {
		//找到字符串中首个不等于分隔符的字母；
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

		//找到又一个分隔符，将两个分隔符之间的字符串取出；
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
/// 字符串分隔
/// </summary>
/// <param name="s">原始字符串</param>
/// <param name="seperator">分隔符 可多个</param>
/// <returns>分隔后字符串列表</returns>
std::vector<std::u16string> split(const std::u16string& s, const std::u16string& seperator) {
	std::vector<std::u16string> result;
	typedef std::u16string::size_type string_size;
	string_size i = 0;

	while (i != s.size()) {
		//找到字符串中首个不等于分隔符的字母；
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

		//找到又一个分隔符，将两个分隔符之间的字符串取出；
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

	//添加当前状态
	if (!status.count(qq_id)) status.insert(pair(qq_id, PeerStatus::IDLE));
	//本地化学生数据
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

	//注册中
	if (status[qq_id] == PeerStatus::REGISTER)
	{
		subCom = data;
		Tools::delSpaceAhead(subCom);
		RegCommand(subCom, qq_id);
		return;
	}

	//提交作业中
	if (status[qq_id] == PeerStatus::HOMEWORK)
	{
		subCom = data;
		Tools::delSpaceAhead(subCom);
		HomCommand(subCom, qq_id);
		return;
	}

	//开始注册
	if (data.substr(0, 2) == u"注册")
	{
		if (status[qq_id] == PeerStatus::UNREG)
			status[qq_id] = PeerStatus::REGISTER;
		if (getStuInfo.count(qq_id))
		{
			PrivateMessageSender sender(qq_id, u8"您已注册");
			sender.send();
			return;
		}
		subCom = Tools::delFirstCom(data, 2);
		status[qq_id] = PeerStatus::REGISTER;
		RegCommand(subCom, qq_id);
		return;
	}

	//未注册
	if (status[qq_id] == PeerStatus::UNREG)//未注册
	{
		PrivateMessageSender sender(qq_id, u8"未注册账号，请输入注册以开始");
		sender.send();
		return;
	}

	//空闲状态
	if (status[qq_id] == PeerStatus::IDLE)
	{
		//查询个人信息
		if (data.substr(0, 6) == u"查询个人信息"|| u"获取个人信息")
		{
			DataManager::Student st = DataManager::getStudent((int)getStuInfo[qq_id].studentId);
			DataManager::Class cl = DataManager::getClass(st.getClassId());
			std::string send = u8"您的个人信息如下\n\r姓名：" + st.getName() + u8"\n\r学号：" + st.getSchoolNum() + u8"\n\r班级：" + cl.getName() + u8"\n\r老师："; //TODO: teacher's name
			PrivateMessageSender sender(qq_id, send);
			sender.send();
			return;
		}

		//查询作业（列表）
		if (data.substr(0, 4) == u"查询作业"|| u"获取作业")//TODO:查询作业（n）：状态【0未完成 1已提交 2已批改】，分数，评语，作业内容，正文，附件表
		{
			std::string homewordId_str = Tools::to_utf8(Tools::delFirstCom(data, 4));
			if (!Tools::isNum(homewordId_str))//未检测到数字
			{
				std::string message;
					std::vector<DataManager::Homework> homeworklist = DataManager::getHomeworkListByStuId(getStuInfo[qq_id].studentId, getStuInfo[qq_id].classId);
					if (homeworklist.size() != 0)
					{
						for (auto& iter : homeworklist)
						{
							int status = iter.getStatus();//TODO: ddl显示
							message += (u8"【作业 " + std::to_string(iter.getId()) + u8"】  " + getHomeworkStatus(status));
							if (status == 2)//已批改
							{
								message += u8"分数：" + std::to_string(iter.getScore());
							}
							message += "\r\n";
						}
					}
					else
						message = u8"暂无作业";
				PrivateMessageSender sender(qq_id, u8"作业列表如下\r\n" + message);
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
				if (homeworkStatus == 0)//未提交
				{
					message += (u8"【作业 " + std::to_string(homework.getId()) + u8"】  " + getHomeworkStatus(homeworkStatus))+ u8"\r\n";
					message += (u8"【作业内容】\r\n");//TODO: 获取assi，添加作业内容、ddl
					message += (u8"【截至时间】");
					PrivateMessageSender sender(qq_id, message);
					sender.send();
					return;
				}
				if (homeworkStatus == 1)//已提交
				{
					message += (u8"【作业 " + std::to_string(homework.getId()) + u8"】  " + getHomeworkStatus(homeworkStatus)) + u8"\r\n";
					message += (u8"【作业内容】\r\n");//TODO: 获取assi，添加作业内容、ddl
					message += (u8"【截至时间】\r\n");
					message += (u8"【作业正文列表】\r\n" + getHomeworkFilename(homework.getContentURL())+u8"\r\n");
					message += (u8"【作业附件列表】\r\n" + getHomeworkFilename(homework.getAttachmentURL()) + u8"\r\n");
					PrivateMessageSender sender(qq_id, message);
					sender.send();
					return;
				}
				if (homeworkStatus == 2)//已批改
				{
					message += (u8"【作业 " + std::to_string(homework.getId()) + u8"】  " + getHomeworkStatus(homeworkStatus)) + u8"\r\n";
					message += (u8"【作业内容】\r\n");//TODO: 获取assi，添加作业内容、ddl
					message += (u8"【截至时间】 ");
					message += (u8"【分数】 " + std::to_string(homework.getScore()) + u8"\r\n");
					message += (u8"【评语】\r\n" + homework.getComments() + u8"\r\n");
					message += (u8"【作业正文列表】\r\n" + getHomeworkFilename(homework.getContentURL()) + u8"\r\n");
					message += (u8"【作业附件列表】\r\n" + getHomeworkFilename(homework.getAttachmentURL()) + u8"\r\n");
					PrivateMessageSender sender(qq_id, message);
					sender.send();
					return;
				}
			}
			catch(DataManager::DMExcetion::TARGET_NOT_FOUND)//无作业
			{
				PrivateMessageSender sender(qq_id, u8"暂无该作业，请重试");
				sender.send();
				return;
			}
			catch (std::exception)
			{
				PrivateMessageSender sender(qq_id, u8"未知错误，请重试");
				sender.send();
				return;
			}
			return;
		}

		//提交作业
		if (data.substr(0, 4) == u"提交作业" || data.substr(0, 4) == u"修改作业")
		{
			std::string homewordId_str = Tools::to_utf8(Tools::delFirstCom(data, 4));
			if (!Tools::isNum(homewordId_str))
			{
				PrivateMessageSender sender(qq_id, u8"未知命令，请重试");
				sender.send();
				return;
			}
			int homeworkID = atoi(homewordId_str.c_str());
			try
			{
				status[qq_id] = PeerStatus::HOMEWORK;
				
				if (data.substr(0, 2) != u"提交")
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
				if (homeworkStatus == 0)//未提交
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
					PrivateMessageSender sender(qq_id, u8"开始提交作业" + std::to_string(info.homeworkId) + u8"\r\n输入“提交”以提交，输入“取消”以删除");
					sender.send();
					return;
				}
				if (homeworkStatus == 1)//已提交
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
				if (homeworkStatus == 2)//已批改
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
				PrivateMessageSender sender(qq_id, u8"暂无该作业，请重试");
				sender.send();
				return;
			}
		}
	}


	PrivateMessageSender sender(qq_id, u8"未知命令，请重试");
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
		PrivateMessageSender sender1(qq_id, u8"开始注册，请输入课程邀请码");
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
			PrivateMessageSender sender(qq_id, u8"未知课程邀请码，请重试");
			sender.send();
			return;
		}
		long long getclassId = 123;

		std::string classInfo = u8"您加入的课程：xxxxx\\r\\n任课老师：yyyyyy\\r\\n\\r\\n请输入姓名";

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
		PrivateMessageSender sender(qq_id, u8"请输入学号");
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
			PrivateMessageSender sender(qq_id, u8"学号格式错误，请重试");
			sender.send();
			return;
		}
#include <stdlib.h>
		long long schoolID = atoll(schoolID_str.c_str());

		regInfo.status = RegStatus::CONFIRM;
		regInfo.schoolId = schoolID;
		regStatus[qq_id] = regInfo;

		std::string classInfo = u8"您的注册信息如下\r\n姓名：" + regInfo.name + u8"\r\n学号：" + std::to_string(regInfo.schoolId) + u8"\r\n\r\n输入“确认”以提交";
		PrivateMessageSender sender(qq_id, classInfo);
		sender.send();
		return;
	}

	if (regInfo.status == RegStatus::CONFIRM)
	{
		std::u16string command = data.substr(0, data.find_first_of(u" "));
		if (command != u"确认")
		{
			PrivateMessageSender sender(qq_id, u8"已取消注册");
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
			PrivateMessageSender sender(qq_id, u8"注册失败，请重试");
			sender.send();
			regStatus.erase(qq_id);
			status[qq_id] = PeerStatus::UNREG;
		}
		PrivateMessageSender sender(qq_id, u8"注册成功");
		sender.send();
		regStatus.erase(qq_id);
		status[qq_id] = PeerStatus::IDLE;
		return;
	}
}

void HomCommand(std::u16string data, long long qq_id)
{
	if (data.substr(0, 2) == u"取消")
	{
		PrivateMessageSender sender(qq_id, u8"您已取消提交作业" + std::to_string(getHomeworkInfo[qq_id].homeworkId));
		sender.send();
		status[qq_id] = PeerStatus::IDLE;
		getHomeworkInfo.erase(qq_id);
		return;
	}
	if (data.substr(0, 2) == u"删除")
	{
		std::u16string tmp = Tools::delFirstCom(data, 2);
		File file(getHomeworkInfo.at(qq_id));
		PrivateMessageSender sender(qq_id, file.delFile(tmp));
		sender.send();
		return;
	}
	if (data.substr(0, 6) == u"获取文件列表")
	{
		File file(getHomeworkInfo[qq_id]);
		PrivateMessageSender sender(qq_id, file.getFileList());
		sender.send();
		return;
	}
	if (data.substr(0, 4) == u"获取文件")
	{
		std::u16string tmp = Tools::delFirstCom(data, 4);
		File file(getHomeworkInfo[qq_id]);
		PrivateMessageSender sender(qq_id, file.getFile(tmp));
		sender.send();
		return;
	}
	
	File file(getHomeworkInfo[qq_id]);
	std::string fileName = file.storeText(Tools::to_utf8(data));
	PrivateMessageSender sender(qq_id, u8"文本："+fileName+u8"\ 已保存");
	sender.send();
	return;
}
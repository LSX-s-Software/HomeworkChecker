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

std::string helper = u8"【注册】\n新用户通过注册提交所属班级、真实姓名与学号，信息一旦提交后学生无法自行修改。\n注册中可通过取消命令退出注册。\n\n命令\n注册\n[Rr]eg\n[Rr]egister\n--------\n【个人信息】\n注册成功后可查询人信息，包括姓名、学号、班级和老师。\n\n命令\n查询个人信息\n获取个人信息\n[Gg]etinfo\n--------\n【作业列表】\n用户可查询个人所有作业，包括作业ID、作业状态、截止时间、分数\n\n命令\n查询作业\n获取作业\n[Gg]et\n[Gg]ethomework\n--------\n【作业详情】\n用户通过指定作业ID查询当前作业情。\n\n包括\n作业ID、作业状态、作业内容、截止时间\n分数、评语\n作业正文列表、作业附件列表\n\n命令\n查询作业 {作业ID}\n获取作业 {作业ID}\n[Gg]et {作业ID}\n[Gg]ethomework {作业ID}\n--------\n【提交作业】\n用户通过指定作业ID进入提交模式，已提交作业自动修改。\n详细操作可输入“帮助 提交模式”查看。\n\n命令\n提交作业 {作业ID}\n[Ss]ubmit {作业ID}\n--------\n【修改作业】\n用户通过指定作业ID进入提交模式，未提交作业自动新建。\n详细操作可输入“帮助 提交模式”查看。\n\n命令\n修改作业 {作业ID}\n[Mm]odify {作业ID}\n--------\n【帮助】\n显示本文档\n更多帮助信息可输入“帮助 提交”查看\n\n命令\n帮助\n[Hh]elp";
std::string regHelper = u8"您正处于注册模式中\n注册需要填写班级邀请码、学生姓名、学号\n--------\n【取消注册】\n删除所有已填写信息，重置为未注册状态\n\n命令\n取消\n[Cc]ancel\n";
std::string subHelper = u8"【提交内容】\n文本和图片可直接在对话框内输入发送，在本地分别保存为txt文件与图片文件\n--------\n【文件列表】\n查询该作业下存在的文件，输出文件名(含扩展名)\n\n命令\n获取文列表\n查询文件列表\n[Gg]etlist\n--------\n【查询文件】\n用户通过指定文件名(含扩展名)，返回文件内容\n目前可返回文本文件、代码文件\n\n命令\n获取 {文件名}\n获取文件 {文件名}\n查询 {文件名}\n查询文件 {文件名}\n[Gg]et {文件名}\n--------\n【删除文件】\n用户通过指定文件名(含扩展名)，删除文件\n可使用|分隔符分隔多个文件名，批量删除\n\n命令\n删除文件 {文件名1|文件名2|...}\n删除 {文件名1|文件名2|...}\n[Dd]elete {文件名1|文件名2|...}\n--------\n【删除所有文件】\n清空该作业下所有文件\n！注意：该操作无法恢复\n\n命令\n全部删除\n删除全部\n清空文件\n[Dd]eleteall\n--------\n【取消提交】\n退出提交模式，所文件保存为草稿\n任何修改都不会返回给教师\n\n命令\n取消\n取消提交\n[Cc]ancel\n--------\n【保存提交】\n保存作业并向教师提交\n\n命令\n提交\n提交作业\n确认提交\n[Ss]ubmit";
std::string homHelper1 = u8"您正处于提交模式中\n正在提交 作业 ";
std::string homHelper2 = u8"\n--------\n【提交内容】\n文本和图片可直接在对话框内输入发送，在本地分别保存为txt文件与图片文件\n--------\n【文件列表】\n查询该作业下存在的文件，输出文件名(含扩展名)\n\n命令\n获取文列表\n查询文件列表\n[Gg]etlist\n--------\n【查询文件】\n用户通过指定文件名(含扩展名)，返回文件内容\n目前可返回文本文件、代码文件\n\n命令\n获取 {文件名}\n获取文件 {文件名}\n查询 {文件名}\n查询文件 {文件名}\n[Gg]et {文件名}\n--------\n【删除文件】\n用户通过指定文件名(含扩展名)，删除文件\n可使用|分隔符分隔多个文件名，批量删除\n\n命令\n删除文件 {文件名1|文件名2|...}\n删除 {文件名1|文件名2|...}\n[Dd]elete {文件名1|文件名2|...}\n--------\n【删除所有文件】\n清空该作业下所有文件\n！注意：该操作无法恢复\n\n命令\n全部删除\n删除全部\n清空文件\n[Dd]eleteall\n--------\n【取消提交】\n退出提交模式，所文件保存为草稿\n任何修改都不会返回给教师\n\n命令\n取消\n取消提交\n[Cc]ancel\n--------\n【保存提交】\n保存作业并向教师提交\n\n命令\n提交\n提交作业\n确认提交\n[Ss]ubmit";


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

/// <summary>
/// 获取文件名列表
/// </summary>
/// <param name="raw">读入url | 分隔</param>
/// <returns>返回文件名 空格分隔</returns>
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
/// TimeStamp转换为日期时间
/// </summary>
/// <param name="timeStamp"></param>
/// <returns>日期时间字符串</returns>
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
	for (auto& iter : homeworklist)//查找当前作业id
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

	//添加当前状态
	if (!status.count(qq_id)) status.insert(pair(qq_id, PeerStatus::IDLE));
	//本地化学生数据
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
	if (data == u"注册"|| data == u"reg" || data == u"register"|| data == u"Register"|| data == u"Reg")
	{
		if (status[qq_id] == PeerStatus::UNREG)
			status[qq_id] = PeerStatus::REGISTER;
		if (getStuInfo.count(qq_id))
		{
			PrivateMessageSender sender(qq_id, u8"您已注册\n输入“查询个人信息”以查询");
			sender.send();
			return;
		}
		subCom = Tools::delFirstCom(data, 2);
		status[qq_id] = PeerStatus::REGISTER;
		RegCommand(subCom, qq_id);
		return;
	}

	if (data == u"帮助" || data == u"Help" || data == u"help")
	{
		PrivateMessageSender sender(qq_id, helper);
		sender.send();
		return;
	}

	if (data == u"帮助 提交模式" || data == u"Help 提交模式" || data == u"help 提交模式" || data == u"help submit" || data == u"Help Submit")
	{
		PrivateMessageSender sender(qq_id, subHelper);
		sender.send();
		return;
	}

	//未注册
	if (status[qq_id] == PeerStatus::UNREG)//未注册
	{
		PrivateMessageSender sender(qq_id, u8"未注册账号，请输入“注册”以开始");
		sender.send();
		return;
	}

	//空闲状态
	if (status[qq_id] == PeerStatus::IDLE)
	{
		//查询个人信息
		if (data==u"查询个人信息"|| data == u"获取个人信息" || data == u"getinfo" || data == u"Getinfo")
		{
			try {
				DataManager::Student st((int)getStuInfo[qq_id].studentId);
				DataManager::Class cl(st.getClassId());
				std::string send = u8"您的个人信息如下\n\n姓名：" + st.getName() + u8"\n学号：" + st.getSchoolNum() + u8"\n班级：" + cl.getName();
				if (cl.getLocation() != u8"")
				{
					send += (u8"\n上课地点：" + cl.getLocation());
				}
				if (cl.getTime() != u8"")
				{
					send += (u8"\n上课时间：" + cl.getTime());
				}
				PrivateMessageSender sender(qq_id, send);
				sender.send();
				return;
			}
			catch (DataManager::DMException::TARGET_NOT_FOUND)
			{
				getStuInfo.erase(qq_id);
				PrivateMessageSender sender(qq_id, u8"[Demo Mode] Refresh account.");
				sender.send();
				status[qq_id] = PeerStatus::UNREG;
				return;
			}
		}

		//查询作业（列表）
		if (data.substr(0, 4) == u"查询作业"|| data.substr(0, 4) == u"获取作业")
		{
			std::string assignmentId_str = Tools::to_utf8(Tools::delFirstCom(data, 4));
			if (!Tools::isNum(assignmentId_str))//未检测到数字
			{
				std::string message;
				try
				{
					std::vector<DataManager::CompleteHomeworkList> homeworklist = DataManager::getHomeworkListByStuId((long)getStuInfo[qq_id].studentId, (long)getStuInfo[qq_id].classId);
					if (homeworklist.size() != 0)
					{
						for (auto& iter : homeworklist)
						{
							int status = iter.homework.getStatus();
							message += (u8"【作业 " + std::to_string(iter.assignment.getId()) + u8"】  " + getHomeworkStatus(status) + u8"  ");
							if (status == 0)//未提交
							{
								if (std::time(0) > iter.assignment.getDeadline())
								{
									message += (u8"已截止提交");
								}
								else
								{
									message += (u8"截止时间：" + TimeConvert(iter.assignment.getDeadline()));
								}
							}
							if (status == 2)//已批改
							{
								message += u8"分数：" + std::to_string(iter.homework.getScore());
							}
							message += "\r\n";
						}
					}
					else
						message = u8"暂无作业";
				}
				catch (...)
				{
					message = u8"暂无作业";
				}
				PrivateMessageSender sender(qq_id, u8"作业列表如下\r\n" + message);
				sender.send();
				return;
			}
			//进入详情查询
			int assignmentId = atoi(assignmentId_str.c_str());
			std::string message;
			try
			{
				
				DataManager::CompleteHomeworkList ch = getCH(qq_id, assignmentId);
				
				int homeworkStatus = ch.homework.getStatus();
				if (homeworkStatus == 0)//未提交
				{
					message += (u8"【作业 " + std::to_string(ch.assignment.getId()) + u8"】  " + getHomeworkStatus(homeworkStatus))+ u8"\r\n";
					message += (u8"【作业内容】\r\n" + ch.assignment.getDescription() + u8"\r\n");
					message += (u8"【截止时间】  " + TimeConvert(ch.assignment.getDeadline()) + u8"\r\n");
					PrivateMessageSender sender(qq_id, message);
					sender.send();
					return;
				}
				if (homeworkStatus == 1)//已提交
				{
					message += (u8"【作业 " + std::to_string(ch.assignment.getId()) + u8"】  " + getHomeworkStatus(homeworkStatus)) + u8"\n\n";
					message += (u8"【作业内容】\r\n" + ch.assignment.getDescription() + u8"\r\n");
					message += (u8"【截止时间】  " + TimeConvert(ch.assignment.getDeadline()) + u8"\n\n");
					message += (u8"【作业正文列表】\r\n" + getHomeworkFilename(ch.homework.getContentURL())+u8"\r\n");
					message += (u8"【作业附件列表】\r\n" + getHomeworkFilename(ch.homework.getAttachmentURL()) + u8"\r\n");
					PrivateMessageSender sender(qq_id, message);
					sender.send();
					return;
				}
				if (homeworkStatus == 2)//已批改
				{
					message += (u8"【作业 " + std::to_string(ch.assignment.getId()) + u8"】  " + getHomeworkStatus(homeworkStatus)) + u8"\n\n";
					message += (u8"【作业内容】\r\n" + ch.assignment.getDescription() + u8"\r\n");
					message += (u8"【截止时间】  " + TimeConvert(ch.assignment.getDeadline()) + u8"\n\n");
					message += (u8"【分数】 " + std::to_string(ch.homework.getScore()) + u8"\r\n");
					message += (u8"【评语】\r\n" + ch.homework.getComments() + u8"\n\n");
					message += (u8"【作业正文列表】\r\n" + getHomeworkFilename(ch.homework.getContentURL()) + u8"\r\n");
					message += (u8"【作业附件列表】\r\n" + getHomeworkFilename(ch.homework.getAttachmentURL()) + u8"\r\n");
					PrivateMessageSender sender(qq_id, message);
					sender.send();
					return;
				}
			}
			catch(DataManager::DMException::TARGET_NOT_FOUND)//无作业
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
		if (data.substr(0, 11) == u"gethomework" || data.substr(0, 11) == u"Gethomework")
		{
			std::string assignmentId_str = Tools::to_utf8(Tools::delFirstCom(data, 11));
			if (!Tools::isNum(assignmentId_str))//未检测到数字
			{
				std::string message;
				try
				{
					std::vector<DataManager::CompleteHomeworkList> homeworklist = DataManager::getHomeworkListByStuId((long)getStuInfo[qq_id].studentId, (long)getStuInfo[qq_id].classId);
					if (homeworklist.size() != 0)
					{
						for (auto& iter : homeworklist)
						{
							int status = iter.homework.getStatus();
							message += (u8"【作业 " + std::to_string(iter.assignment.getId()) + u8"】  " + getHomeworkStatus(status) + u8"  ");
							if (status == 0)//未提交
							{
								if (std::time(0) > iter.assignment.getDeadline())
								{
									message += (u8"已截止提交");
								}
								else
								{
									message += (u8"截止时间：" + TimeConvert(iter.assignment.getDeadline()));
								}
							}
							if (status == 2)//已批改
							{
								message += u8"分数：" + std::to_string(iter.homework.getScore());
							}
							message += "\r\n";
						}
					}
					else
						message = u8"暂无作业";
				}
				catch (...)
				{
					message = u8"暂无作业";
				}
				PrivateMessageSender sender(qq_id, u8"作业列表如下\r\n" + message);
				sender.send();
				return;
			}
			//进入详情查询
			int assignmentId = atoi(assignmentId_str.c_str());
			std::string message;
			try
			{

				DataManager::CompleteHomeworkList ch = getCH(qq_id, assignmentId);

				int homeworkStatus = ch.homework.getStatus();
				if (homeworkStatus == 0)//未提交
				{
					message += (u8"【作业 " + std::to_string(ch.assignment.getId()) + u8"】  " + getHomeworkStatus(homeworkStatus)) + u8"\r\n";
					message += (u8"【作业内容】\r\n" + ch.assignment.getDescription() + u8"\r\n");
					message += (u8"【截止时间】  " + TimeConvert(ch.assignment.getDeadline()) + u8"\r\n");
					PrivateMessageSender sender(qq_id, message);
					sender.send();
					return;
				}
				if (homeworkStatus == 1)//已提交
				{
					message += (u8"【作业 " + std::to_string(ch.assignment.getId()) + u8"】  " + getHomeworkStatus(homeworkStatus)) + u8"\n\n";
					message += (u8"【作业内容】\r\n" + ch.assignment.getDescription() + u8"\r\n");
					message += (u8"【截止时间】  " + TimeConvert(ch.assignment.getDeadline()) + u8"\n\n");
					message += (u8"【作业正文列表】\r\n" + getHomeworkFilename(ch.homework.getContentURL()) + u8"\r\n");
					message += (u8"【作业附件列表】\r\n" + getHomeworkFilename(ch.homework.getAttachmentURL()) + u8"\r\n");
					PrivateMessageSender sender(qq_id, message);
					sender.send();
					return;
				}
				if (homeworkStatus == 2)//已批改
				{
					message += (u8"【作业 " + std::to_string(ch.assignment.getId()) + u8"】  " + getHomeworkStatus(homeworkStatus)) + u8"\n\n";
					message += (u8"【作业内容】\r\n" + ch.assignment.getDescription() + u8"\r\n");
					message += (u8"【截止时间】  " + TimeConvert(ch.assignment.getDeadline()) + u8"\n\n");
					message += (u8"【分数】 " + std::to_string(ch.homework.getScore()) + u8"\r\n");
					message += (u8"【评语】\r\n" + ch.homework.getComments() + u8"\n\n");
					message += (u8"【作业正文列表】\r\n" + getHomeworkFilename(ch.homework.getContentURL()) + u8"\r\n");
					message += (u8"【作业附件列表】\r\n" + getHomeworkFilename(ch.homework.getAttachmentURL()) + u8"\r\n");
					PrivateMessageSender sender(qq_id, message);
					sender.send();
					return;
				}
			}
			catch (DataManager::DMException::TARGET_NOT_FOUND)//无作业
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
		if (data.substr(0, 3) == u"get" || data.substr(0, 3) == u"Get")
		{
			std::string assignmentId_str = Tools::to_utf8(Tools::delFirstCom(data, 3));
			if (!Tools::isNum(assignmentId_str))//未检测到数字
			{
				std::string message;
				try
				{
					std::vector<DataManager::CompleteHomeworkList> homeworklist = DataManager::getHomeworkListByStuId((long)getStuInfo[qq_id].studentId, (long)getStuInfo[qq_id].classId);
					if (homeworklist.size() != 0)
					{
						for (auto& iter : homeworklist)
						{
							int status = iter.homework.getStatus();
							message += (u8"【作业 " + std::to_string(iter.assignment.getId()) + u8"】  " + getHomeworkStatus(status) + u8"  ");
							if (status == 0)//未提交
							{
								if (std::time(0) > iter.assignment.getDeadline())
								{
									message += (u8"已截止提交");
								}
								else
								{
									message += (u8"截止时间：" + TimeConvert(iter.assignment.getDeadline()));
								}
							}
							if (status == 2)//已批改
							{
								message += u8"分数：" + std::to_string(iter.homework.getScore());
							}
							message += "\r\n";
						}
					}
					else
						message = u8"暂无作业";
				}
				catch (...)
				{
					message = u8"暂无作业";
				}
				PrivateMessageSender sender(qq_id, u8"作业列表如下\r\n" + message);
				sender.send();
				return;
			}
			//进入详情查询
			int assignmentId = atoi(assignmentId_str.c_str());
			std::string message;
			try
			{

				DataManager::CompleteHomeworkList ch = getCH(qq_id, assignmentId);

				int homeworkStatus = ch.homework.getStatus();
				if (homeworkStatus == 0)//未提交
				{
					message += (u8"【作业 " + std::to_string(ch.assignment.getId()) + u8"】  " + getHomeworkStatus(homeworkStatus)) + u8"\r\n";
					message += (u8"【作业内容】\r\n" + ch.assignment.getDescription() + u8"\r\n");
					message += (u8"【截止时间】  " + TimeConvert(ch.assignment.getDeadline()) + u8"\r\n");
					PrivateMessageSender sender(qq_id, message);
					sender.send();
					return;
				}
				if (homeworkStatus == 1)//已提交
				{
					message += (u8"【作业 " + std::to_string(ch.assignment.getId()) + u8"】  " + getHomeworkStatus(homeworkStatus)) + u8"\n\n";
					message += (u8"【作业内容】\r\n" + ch.assignment.getDescription() + u8"\r\n");
					message += (u8"【截止时间】  " + TimeConvert(ch.assignment.getDeadline()) + u8"\n\n");
					message += (u8"【作业正文列表】\r\n" + getHomeworkFilename(ch.homework.getContentURL()) + u8"\r\n");
					message += (u8"【作业附件列表】\r\n" + getHomeworkFilename(ch.homework.getAttachmentURL()) + u8"\r\n");
					PrivateMessageSender sender(qq_id, message);
					sender.send();
					return;
				}
				if (homeworkStatus == 2)//已批改
				{
					message += (u8"【作业 " + std::to_string(ch.assignment.getId()) + u8"】  " + getHomeworkStatus(homeworkStatus)) + u8"\n\n";
					message += (u8"【作业内容】\r\n" + ch.assignment.getDescription() + u8"\r\n");
					message += (u8"【截止时间】  " + TimeConvert(ch.assignment.getDeadline()) + u8"\n\n");
					message += (u8"【分数】 " + std::to_string(ch.homework.getScore()) + u8"\r\n");
					message += (u8"【评语】\r\n" + ch.homework.getComments() + u8"\n\n");
					message += (u8"【作业正文列表】\r\n" + getHomeworkFilename(ch.homework.getContentURL()) + u8"\r\n");
					message += (u8"【作业附件列表】\r\n" + getHomeworkFilename(ch.homework.getAttachmentURL()) + u8"\r\n");
					PrivateMessageSender sender(qq_id, message);
					sender.send();
					return;
				}
			}
			catch (DataManager::DMException::TARGET_NOT_FOUND)//无作业
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

		//提交&修改作业
		if (data.substr(0, 4) == u"提交作业"|| data.substr(0, 4) == u"修改作业")
		{
			std::string assignmentId_str = Tools::to_utf8(Tools::delFirstCom(data, 4));
			if (!Tools::isNum(assignmentId_str)|| assignmentId_str=="")
			{
				PrivateMessageSender sender(qq_id, u8"未知命令，请重试");
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
					PrivateMessageSender sender(qq_id, u8"作业提交已截止");
					sender.send();
					status[qq_id] = PeerStatus::IDLE;
					return;
				}
				PrivateMessageSender sender(qq_id, u8"已新建作业");
				sender.send();

				HomeworkInfo info;
				info.classId = st.getClassId();
				info.homeworkId = assignmentId;
				info.studentId = getStuInfo[qq_id].studentId;
				info.studentNum = atoll(st.getSchoolNum().c_str());
				if (getHomeworkInfo.count(qq_id))
					getHomeworkInfo.erase(qq_id);
				getHomeworkInfo.insert(std::pair<long long, HomeworkInfo>(qq_id, info));
				PrivateMessageSender sender2(qq_id, u8"开始提交作业" + std::to_string(info.homeworkId) + u8"\r\n结束后，输入“确认提交”以提交，输入“取消提交”以取消");
				sender2.send();

				File file(info);
				std::string filelist = file.getFileList();
				if (filelist != u8"暂无文件")
				{
					PrivateMessageSender sender(qq_id, u8"已检测到草稿\n" + filelist);
					sender.send();
				}

				return;
			}
			catch (DataManager::DMException::TARGET_NOT_FOUND)
			{
				status[qq_id] = PeerStatus::IDLE;
				PrivateMessageSender sender(qq_id, u8"暂无该作业，请重试");
				sender.send();
				return;
			}
		}
		if (data.substr(0, 6) == u"Submit" || data.substr(0, 6) == u"submit" || data.substr(0, 6) == u"Modify" || data.substr(0, 6) == u"modify")
		{
			std::string assignmentId_str = Tools::to_utf8(Tools::delFirstCom(data, 6));
			if (!Tools::isNum(assignmentId_str) || assignmentId_str == "")
			{
				PrivateMessageSender sender(qq_id, u8"未知命令，请重试");
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
					PrivateMessageSender sender(qq_id, u8"作业提交已截止");
					sender.send();
					status[qq_id] = PeerStatus::IDLE;
					return;
				}
				PrivateMessageSender sender(qq_id, u8"已新建作业");
				sender.send();

				HomeworkInfo info;
				info.classId = st.getClassId();
				info.homeworkId = assignmentId;
				info.studentId = getStuInfo[qq_id].studentId;
				info.studentNum = atoll(st.getSchoolNum().c_str());
				if (getHomeworkInfo.count(qq_id))
					getHomeworkInfo.erase(qq_id);
				getHomeworkInfo.insert(std::pair<long long, HomeworkInfo>(qq_id, info));
				PrivateMessageSender sender2(qq_id, u8"开始提交作业" + std::to_string(info.homeworkId) + u8"\r\n结束后，输入“确认提交”以提交，输入“取消提交”以取消");
				sender2.send();

				File file(info);
				std::string filelist = file.getFileList();
				if (filelist != u8"暂无文件")
				{
					PrivateMessageSender sender(qq_id, u8"已检测到草稿\n" + filelist);
					sender.send();
				}

				return;
			}
			catch (DataManager::DMException::TARGET_NOT_FOUND)
			{
				status[qq_id] = PeerStatus::IDLE;
				PrivateMessageSender sender(qq_id, u8"暂无该作业，请重试");
				sender.send();
				return;
			}
		}
	}

	PrivateMessageSender sender(qq_id, u8"未知命令，请重试\n输入“帮助”以获得命令列表");
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

	if (data == u"取消注册" || data == u"取消" || data == u"Cancel" || data == u"cancel")
	{
		PrivateMessageSender sender(qq_id, u8"已取消注册");
		sender.send();
		regStatus.erase(qq_id);
		status[qq_id] = PeerStatus::IDLE;
		return;
	}
	if (data == u"帮助" || data == u"Help" || data == u"help")
	{
		PrivateMessageSender sender(qq_id, regHelper);
		sender.send();
		return;
	}
	if (regInfo.status == RegStatus::START)
	{
		PrivateMessageSender sender1(qq_id, u8"开始注册，输入“取消”即可退出注册\n\n请输入课程邀请码");
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
			std::string classInfo = u8"您即将加入："+cl.getName()+u8"\n\n请输入姓名";
			PrivateMessageSender sender(qq_id, classInfo);
			sender.send();
			regInfo.status = RegStatus::NAME;
			regInfo.classId = cl.getId();
			regStatus[qq_id] = regInfo;
			return;
		}
		
		catch(DataManager::DMError)
		{
			PrivateMessageSender sender(qq_id, u8"未知课程邀请码，请重试");
			sender.send();
			return;
		}
		
	}

	if (regInfo.status == RegStatus::NAME)
	{
		std::u16string name = data.substr(0, data.find_first_of(u" "));
		if (name.length() < 1 || name.length() > 20)
		{
			PrivateMessageSender sender(qq_id, u8"非法姓名，请重新输入");
			sender.send();
			return;
		}
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
			PrivateMessageSender sender(qq_id, u8"学号格式错误，请重新输入");
			sender.send();
			return;
		}

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
			st.setClassId((long)regInfo.classId);
		}
		catch(DataManager::DMError)
		{
			PrivateMessageSender sender(qq_id, u8"注册失败，请重试");
			sender.send();
			regStatus.erase(qq_id);
			status[qq_id] = PeerStatus::UNREG;
			return;
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
	if (data == u"取消"|| data == u"取消提交"|| data == u"Cancel"||data == u"cancel")
	{
		PrivateMessageSender sender(qq_id, u8"您已取消提交作业" + std::to_string(getHomeworkInfo[qq_id].homeworkId)+u8"\n当前草稿已保存");
		sender.send();
		status[qq_id] = PeerStatus::IDLE;
		getHomeworkInfo.erase(qq_id);
		return;
	}
	if (data == u"帮助" || data == u"Help" || data == u"help")
	{
		PrivateMessageSender sender(qq_id, homHelper1+std::to_string(getHomeworkInfo[qq_id].homeworkId)+homHelper2);
		sender.send();
		return;
	}
	if (data == u"全部删除" || data == u"清空文件" || data == u"Deleteall" || data == u"deleteall")
	{
		File file(getHomeworkInfo.at(qq_id));
		file.delAll();
		PrivateMessageSender sender(qq_id, u8"文件已清空");
		sender.send();
		return;
	}
	if (data.substr(0, 4) == u"删除文件")
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
	if (data.substr(0, 2) == u"删除")
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
	if (data == u"获取文件列表"|| data == u"查询文件列表" || data == u"Getlist" || data == u"getlist")
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
	if (data.substr(0, 2) == u"获取" || data.substr(0, 2) == u"查询")
	{
		std::u16string tmp = Tools::delFirstCom(data, 2);
		File file(getHomeworkInfo[qq_id]);
		PrivateMessageSender sender(qq_id, file.getFile(tmp));
		sender.send();
		return;
	}
	if (data.substr(0, 4) == u"获取文件" || data.substr(0, 4) == u"查询文件")
	{
		std::u16string tmp = Tools::delFirstCom(data, 4);
		File file(getHomeworkInfo[qq_id]);
		PrivateMessageSender sender(qq_id, file.getFile(tmp));
		sender.send();
		return;
	}
	
	if (data == u"提交作业" || data == u"确认提交" || data == u"提交" || data == u"Submit" || data == u"submit")
	{
		File file(getHomeworkInfo[qq_id]);
		try
		{
			DataManager::Homework hm((long)getStuInfo[qq_id].studentId, (long)getHomeworkInfo[qq_id].homeworkId);
			if (file.save(hm.getId()))//上传成功
			{
				hm.submit(file.getContentFile(), file.getAttachmentFile());
				status[qq_id] = PeerStatus::IDLE;
				PrivateMessageSender sender(qq_id, u8"提交成功");
				sender.send();
				return;
			}
			else
			{
				DataManager::deleteHomework(hm.getId());
				PrivateMessageSender sender(qq_id, u8"提交失败");
				sender.send();
				return;
			}
		}
		catch (DataManager::DMException::TARGET_EXISTED)
		{
			long long submitId = file.getSubmitId();
			DataManager::Homework hm((long)submitId);
			if (file.save(submitId))//上传成功
			{
				hm.submit(file.getContentFile(), file.getAttachmentFile());
				status[qq_id] = PeerStatus::IDLE;
				PrivateMessageSender sender(qq_id, u8"提交成功");
				sender.send();
				return;
			}
			else
			{
				DataManager::deleteHomework(hm.getId());
				PrivateMessageSender sender(qq_id, u8"提交失败");
				sender.send();
				return;
			}
		}
		catch (...)
		{
			PrivateMessageSender sender(qq_id, u8"提交失败");
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
			//msg.replace(msg.find(posCQ->str()), posCQ->str().length(), fileName);
			PrivateMessageSender sender(qq_id, u8"图片：" + fileName + u8" 已保存");
			sender.send();
		}

		File file(getHomeworkInfo[qq_id]);
		std::string fileName = file.storeText(msg);
		PrivateMessageSender sender(qq_id, u8"文本：" + fileName + u8" 已保存");
		sender.send();
		return;
	}
	catch (...)
	{
		PrivateMessageSender sender(qq_id, u8"保存失败，请重试");
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
			PrivateMessageSender sender(qq_id, u8"文件：" + filename + u8" 已接收");
			sender.send();
			return;
		}
		else
		{
			PrivateMessageSender sender(qq_id, u8"文件接收失败，请重试");
			sender.send();
			return;
		}
	}
	else
	{
		PrivateMessageSender sender(qq_id, u8"非作业模式下不允许提交文件");
		sender.send();
		return;
	}
}

bool sendReview(long homeworkId)
{
	std::string msg = u8"未知消息";
	try
	{
		DataManager::Homework hm(homeworkId);
		DataManager::Assignment as(hm.getAssignmentId());
		DataManager::Student st(hm.getStudentId());

		long long qq_id = atoll(st.getQQ().c_str());
		std::string msg = u8"您提交的作业 " + std::to_string(as.getId()) + u8"已批改\n\n【分数】 " + std::to_string(hm.getScore()) + u8"\n【评语】\n" + hm.getComments();
		PrivateMessageSender sender(qq_id, msg);
		sender.send();
		return true;
	}
	catch (...)
	{
		return false;
	}
}

void sendHomeworkNotification(long long assignmentId,int mode)
{
	auto assignment = DataManager::Assignment((unsigned long)assignmentId);
	auto studentList = DataManager::getStudentList(assignment.getClassId());
	for (auto& iter : studentList)
	{
		if (mode == 1)
		{
			std::string message = u8"您收到了新的作业  ";
			message += (u8"【作业 " + std::to_string(assignmentId) + u8"】" + u8"\r\n");
			message += (u8"【作业内容】\r\n" + assignment.getDescription() + u8"\r\n");
			message += (u8"【截止时间】  " + TimeConvert(assignment.getDeadline()) + u8"\r\n");
			PrivateMessageSender sender(atoll(iter.getQQ().c_str()), message);
			sender.send();
		}
	}
}
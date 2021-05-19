#include <string>
#include <iostream>
#include <map>
#include <sstream>
#include <stdlib.h>
#include "Tools.h"
#include "PrivateMessageSender.h"
#include "Analyst.h"
#include <DataManager.hpp>

extern std::string connectUrl;
extern std::map<long long, PeerStatus> status;
extern std::map<long long, RegInfo> regStatus;
extern std::map<long long, long long> getStudentId;

extern WebsocketClient wsClient;

void RegCommand(std::u16string data, long long qq_id);
void HomCommand(std::u16string data, long long qq_id);

void AnaText(std::u16string data, long long qq_id)
{
	typedef std::pair<long long, PeerStatus> pair;
	std::u16string subCom, retInfo;

	if (!status.count(qq_id)) status.insert(pair(qq_id, PeerStatus::IDLE));//添加当前状态

	if ((status[qq_id] != PeerStatus::REGISTER)&&!getStudentId.count(qq_id) && (status[qq_id] != PeerStatus::UNREG))
	{
		long long sid;
		try
		{
			DataManager::Student st=DataManager::getStudent(std::to_string(qq_id));
			sid = st.getId();
			getStudentId.insert(std::pair<long long, long long>(qq_id, sid));
		}
		catch (DataManager::DMError& e)
		{
			status[qq_id] = PeerStatus::UNREG;
		}
	}


	if (status[qq_id] == PeerStatus::REGISTER)//注册中
	{
		subCom = data;
		Tools::delSpaceAhead(subCom);
		RegCommand(subCom, qq_id);
		return;
	}

	if (status[qq_id] == PeerStatus::HOMEWORK)//提交作业中
	{
		subCom = data;
		Tools::delSpaceAhead(subCom);
		HomCommand(subCom, qq_id);
		return;
	}

	if (data.substr(0, 2) == u"注册")//开始注册
	{
		if (status[qq_id] == PeerStatus::UNREG)
			status[qq_id] = PeerStatus::REGISTER;
		if (getStudentId.count(qq_id))
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

	if (status[qq_id] == PeerStatus::UNREG)//未注册
	{
		PrivateMessageSender sender(qq_id, u8"未注册账号，请输入注册以开始");
		sender.send();
		return;
	}

	if (status[qq_id] == PeerStatus::IDLE)
	{
		if (data.substr(0, 6) == u"查询个人信息")//TODO:查询个人信息 数据库 返回班级、老师、姓名、学号
		{
			DataManager::Student st = DataManager::getStudent(getStudentId[qq_id]);
			DataManager::Class cl = DataManager::getClass(st.getClassId());
			std::string send = u8"您的个人信息如下\n\r姓名：" + st.getName() + u8"\n\r学号：" + st.getSchoolNum() + u8"\n\r班级：" + cl.getName() + u8"\n\r老师：";
			PrivateMessageSender sender(qq_id, send);
			sender.send();
			return;
		}

		
		if (data.substr(0, 4) == u"查询作业")//TODO:查询作业（n）：状态【0未完成 1已提交 2已批改】，分数，评语，作业内容，正文，附件表
		{
			std::string homewordId_str = Tools::to_utf8(Tools::delFirstCom(data, 4));
			if (!Tools::isNum(homewordId_str))
			{
				PrivateMessageSender sender(qq_id, u8"作业列表如下");//TODO: vector 遍历 未完成：
				{

				}
				sender.send();
				return;
			}
#include <stdlib.h>
			int homeworkID = atoi(homewordId_str.c_str());
			
			int homeworkStatus=0;
			if (homeworkStatus == -1)//无作业
			{
				PrivateMessageSender sender(qq_id, u8"暂无该作业，请重试");
				sender.send();
				return;
			}
			if (homeworkStatus == 0)//未提交
			{
				
				return;
			}
			if (homeworkStatus == 1)//已提交
			{

				return;
			}
			if (homeworkStatus == 2)//已批改
			{

				return;
			}
			return;
		}

		if (data.substr(0, 4) == u"提交作业" || data.substr(0, 4) == u"修改作业")
		{
			std::string homewordId_str = Tools::to_utf8(Tools::delFirstCom(data, 4));
			if (!Tools::isNum(homewordId_str))
			{
				PrivateMessageSender sender(qq_id, u8"未知命令，请重试");
				sender.send();
				return;
			}
#include <stdlib.h>
			int homeworkID = atoi(homewordId_str.c_str());

			int homeworkStatus=0;
			if (homeworkStatus == -1)//无作业
			{
				PrivateMessageSender sender(qq_id, u8"暂无该作业，请重试");
				sender.send();
				return;
			}
			if (homeworkStatus == 0)//未提交
			{

				return;
			}
			if (homeworkStatus == 1)//已提交
			{

				return;
			}
			if (homeworkStatus == 2)//已批改
			{

				return;
			}
			return;
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
			DataManager::Student st;
			st.reg(std::to_string(regInfo.schoolId), std::to_string(qq_id), regInfo.name);
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
		getStudentId[qq_id] = regInfo.schoolId;
		return;
	}
}

void HomCommand(std::u16string data, long long qq_id)
{
	
}
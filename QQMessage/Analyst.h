#pragma once
#include <string>
#include "WebsocketClient.h"

/// <summary>
/// 共用枚举类型
/// <para>
/// 一级菜单主状态记录
/// </para>
/// </summary>
enum class PeerStatus {
	/// <summary>
	/// 空闲
	/// </summary>
	IDLE,
	/// <summary>
	/// 注册中
	/// </summary>
	REGISTER,
	/// <summary>
	/// 提交作业中
	/// </summary>
	HOMEWORK,
	/// <summary>
	/// 未注册
	/// </summary>
	UNREG
};

/// <summary>
/// 共用枚举类型
/// <para>
/// 二级菜单注册状态记录
/// </para>
/// </summary>
enum class RegStatus {
	/// <summary>
	/// 开始注册
	/// </summary>
	START,
	/// <summary>
	/// 提交班级邀请码
	/// </summary>
	CLASS,
	/// <summary>
	/// 提交学号
	/// </summary>
	NUM,
	/// <summary>
	/// 提交姓名
	/// </summary>
	NAME,
	/// <summary>
	/// 确认
	/// </summary>
	CONFIRM
};
/// <summary>
/// 共用结构体
/// <para>
/// 记录注册信息，便于发送
/// </para>
/// </summary>
struct RegInfo
{
	/// <summary>
	/// 注册状态
	/// </summary>
	RegStatus status = RegStatus::START;
	/// <summary>
	/// 姓名
	/// </summary>
	std::string name;
	/// <summary>
	/// 班级ID
	/// </summary>
	long long classId;
	/// <summary>
	/// 学号
	/// </summary>
	long long schoolId;
};
/// <summary>
/// 作业提交详情
/// </summary>
struct HomeworkInfo
{
	/// <summary>
	/// 学生id
	/// </summary>
	long long studentId;
	/// <summary>
	/// 学号
	/// </summary>
	long long studentNum;
	/// <summary>
	/// 班级id
	/// </summary>
	long long classId;

	/// <summary>
	/// 作业id
	/// </summary>
	long long homeworkId;
	/// <summary>
	/// 提交id
	/// </summary>
	long long submitId;
};
/// <summary>
/// 私聊消息发送
/// </summary>
class PrivateMessageSender;

/// <summary>
/// 检测输入文本【一级菜单】
/// </summary>
/// <param name="data">聊天消息</param>
/// <param name="qq_id">对象qq</param>
void AnaText(std::u16string data, long long qq_id);

/// <summary>
/// 注册【二级菜单】
/// </summary>
/// <param name="data">聊天消息</param>
/// <param name="qq_id">对象qq</param>
void RegCommand(std::u16string data, long long qq_id);
/// <summary>
/// 作业【二级菜单】
/// </summary>
/// <param name="data">聊天消息</param>
/// <param name="qq_id">对象qq</param>
void HomCommand(std::u16string data, long long qq_id);
#pragma once
#include <string>
#include "WebsocketClient.h"

/// <summary>
/// ����ö������
/// <para>
/// һ���˵���״̬��¼
/// </para>
/// </summary>
enum class PeerStatus {
	/// <summary>
	/// ����
	/// </summary>
	IDLE,
	/// <summary>
	/// ע����
	/// </summary>
	REGISTER,
	/// <summary>
	/// �ύ��ҵ��
	/// </summary>
	HOMEWORK,
	/// <summary>
	/// δע��
	/// </summary>
	UNREG
};

/// <summary>
/// ����ö������
/// <para>
/// �����˵�ע��״̬��¼
/// </para>
/// </summary>
enum class RegStatus {
	/// <summary>
	/// ��ʼע��
	/// </summary>
	START,
	/// <summary>
	/// �ύ�༶������
	/// </summary>
	CLASS,
	/// <summary>
	/// �ύѧ��
	/// </summary>
	NUM,
	/// <summary>
	/// �ύ����
	/// </summary>
	NAME,
	/// <summary>
	/// ȷ��
	/// </summary>
	CONFIRM
};
/// <summary>
/// ���ýṹ��
/// <para>
/// ��¼ע����Ϣ�����ڷ���
/// </para>
/// </summary>
struct RegInfo
{
	/// <summary>
	/// ע��״̬
	/// </summary>
	RegStatus status = RegStatus::START;
	/// <summary>
	/// ����
	/// </summary>
	std::string name;
	/// <summary>
	/// �༶ID
	/// </summary>
	long long classId;
	/// <summary>
	/// ѧ��
	/// </summary>
	long long schoolId;
};
/// <summary>
/// ��ҵ�ύ����
/// </summary>
struct HomeworkInfo
{
	/// <summary>
	/// ѧ��id
	/// </summary>
	long long studentId;
	/// <summary>
	/// ѧ��
	/// </summary>
	long long studentNum;
	/// <summary>
	/// �༶id
	/// </summary>
	long long classId;

	/// <summary>
	/// ��ҵid
	/// </summary>
	long long homeworkId;
	/// <summary>
	/// �ύid
	/// </summary>
	long long submitId;
};
/// <summary>
/// ˽����Ϣ����
/// </summary>
class PrivateMessageSender;

/// <summary>
/// ��������ı���һ���˵���
/// </summary>
/// <param name="data">������Ϣ</param>
/// <param name="qq_id">����qq</param>
void AnaText(std::u16string data, long long qq_id);

/// <summary>
/// ע�᡾�����˵���
/// </summary>
/// <param name="data">������Ϣ</param>
/// <param name="qq_id">����qq</param>
void RegCommand(std::u16string data, long long qq_id);
/// <summary>
/// ��ҵ�������˵���
/// </summary>
/// <param name="data">������Ϣ</param>
/// <param name="qq_id">����qq</param>
void HomCommand(std::u16string data, long long qq_id);
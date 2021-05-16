#pragma once
#include <string>
/// <summary>
/// ˽����Ϣ����
/// </summary>
class PrivateMessageSender
{
private:
	/// <summary>
	/// ���͵���Ϣ
	/// </summary>
	std::string data;
	/// <summary>
	/// ������qq
	/// </summary>
	long long targetId;
public:
	/// <summary>
	/// ��ʼ����Ϣ����
	/// </summary>
	/// <param name="targetId">������qq</param>
	/// <param name="data">����</param>
	PrivateMessageSender(long long targetId, std::string data);
	/// <summary>
	/// ���÷��͵���Ϣ
	/// </summary>
	/// <param name="data">����</param>
	void setContent(std::string data);
	/// <summary>
	/// ����
	/// </summary>
	void send();
};
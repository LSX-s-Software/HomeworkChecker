#pragma once
#include "Analyst.h"
#include "WebsocketServer.h"

/// <summary>
/// ��̬��
/// <para>����QQ��Ϣ</para>
/// </summary>
class QQMessage {
public:
	/// <summary>
	/// �ص�����Open
	/// </summary>
	static void onOpen();
	/// <summary>
	/// �ص�����Close
	/// </summary>
	static void onClose();
	/// <summary>
	/// �ص�����Fail
	/// </summary>
	static void onFail();
	/// <summary>
	/// �ص�����Message
	/// </summary>
	/// <param name="message">��ȡ����Ϣ</param>
	static void readMessage(const std::string& message);
	/// <summary>
	/// ��ʼ������
	/// </summary>
	/// <param name="url">����ip:�˿�</param>
	static void _Init(std::string url = "127.0.0.1:6700");
	/// <summary>
	/// �ر�����
	/// </summary>
	static void _Stop();
};


#pragma once

/// <summary>
/// ���߼�
/// </summary>
class Tools
{
public:
	/// <summary>
	/// utf8תutf16
	/// </summary>
	/// <param name="str">utf8�ִ�</param>
	/// <returns>utf16�ִ�</returns>
	static std::u16string to_utf16(std::string str);

	/// <summary>
	/// utf16תutf8
	/// </summary>
	/// <param name="str">utf16�ִ�</param>
	/// <returns>utf8�ִ�</returns>
	static std::string to_utf8(std::u16string str16);
	/// <summary>
	/// ����Ƿ�Ϊ����
	/// </summary>
	/// <param name="str">utf8�ַ���</param>
	/// <returns></returns>
	static bool isNum(std::string str);
	/// <summary>
	/// ɾ��ǰ�˶���ո�
	/// </summary>
	/// <param name="x">utf16�ַ���</param>
	static void delSpaceAhead(std::u16string& x);
	/// <summary>
	/// ɾ��ǰ������
	/// </summary>
	/// <param name="data">ԭʼutf16��Ϣ</param>
	/// <param name="data">ǰ�������</param>
	/// <returns>������Ϣ</returns>
	static std::u16string delFirstCom(std::u16string data,int len);
};

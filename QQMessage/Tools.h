#pragma once

/// <summary>
/// 工具集
/// </summary>
class Tools
{
public:
	/// <summary>
	/// utf8转utf16
	/// </summary>
	/// <param name="str">utf8字串</param>
	/// <returns>utf16字串</returns>
	static std::u16string to_utf16(std::string str);

	/// <summary>
	/// utf16转utf8
	/// </summary>
	/// <param name="str">utf16字串</param>
	/// <returns>utf8字串</returns>
	static std::string to_utf8(std::u16string str16);
	/// <summary>
	/// 检测是否为数字
	/// </summary>
	/// <param name="str">utf8字符串</param>
	/// <returns></returns>
	static bool isNum(std::string str);
	/// <summary>
	/// 删除前端多余空格
	/// </summary>
	/// <param name="x">utf16字符串</param>
	static void delSpaceAhead(std::u16string& x);
	/// <summary>
	/// 删除前序命令
	/// </summary>
	/// <param name="data">原始utf16消息</param>
	/// <param name="data">前序命令长度</param>
	/// <returns>二级消息</returns>
	static std::u16string delFirstCom(std::u16string data,int len);
};

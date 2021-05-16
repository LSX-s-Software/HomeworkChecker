#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <locale>
#include <codecvt>
#include <chrono>
#include "Tools.h"

std::u16string Tools::to_utf16(std::string str)
{
	return std::wstring_convert< std::codecvt_utf8_utf16<char16_t>, char16_t >{}.from_bytes(str);
}

std::string Tools::to_utf8(std::u16string str16)
{
	return std::wstring_convert< std::codecvt_utf8_utf16<char16_t>, char16_t >{}.to_bytes(str16);
}

bool Tools::isNum(std::string str)
{
	std::stringstream sin(str);
	double d;
	char c;
	if (!(sin >> d))
	{
		return false;
	}
	if (sin >> c)
	{
		return false;
	}
	return true;
}

void Tools::delSpaceAhead(std::u16string& x)
{
	while (x.substr(0, 1) == u" ")
	{
		x = x.substr(1, x.length() - 1);
	}
	return;
}

std::u16string Tools::delFirstCom(std::u16string data,int len)
{
	std::u16string subCom = data.substr(len, data.length() - len);
	Tools::delSpaceAhead(subCom);
	return subCom;
}

long long Tools::getTimestamp()
{
	auto timeNow = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	return timeNow.count();
}
#pragma once
#include <string>
#include <iostream>
#include <locale>
#include <codecvt>
static class Tools
{
public:
	static std::u16string to_utf16(std::string str);

	static std::string to_utf8(std::u16string str16);
};

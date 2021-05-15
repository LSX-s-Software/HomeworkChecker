#include "Tools.h"

std::u16string Tools::to_utf16(std::string str)
{
	return std::wstring_convert< std::codecvt_utf8_utf16<char16_t>, char16_t >{}.from_bytes(str);
}

std::string Tools::to_utf8(std::u16string str16)
{
	return std::wstring_convert< std::codecvt_utf8_utf16<char16_t>, char16_t >{}.to_bytes(str16);
}
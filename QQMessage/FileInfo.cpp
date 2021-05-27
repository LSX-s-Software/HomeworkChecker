#include "FileInfo.h"
#include <string>
#include <iostream>
#include <algorithm>

FileInfo::FileInfo(std::filesystem::path filePath)
{
	this->filePath = filePath;
	fileName = filePath.filename();
	std::string fileExt = fileName.string().substr(fileName.string().find_last_of(".") + 1);
	std::transform(fileExt.begin(), fileExt.end(), fileExt.begin(), tolower);
	if (fileExt == "txt")
		fileFormats = FileFormats::TXT;
	else if (fileExt == "bmp" || fileExt == "jpg" || fileExt == "jpeg" || fileExt == "png" || fileExt == "gif" || fileExt == "webp")
		fileFormats = FileFormats::PIC;
	else if (fileExt == "h" || fileExt == "hpp" || fileExt == "hxx" || fileExt == "c" || fileExt == "cpp" || fileExt == "c++" || fileExt == "c" || fileExt == "cxx")
		fileFormats = FileFormats::CODE;
	else
		fileFormats = FileFormats::OTHER;
}

FileFormats FileInfo::getFileFormats()
{
	return fileFormats;
}

std::filesystem::path FileInfo::getFileName()
{
	return fileName;
}

std::filesystem::path FileInfo::getFilePath()
{
	return filePath;
}
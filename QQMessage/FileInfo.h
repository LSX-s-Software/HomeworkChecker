#pragma once
#include <filesystem>

enum class FileFormats
{
	TXT,
	PIC,
	CODE,
	OTHER
};

class FileInfo
{
private:
	std::filesystem::path filePath;
	std::filesystem::path fileName;
	FileFormats fileFormats;
public:
	FileInfo(std::filesystem::path filePath);

	std::filesystem::path getFilePath();
	std::filesystem::path getFileName();
	FileFormats getFileFormats();
};


#include "File.h"
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "FileInfo.h"
#include "Exception.h"
#include "Tools.h"

#pragma comment(lib, "urlmon.lib")

extern std::string rootPath;

File::File(long long classId, long long schoolId, long long homeworkId, long long submitId) :
	classId(classId), schoolId(schoolId), homeworkId(homeworkId), submitId(submitId),lastId(-1)
{
	workPath = rootPath;
	workPath.append(std::to_string(classId)).append(std::to_string(schoolId)).append(std::to_string(homeworkId));
	homePath = workPath;
	workPath.append(std::to_string(submitId));
	infoPath = workPath;
	infoPath.append(".info");
	try
	{
		create_directories(workPath);

		if (std::filesystem::exists(infoPath))
		{
			std::ifstream in;
			in.open(infoPath);
			in >> autoIndex >> lastId;
			in.close();
			std::ofstream out;
			out.open(infoPath, std::ios::trunc);
			out << autoIndex << std::endl << lastId << std::endl;
			out.close();
		}
		else
		{
			std::ofstream out;
			out.open(infoPath, std::ios::trunc);
			out << autoIndex << std::endl << lastId << std::endl;
			out.close();
		}
	}
	catch (std::exception& e)
	{
		throw FileError(e.what());
	}
}

File::File(HomeworkInfo info)
	:
	classId(info.classId), schoolId(info.studentNum), homeworkId(info.homeworkId), submitId(info.submitId), lastId(-1)
{
	workPath = rootPath;
	workPath.append(std::to_string(classId)).append(std::to_string(schoolId)).append(std::to_string(homeworkId));
	homePath = workPath;
	workPath.append(std::to_string(submitId));
	infoPath = workPath;
	infoPath.append(".info");
	try
	{
		create_directories(workPath);

		if (std::filesystem::exists(infoPath))
		{
			std::ifstream in;
			in.open(infoPath);
			in >> autoIndex >> lastId;
			in.close();
			std::ofstream out;
			out.open(infoPath, std::ios::trunc);
			out << autoIndex << std::endl << lastId << std::endl;
			out.close();
		}
		else
		{
			std::ofstream out;
			out.open(infoPath, std::ios::trunc);
			out << autoIndex << std::endl << lastId << std::endl;
			out.close();
		}
	}
	catch (std::exception& e)
	{
		throw FileError(e.what());
	}
}

File::File(long long classId, long long schoolId, long long homeworkId, long long submitId,long long lastId) :
	classId(classId), schoolId(schoolId), homeworkId(homeworkId), submitId(submitId),lastId(lastId)
{
	workPath = rootPath;
	workPath.append(std::to_string(classId)).append(std::to_string(schoolId)).append(std::to_string(homeworkId));
	homePath = workPath;
	std::filesystem::path lastPath = homePath;
	lastPath.append(std::to_string(lastId));
	workPath.append(std::to_string(submitId));
	infoPath = workPath;
	infoPath.append(".info");
	try
	{
		std::filesystem::copy(lastPath, workPath);
		if (std::filesystem::exists(infoPath))
		{
			std::ifstream in;
			in.open(infoPath);
			in >> autoIndex;
			in.close();
			std::ofstream out;
			out.open(infoPath, std::ios::trunc);
			out << autoIndex << std::endl << lastId << std::endl;
			out.close();
		}
		else
		{
			std::ofstream out;
			out.open(infoPath, std::ios::trunc);
			out << autoIndex << std::endl << lastId << std::endl;
			out.close();
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what();
		throw FileError(e.what());
	}
}

std::string File::storeText(std::string data)
{
	std::filesystem::path fileName = std::to_string(autoIndex)+".txt";
	while (std::filesystem::exists(workPath / fileName))
	{
		autoIndex++;
		fileName = std::to_string(autoIndex) + ".txt";
	}
	try
	{
		std::ofstream out;
		out.open(workPath / fileName, std::ios::trunc);
		out << data;
		out.close();
		autoIndex++;
		return fileName.string();
	}
	catch (std::exception& e)
	{
		throw FileError("cannot store file:" + (workPath / fileName).string() + "\n" + e.what());
	}
	
}

std::string File::delFile(std::filesystem::path fileName)
{
	if (!std::filesystem::exists(workPath / fileName)) throw FileNotExist((workPath / fileName).string());
	try
	{
		std::filesystem::remove(workPath / fileName);
	}
	catch (std::exception& e)
	{
		return u8"无法找到文件：" + fileName.string() + " 请重试";
	}
	return u8"成功删除文件：" + fileName.string();
}

LPCWSTR stringToLPCWSTR(std::string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t* wcstring = (wchar_t*)malloc(sizeof(wchar_t) * (orig.length() - 1));
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);

	return wcstring;
}

std::string File::downFile(std::string url, std::filesystem::path fileName)
{
	if (std::filesystem::exists(workPath / fileName))
	{
		fileName = fileName.stem().string() + std::to_string(Tools::getTimestamp()) + "." + fileName.string().substr(fileName.string().find_last_of(".") + 1);
	}
	URLDownloadToFile(NULL, stringToLPCWSTR(url), stringToLPCWSTR((workPath / fileName).string()), 0, NULL);
	return fileName.string();
}

std::string File::storePic(std::string url)
{
	std::filesystem::path fileName = std::to_string(autoIndex) + ".png";
	while (std::filesystem::exists(workPath / fileName))
	{
		autoIndex++;
		fileName = std::to_string(autoIndex) + ".png";
	}
	try
	{
		downFile(url, fileName);
		autoIndex++;
		return fileName.string();
	}
	catch (std::exception& e)
	{
		throw FileError("cannot store file:" + (workPath / fileName).string() + "\n" + e.what());
	}

}

bool File::save()
{
	if (!std::filesystem::exists(infoPath))
	{
		return false;
	}

	std::ifstream in;
	in.open(infoPath);
	in >> autoIndex >> lastId;
	in.close();

	int cnt = 0;
	std::vector<std::string> txtFile, picFile, codeFile, otherFile;
	for (auto& iter : std::filesystem::directory_iterator(workPath))
	{
		if (iter.path().filename().string() == ".info") continue;
		cnt++;
		FileInfo fileInfo(iter.path());
		switch (fileInfo.getFileFormats())
		{
		case(FileFormats::TXT):
			txtFile.push_back(fileInfo.getFileName().string());
			break;
		case(FileFormats::PIC):
			picFile.push_back(fileInfo.getFileName().string());
			break;
		case(FileFormats::CODE):
			codeFile.push_back(fileInfo.getFileName().string());
			break;
		case(FileFormats::OTHER):
			otherFile.push_back(fileInfo.getFileName().string());
			break;
		default:
			break;
		}
	}
	if (cnt == 0)
	{
		std::filesystem::remove_all(workPath);
		return false;
	}
	std::ofstream out;
	out.open(infoPath, std::ios::trunc);
	out << autoIndex << std::endl << lastId << std::endl;
	out << "__TXT__" << std::endl;
	for (auto& iter : txtFile)
	{
		out << iter << " ";
	}
	out << std::endl << "__PIC__" << std::endl;
	for (auto& iter : picFile)
	{
		out << iter << " ";
	}
	out << std::endl << "__CODE__" << std::endl;
	for (auto& iter : codeFile)
	{
		out << iter << " ";
	}
	out << std::endl << "__OHTER__" << std::endl;
	for (auto& iter : otherFile)
	{
		out << iter << " ";
	}
	out.close();
	return true;
}

std::string File::getFileList()
{
	int cnt = 0;
	std::vector<std::string> txtFile, picFile, codeFile, otherFile;
	for (auto& iter : std::filesystem::directory_iterator(workPath))
	{
		if (iter.path().filename().string() == ".info") continue;
		cnt++;
		FileInfo fileInfo(iter.path());
		switch (fileInfo.getFileFormats())
		{
		case(FileFormats::TXT):
			txtFile.push_back(fileInfo.getFileName().string());
			break;
		case(FileFormats::PIC):
			picFile.push_back(fileInfo.getFileName().string());
			break;
		case(FileFormats::CODE):
			codeFile.push_back(fileInfo.getFileName().string());
			break;
		case(FileFormats::OTHER):
			otherFile.push_back(fileInfo.getFileName().string());
			break;
		default:
			break;
		}
	}
	if (cnt == 0)
	{
		std::filesystem::remove_all(workPath);
		return u8"暂无文件";
	}
	std::string returnString;
	if (txtFile.size() != 0)
	{
		returnString += u8"正文：\r\n";
		for (auto& iter : txtFile)
		{
			returnString += (iter + " ");
		}
	}
	if (picFile.size() != 0)
	{
		returnString += u8"\r\n图片：\r\n";
		for (auto& iter : picFile)
		{
			returnString += (iter + " ");
		}
	}
	if (codeFile.size() != 0)
	{
		returnString += u8"\r\n代码：\r\n";
		for (auto& iter : codeFile)
		{
			returnString += (iter + " ");
		}
	}
	
	if (otherFile.size() != 0)
	{
		returnString += u8"\r\n其他附件：\r\n";
		for (auto& iter : otherFile)
		{
			returnString += (iter + " ");
		}
	}
	return returnString;
}

std::string File::getFile(std::filesystem::path fileName)
{
	FileInfo file(workPath / fileName);
	if (file.getFileFormats() == FileFormats::OTHER || file.getFileFormats() == FileFormats::PIC)
	{
		return u8"该类型文件暂不支持在线查看";
	}
	std::ifstream in(file.getFilePath());
	std::ostringstream tmp;
	tmp << in.rdbuf();
	return tmp.str();
}
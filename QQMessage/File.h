#pragma once
#include <filesystem>
#include <iostream>
#include <vector>
#include "FileInfo.h"
#include "Analyst.h"

/// <summary>
/// 文件管理类
/// </summary>
class File
{
private:
	/// <summary>
	/// 当前提交id的工作目录
	/// </summary>
	std::filesystem::path workPath;
	/// <summary>
	/// 提交id的上层目录【当前作业目录】
	/// </summary>
	std::filesystem::path homePath;
	/// <summary>
	/// 当前提交id的信息文件
	/// </summary>
	std::filesystem::path infoPath;
	/// <summary>
	/// 班级id 学号 作业id 本次提交id 上次提交id
	/// </summary>
	long long classId, schoolId, homeworkId, submitId, lastId;
	/// <summary>
	/// 工作目录所有文件
	/// </summary>
	std::vector<FileInfo> fileList;
	/// <summary>
	/// 自动编号
	/// </summary>
	int autoIndex = 1;
public:
	/// <summary>
	/// 文件管理
	/// </summary>
	/// <param name="classId">班级id</param>
	/// <param name="schoolId">学号</param>
	/// <param name="homeworkId">作业id</param>
	/// <param name="submitId">当前提交id</param>
	File(long long classId, long long schoolId, long long homeworkId, long long submitId);
	File(HomeworkInfo info);
	/// <summary>
	/// 文件管理
	/// </summary>
	/// <param name="classId">班级id</param>
	/// <param name="schoolId">学号</param>
	/// <param name="homeworkId">作业id</param>
	/// <param name="submitId">当前提交id</param>
	/// <param name="lastId">上次提交id</param>
	File(long long classId, long long schoolId, long long homeworkId, long long submitId, long long lastId);
	/// <summary>
	/// 存储文字，使用自动编号
	/// </summary>
	/// <param name="data">utf8文字信息</param>
	/// <returns>文件名</returns>
	std::string storeText(std::string data);
	/// <summary>
	/// 删除文件
	/// </summary>
	/// <param name="fileName">文件名</param>
	std::string delFile(std::filesystem::path fileName);
	/// <summary>
	/// 下载文件
	/// </summary>
	/// <param name="url">下载地址</param>
	/// <param name="fileName">保存文件名</param>
	/// <returns>文件名</returns>
	std::string downFile(std::string url, std::filesystem::path fileName);
	/// <summary>
	/// 存储图片，使用自动编号
	/// </summary>
	/// <param name="url">下载地址</param>
	/// <returns>文件名</returns>
	std::string storePic(std::string url);
	/// <summary>
	/// 本地保存文件
	/// </summary>
	/// <returns>保存结果</returns>
	bool save();
	/// <summary>
	/// 获取当前文件夹下所有文件
	/// </summary>
	/// <returns>类型+文件名</returns>
	std::string getFileList();
	/// <summary>
	/// 获取某个文件
	/// </summary>
	/// <param name="fileName"></param>
	/// <returns></returns>
	std::string getFile(std::filesystem::path fileName);
};


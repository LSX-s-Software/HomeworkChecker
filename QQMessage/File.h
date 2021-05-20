#pragma once
#include <filesystem>
#include <iostream>
#include <vector>
#include "FileInfo.h"
#include "Analyst.h"

/// <summary>
/// �ļ�������
/// </summary>
class File
{
private:
	/// <summary>
	/// ��ǰ�ύid�Ĺ���Ŀ¼
	/// </summary>
	std::filesystem::path workPath;
	/// <summary>
	/// �ύid���ϲ�Ŀ¼����ǰ��ҵĿ¼��
	/// </summary>
	std::filesystem::path homePath;
	/// <summary>
	/// ��ǰ�ύid����Ϣ�ļ�
	/// </summary>
	std::filesystem::path infoPath;
	/// <summary>
	/// �༶id ѧ�� ��ҵid �����ύid �ϴ��ύid
	/// </summary>
	long long classId, schoolId, homeworkId, submitId, lastId;
	/// <summary>
	/// ����Ŀ¼�����ļ�
	/// </summary>
	std::vector<FileInfo> fileList;
	/// <summary>
	/// �Զ����
	/// </summary>
	int autoIndex = 1;
public:
	/// <summary>
	/// �ļ�����
	/// </summary>
	/// <param name="classId">�༶id</param>
	/// <param name="schoolId">ѧ��</param>
	/// <param name="homeworkId">��ҵid</param>
	/// <param name="submitId">��ǰ�ύid</param>
	File(long long classId, long long schoolId, long long homeworkId, long long submitId);
	File(HomeworkInfo info);
	/// <summary>
	/// �ļ�����
	/// </summary>
	/// <param name="classId">�༶id</param>
	/// <param name="schoolId">ѧ��</param>
	/// <param name="homeworkId">��ҵid</param>
	/// <param name="submitId">��ǰ�ύid</param>
	/// <param name="lastId">�ϴ��ύid</param>
	File(long long classId, long long schoolId, long long homeworkId, long long submitId, long long lastId);
	/// <summary>
	/// �洢���֣�ʹ���Զ����
	/// </summary>
	/// <param name="data">utf8������Ϣ</param>
	/// <returns>�ļ���</returns>
	std::string storeText(std::string data);
	/// <summary>
	/// ɾ���ļ�
	/// </summary>
	/// <param name="fileName">�ļ���</param>
	std::string delFile(std::filesystem::path fileName);
	/// <summary>
	/// �����ļ�
	/// </summary>
	/// <param name="url">���ص�ַ</param>
	/// <param name="fileName">�����ļ���</param>
	/// <returns>�ļ���</returns>
	std::string downFile(std::string url, std::filesystem::path fileName);
	/// <summary>
	/// �洢ͼƬ��ʹ���Զ����
	/// </summary>
	/// <param name="url">���ص�ַ</param>
	/// <returns>�ļ���</returns>
	std::string storePic(std::string url);
	/// <summary>
	/// ���ر����ļ�
	/// </summary>
	/// <returns>������</returns>
	bool save();
	/// <summary>
	/// ��ȡ��ǰ�ļ����������ļ�
	/// </summary>
	/// <returns>����+�ļ���</returns>
	std::string getFileList();
	/// <summary>
	/// ��ȡĳ���ļ�
	/// </summary>
	/// <param name="fileName"></param>
	/// <returns></returns>
	std::string getFile(std::filesystem::path fileName);
};


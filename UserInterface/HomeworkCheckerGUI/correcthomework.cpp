#include "correcthomework.h"
#include "WebsocketClientForApp.h"
#include "settingpage.h"
#include <filesystem>


extern WebsocketClientForApp websocketClient;

void CorrectHomework::setHomeworkId(QString homeworkId)
{
	this->homeworkId_qstr = homeworkId;
	this->homeworkId = homeworkId.toLong();
}

QByteArray CorrectHomework::readFile(QFile file)
{
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	return file.readAll();
}

void CorrectHomework::initLoad()
{
	DataManager::Homework hw(homeworkId);

	QString content_str = QString::fromStdString(hw.getContentURL());
	QString attachment_str = QString::fromStdString(hw.getAttachmentURL());
	contentList = content_str.split("|");
	attachmentList = attachment_str.split("|");

	DataManager::Student st(hw.getStudentId());
	
	auto tmpPath = (SettingPage::getWorkPath_str() + "/" + std::to_string(st.getClassId()) + "/" + std::to_string(st.getId()) + "/" + std::to_string(hw.getAssignmentId()));
	

	rootPath = QString::fromStdString(tmpPath.substr(8));
}

QString CorrectHomework::getText()
{
	websocketClient.Connect("ws://" + SettingPage::getWsClientUrl_str());
	text = "";
	for (auto& iter : contentList)
	{
		websocketClient.getFile(homeworkId, iter.toStdString());
		auto fileData = readFile(rootPath + "/" + iter);
		text += ("【" + iter + "】\n");
		text += (QString(fileData) + "\n\n");
	}
	//websocketClient.Close();
	return text;
}

QJsonArray CorrectHomework::getAttachmentList()
{
	while (attachmentArray.count()) {
		attachmentArray.pop_back();
	}
	for (auto& iter : attachmentList)
	{
		QJsonObject obj;
		obj.insert("fileName", iter);
		attachmentArray.append(obj);
	}

	return attachmentArray;
}

bool CorrectHomework::downloadFile(QString fileName)
{
	//websocketClient.Connect("ws://" + SettingPage::getWsClientUrl_str());
	websocketClient.getFile(homeworkId, websocketClient.Utf8ToGbk(fileName.toStdString().c_str()));
	//std::filesystem::path p = websocketClient.Utf8ToGbk("线性代数 第2版.pdf");
	//websocketClient.getFile(homeworkId, p);
	//websocketClient.Close();
	return true;
}
QString CorrectHomework::getWorkPath()
{
	return "file:///" + rootPath;
}

void CorrectHomework::submit(QString comment, QString score)
{
	DataManager::Homework hm(homeworkId);
	hm.setComments(comment.toStdString());
	hm.setScore(score.toShort());
	//websocketClient.Connect("ws://" + SettingPage::getWsClientUrl_str());
	websocketClient.sendReview(homeworkId);
	websocketClient.Close();
}
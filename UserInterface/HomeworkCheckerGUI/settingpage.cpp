#include "settingpage.h"

extern std::string workPath;

SettingPage::SettingPage(QObject* parent) : QObject(parent) {}

void SettingPage::setWorkPath(const QString& path)
{
	workPath = path.toStdString();
}

QString SettingPage::getWorkPath()
{
	return QString::fromStdString(workPath);
}

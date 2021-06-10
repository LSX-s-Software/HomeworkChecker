#include "settingpage.h"
#include <fstream>
#include <filesystem>
#include <sstream>
#include <json.hpp>
#include <QDebug>
#include <QSettings>

std::string SettingPage::workPath;
std::string SettingPage::wsClientUrl;


QSettings settings;

SettingPage::SettingPage(QObject* parent) : QObject(parent) 
{
	workPath = "file:///E:/tmp";
	wsClientUrl = "42.193.50.174:6701";
    loadSettings();
}

void SettingPage::setWorkPath(const QString& path)
{
	workPath = path.toStdString();
}

QString SettingPage::getWsClientUrl()
{
	return QString::fromStdString(wsClientUrl);
}

std::string SettingPage::getWsClientUrl_str()
{
    return wsClientUrl;
}

void SettingPage::setWsClientUrl(const QString& url)
{
    wsClientUrl = url.toStdString();
}

QString SettingPage::getWorkPath()
{
    return QString::fromStdString(workPath);
}
std::string SettingPage::getWorkPath_str()
{
    return workPath;
}


void SettingPage::saveSettings()
{
    settings.setValue("DownloadFolder", QString::fromStdString(workPath));
    settings.setValue("WsClientUrl", QString::fromStdString(wsClientUrl));
}

void SettingPage::restoreSettings()
{
    settings.setValue("DownloadFolder", "file:///E:/tmp");
    settings.setValue("WsClientUrl", "42.193.50.174:6701");
    workPath = "file:///E:/tmp";
    wsClientUrl = "42.193.50.174:6701";
    saveSettings();
}

void SettingPage::loadSettings()
{
    if (settings.contains("DownloadFolder") && settings.contains("WsClientUrl")) {
        workPath = settings.value("DownloadFolder").toString().toStdString();
        wsClientUrl = settings.value("WsClientUrl").toString().toStdString();
    } else {
        restoreSettings();
    }
}

#include "settingpage.h"
#include <fstream>
#include <filesystem>
#include <sstream>
#include <json.hpp>
#include <QDebug>

std::string SettingPage::workPath;
std::string SettingPage::wsClientUrl;

SettingPage::SettingPage(QObject* parent) : QObject(parent) 
{
	workPath = "file:///E:/tmp";
	wsClientUrl = "127.0.0.1:6700";
    loadFromFile();
}

void SettingPage::setWorkPath(const QString& path)
{
	workPath = path.toStdString();
}

QString SettingPage::getWsClientUrl()
{
	return QString::fromStdString(wsClientUrl);
}

void SettingPage::setWsClientUrl(const QString& url)
{
    wsClientUrl = url.toStdString();
}

QString SettingPage::getWorkPath()
{
    return QString::fromStdString(workPath);
}

void SettingPage::saveToFile()
{
    std::filesystem::path settingFile = "setting.config";
    std::ofstream out;
    out.open(settingFile, std::ios::trunc);
    nlohmann::json encode{
    { "DownloadFolder", workPath},
    { "WsClientUrl", wsClientUrl },
    };
    out << encode;
    out.close();
}

void SettingPage::restoreFile()
{
    workPath = "file:///E:/tmp";
    wsClientUrl = "127.0.0.1:6700";
    saveToFile();
}

void SettingPage::loadFromFile()
{
    std::filesystem::path settingFile = "setting.config";
    if (!std::filesystem::exists(settingFile))
    {
        restoreFile();
    }
    if (std::filesystem::exists(settingFile))
    {
        std::ifstream in;
        in.open(settingFile);
        std::stringstream buffer;
        buffer << in.rdbuf();
        std::string contents(buffer.str());
        in.close();
        auto decode = nlohmann::json::parse(contents);
        wsClientUrl = "";
        workPath = "";
        if (decode.contains("DownloadFolder") && decode.contains("WsClientUrl"))
        {
            workPath = decode.at("DownloadFolder");
            wsClientUrl = decode.at("WsClientUrl");
        }
        if (wsClientUrl == "" || workPath == "")
        {
            restoreFile();
        }
    }
    //std::cout << wsClientUrl << std::endl << workPath << std::endl;
}

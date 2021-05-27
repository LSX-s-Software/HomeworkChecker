#include <iostream>
#include <fstream>
#include <string>
std::string rootPath = R"(D:\Work\HomeworkChecker\x64\Debug\tmp\)";
#include "QQMessage.h"
#include "WebsocketClient.h"
#include "File.h"
#include "DataManager.hpp"
#include <json.hpp>
#include <thread>

std::string wsClientUrl;
std::string workPath;

void saveToFile()
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

void restoreFile()
{
    workPath = "file:///E:/tmp";
    wsClientUrl = "127.0.0.1:6700";
    saveToFile();
}

void loadFromFile()
{
    std::filesystem::path settingFile = "setting.config";
    std::cout << settingFile;
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
    std::cout << wsClientUrl << std::endl << workPath << std::endl;
}


int main()
{
    system("CHCP 65001");
    
    loadFromFile();

    
    

    system("pause");
    using namespace std;
    try
    {
        QQMessage::_InitClient("127.0.0.1:6700");
        //ws.Send(R"({"action":"get_file","homework_id":"19","file_name":"1.png"})");
        QQMessage::_InitServer(6701);
        //ws.Close("CLOSE");
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
    }
    while (true);
    QQMessage::_Stop();
    return 0;
}
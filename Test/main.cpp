#include <iostream>
#include <string>
std::string rootPath = R"(D:\Work\HomeworkChecker\x64\Debug\tmp\)";
#include "QQMessage.h"
#include "WebsocketClient.h"
#include "File.h"
#include "DataManager.hpp"
#include <json.hpp>
#include <thread>
    

int main()
{
    system("CHCP 65001");
    
    
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
#include <iostream>
#include <string>

#include "QQMessage.h"
std::string rootPath = R"(tmp)";

int main()
{
    //system("CHCP 65001");
    
    //::ShellExecute(NULL, L"open", L"D:\\Work\\HomeworkChecker\\go-cqhttp\\start.lnk", L"", NULL, SW_SHOWNORMAL);
    //Sleep(8000);
    try
    {
        //QQMessage::_InitClient("127.0.0.1:6700");
        QQMessage::_InitClient("114.116.231.126:6700");
        QQMessage::_InitServer(6701);
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    int x;
    while (std::cin >> x)
    {
        std::cout << x << std::endl;
    }
    QQMessage::_Stop();
    return 0;
}
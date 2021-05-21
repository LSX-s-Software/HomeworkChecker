#include <iostream>
#include <string>

#include "QQMessage.h"
std::string rootPath = R"(D:\Work\HomeworkChecker\x64\Debug\tmp\)";

int main()
{
    system("CHCP 65001");
    
    ::ShellExecute(NULL, L"open", L"D:\\Work\\HomeworkChecker\\go-cqhttp\\start.lnk", L"", NULL, SW_SHOWNORMAL);
    Sleep(10000);
    try
    {
        QQMessage::_InitClient("127.0.0.1:6700");
        QQMessage::_InitServer(6701);
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    while (true);
    QQMessage::_Stop();
    return 0;
}
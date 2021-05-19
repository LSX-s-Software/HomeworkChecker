#include <iostream>
#include <string>
std::string rootPath = R"(D:\Work\HomeworkChecker\x64\Debug\tmp\)";
#include "QQMessage.h"

int main() {
    
    WebsocketServer wsr;
    wsr.start(7999);
    std::string x;
    while (std::cin >> x)
    {
        std::cout << x;
    }
}



int main2()
{
    using namespace std;
    try
    {
        QQMessage::_Init("127.0.0.1:6700");
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
    }

    string x;
    while (cin >> x)
    {
    }
    QQMessage::_Stop();
    return 0;
}
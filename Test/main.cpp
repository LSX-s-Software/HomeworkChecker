#include <iostream>
#include <string>
std::string rootPath = R"(D:\Work\HomeworkChecker\x64\Debug\tmp\)";
#include "QQMessage.h"
#include "File.h"

int main()
{
    using namespace std;
    File fp(1001, 1002, 1003, 1007, 1004);
    fp.storeText(u8"123123\r\n1231245ºÃµÄ");
    fp.storePic("http://c2cpicdw.qpic.cn/offpic_new/0//1114738346-3526679326-A5A2E4ADB717E94A1D83E6587068E083/0?term=2");
    fp.downFile("http://116.128.163.102/ftn_handler/a7de378eb0f042340e5ef3f4b48fafb7bbdcb1881458034e45b80f4db6991cc4e7a8bac733cbbb01bd3d459f71449f1ee4976c6c52480e873e19ad728c99c5c0", "test.cpp");
    fp.delFile("2.txt");
    fp.delFile("1.png");
    fp.save();
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
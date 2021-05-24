#include <iostream>
#include <string>
#include "WebsocketClientForApp.h"

using namespace std;


int main()
{
	system("CHCP 65001");
	WebsocketClientForApp ws;//创建ws客户端对象
	ws.rootPath = R"(E:/tmp)";//指定本地根路径
	ws.Connect("ws://127.0.0.1:6701");//连接ws
	//ws.Connect("ws://119.29.3.36:6700");
	//ws.sendReview(19);//发送评语+分数
	//ws.getFile(19, "1.zip");//获取文件
	//ws.getFile(19, "1.png");
	Sleep(1000);
	ws.Close();//程序结束前关闭ws连接
}
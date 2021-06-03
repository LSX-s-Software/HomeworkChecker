#include <iostream>
#include <string>
#include "WebsocketClientForApp.h"

using namespace std;


int main()
{
	system("CHCP 65001");
	WebsocketClientForApp ws;//创建ws客户端对象
	ws.rootPath = R"(E:/tmp)";//指定本地根路径
	ws.Connect("ws://42.193.50.174:6701");//连接ws
	ws.sendReview(27);//发送评语+分数
	//ws.getFile(24, "线性代数 第2版.pdf");
	//ws.sendNewHomeworkNotification(2);
	//while(true)
		//Sleep(1000);
	ws.Close();//程序结束前关闭ws连接
}
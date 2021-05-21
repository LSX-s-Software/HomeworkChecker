#include <iostream>
#include <string>
#include "WebsocketClientForApp.h"

using namespace std;
bool completeFileTransfer=false;//捕获是否下载完成

int main()
{
	system("CHCP 65001");
	WebsocketClientForApp ws;//创建对象
	ws.rootPath = R"(E:/tmp)";//指定本地根路径
	ws.Connect("ws://127.0.0.1:6701");//连接ws
	Sleep(2000);
	//ws.sendReview(19);
	ws.getFile(19, "1.zip");
	while (true)
	{
		if (completeFileTransfer)
		{
			cout << "file ok" << endl;
			break;
			//ws.Close();
			//return 0;
		}	
	}
	ws.getFile(19, "1.png");
	while (true)
	{
		if (completeFileTransfer)
		{
			cout << "file ok" << endl;
			break;
			//ws.Close();
			//return 0;
		}
	}
}
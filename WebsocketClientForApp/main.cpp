#include <iostream>
#include <string>
#include "WebsocketClientForApp.h"

using namespace std;
bool completeFileTransfer=false;//�����Ƿ��������

int main()
{
	system("CHCP 65001");
	WebsocketClientForApp ws;//��������
	ws.rootPath = R"(E:/tmp)";//ָ�����ظ�·��
	ws.Connect("ws://127.0.0.1:6701");//����ws
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
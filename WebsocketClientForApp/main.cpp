#include <iostream>
#include <string>
#include "WebsocketClientForApp.h"

using namespace std;
bool completeFileTransfer=false;//�����Ƿ��������

int main()
{
	system("CHCP 65001");
	WebsocketClientForApp ws;//����ws�ͻ��˶���
	ws.rootPath = R"(E:/tmp)";//ָ�����ظ�·��
	ws.Connect("ws://127.0.0.1:6701");//����ws
	ws.sendReview(19);//��������+����
	ws.getFile(19, "1.zip");//��ȡ�ļ�
	while (true)
	{
		if (completeFileTransfer)
		{
			cout << "file ok" << endl;
			break;
		}	
	}
	ws.Close();//�������ǰ�ر�ws����
}
#include <iostream>
#include <string>
#include "WebsocketClientForApp.h"

using namespace std;


int main()
{
	system("CHCP 65001");
	WebsocketClientForApp ws;//����ws�ͻ��˶���
	ws.rootPath = R"(E:/tmp)";//ָ�����ظ�·��
	ws.Connect("ws://127.0.0.1:6701");//����ws
	//ws.Connect("ws://119.29.3.36:6700");
	//ws.sendReview(19);//��������+����
	//ws.getFile(19, "1.zip");//��ȡ�ļ�
	//ws.getFile(19, "1.png");
	Sleep(1000);
	ws.Close();//�������ǰ�ر�ws����
}
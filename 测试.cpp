// PortScanf.cpp : 定义控制台应用程序的入口点。
//TCP扫描,SYN扫描,UDP扫描
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN


#include <WinSock2.h>
#include <cstdio>
#include <iostream>

#pragma comment(lib, "Ws2_32")

using namespace std;

int scant(char* Ip, int StartPort, int EndPort)
{
	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;

	int CurrPort;    //当前端口
	int ret;

	WSAStartup(MAKEWORD(2, 2), &wsa);    //使用winsock函数之前，必须用WSAStartup函数来装入并初始化动态连接库

	server.sin_family = AF_INET;    //指定地址格式，在winsock中只能使用AF_INET
	server.sin_addr.s_addr = inet_addr(Ip); //指定被扫描的IP地址

	for (CurrPort = StartPort; CurrPort <= EndPort; CurrPort++)
	{
		s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		server.sin_port = htons(CurrPort); //指定被扫描IP地址的端口号
		ret = connect(s, (struct sockaddr*)&server, sizeof(server)); //连接

		if (0 == ret) //判断连接是否成功
		{
			printf("%s:%d Success O(∩_∩)O~~\n", Ip, CurrPort);
			closesocket(s);
		}
		else {
			printf("%s:%d Failed\n", Ip, CurrPort);
		}
	}
	//printf("Cost time:%f second\n", CostTime); //输出扫描过程中耗费的时间
	WSACleanup();    //释放动态连接库并释放被创建的套接字
	return 1;
}

int main()
{
	while (true)
	{

		cout << "请输入你要扫描的ip：" << endl;
		cout << ">>";
		char* ip = new char[50];
		cin >> ip;

		cout << "输入你要查询的起始端口：" << endl;
		cout << ">>";
		int startPort;
		cin >> startPort;

		cout << "输入你要查询的结束端口：" << endl;
		cout << ">>";
		int endPort;
		cin >> endPort;

		scant(ip, startPort, endPort);

	}

	return 0;
}
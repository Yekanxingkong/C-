// PortScanf.cpp : �������̨Ӧ�ó������ڵ㡣
//TCPɨ��,SYNɨ��,UDPɨ��
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

	int CurrPort;    //��ǰ�˿�
	int ret;

	WSAStartup(MAKEWORD(2, 2), &wsa);    //ʹ��winsock����֮ǰ��������WSAStartup������װ�벢��ʼ����̬���ӿ�

	server.sin_family = AF_INET;    //ָ����ַ��ʽ����winsock��ֻ��ʹ��AF_INET
	server.sin_addr.s_addr = inet_addr(Ip); //ָ����ɨ���IP��ַ

	for (CurrPort = StartPort; CurrPort <= EndPort; CurrPort++)
	{
		s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		server.sin_port = htons(CurrPort); //ָ����ɨ��IP��ַ�Ķ˿ں�
		ret = connect(s, (struct sockaddr*)&server, sizeof(server)); //����

		if (0 == ret) //�ж������Ƿ�ɹ�
		{
			printf("%s:%d Success O(��_��)O~~\n", Ip, CurrPort);
			closesocket(s);
		}
		else {
			printf("%s:%d Failed\n", Ip, CurrPort);
		}
	}
	//printf("Cost time:%f second\n", CostTime); //���ɨ������кķѵ�ʱ��
	WSACleanup();    //�ͷŶ�̬���ӿⲢ�ͷű��������׽���
	return 1;
}

int main()
{
	while (true)
	{

		cout << "��������Ҫɨ���ip��" << endl;
		cout << ">>";
		char* ip = new char[50];
		cin >> ip;

		cout << "������Ҫ��ѯ����ʼ�˿ڣ�" << endl;
		cout << ">>";
		int startPort;
		cin >> startPort;

		cout << "������Ҫ��ѯ�Ľ����˿ڣ�" << endl;
		cout << ">>";
		int endPort;
		cin >> endPort;

		scant(ip, startPort, endPort);

	}

	return 0;
}
#ifndef UNICODE
#define UNICODE
#endif
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <string>
// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")
using namespace std;
void main()
{
	//Initialze winsock
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cout << "Can't Initialize winsock!Quiting!" << std::endl;;
		return;
	}
	//Creste a sockrt
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);
	if (sockClient == INVALID_SOCKET) {
		wprintf(L"Can't create a socket with error %d\n", WSAGetLastError());
		WSACleanup();
		return;
	}
	//Bind the socket to an ip address and port
	int port = 5099;
	SOCKADDR_IN addrSrv;
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(5099);
	//addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	inet_pton(AF_INET, "127.0.0.1",&addrSrv.sin_addr.S_un.S_addr);
	char buff[1024];
	memset(buff, 0, sizeof(buff));
	//向服务器发出连接请求
	if (connect(sockClient, (struct  sockaddr*) & addrSrv, sizeof(addrSrv)) == INVALID_SOCKET) {
		printf("Connect failed:%d", WSAGetLastError());
		return;
	}
	else
	{
		//接收数据
		recv(sockClient, buff, sizeof(buff), 0);
		printf("%s\n", buff);
	}
	//发送数据
	//const char* buffSend = "hello, this is a Client....";
	//send(sockClient, buffSend, strlen(buffSend) + 1, 0);
	char sendbuf[BUFSIZ];
	std::cout << "Use quit to exit!\n";
	while (true) {
		std::cout << "Please input a string to send:";
		std::string str;
		getline(std::cin, str);
		if (str == "quit") {
			break;
		}
		ZeroMemory(sendbuf, BUFSIZ);
		strcpy_s(sendbuf, str.c_str());
		if (send(sockClient, sendbuf, strlen(sendbuf) + 1, 0) == SOCKET_ERROR) {
			wprintf(L"send failed with error: %d\n", WSAGetLastError());
			closesocket(sockClient);
			WSACleanup();
			break;
		}
	}
	//printf("%d", strlen(buffSend) + 1);
	//关闭套接字
	closesocket(sockClient);
	WSACleanup();
	system("pause");
}

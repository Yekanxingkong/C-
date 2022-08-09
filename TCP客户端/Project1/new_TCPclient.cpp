#include <iostream>
#include <WinSock2.h>  
#include <WS2tcpip.h>  
#include <stdio.h>
#include <cstdio>
#include <windows.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

// 【1】初始化WinSock
bool initWinSockC()
{
	WORD verision = MAKEWORD(2, 2);
	WSADATA lpData;
	int intEr = WSAStartup(verision, &lpData); // 指定winsock版本并初始化
	if (intEr != 0)
	{
		cout << "WinSock初始化失败！" << endl;
		return false;
	}
	return true;
}

// 【2】创建socket
bool createSocketC(SOCKET& listenScok)
{ 
	listenScok = socket(AF_INET, SOCK_STREAM, 0);
	if (listenScok == INVALID_SOCKET)
	{
		cout << "socket创建失败！" << endl;
		return false;
	}
	return true;
}

// 【3】连接到服务器
bool connectSocketC(SOCKET& conSock, const string ip, const unsigned short port)
{
	sockaddr_in hostAddr;
	hostAddr.sin_family = AF_INET;
	hostAddr.sin_port = htons(port);
	in_addr addr;
	inet_pton(AF_INET, ip.c_str(), (void*)&addr);
	hostAddr.sin_addr = addr;
	int err = connect(conSock, (sockaddr*)&hostAddr, sizeof(sockaddr));
	if (err == INVALID_SOCKET)
	{
		cout << "连接服务器失败！" << endl;
		return false;
	}
	return true;
}

// 【4】发送数据
bool sendDataC(SOCKET& clientSock, const string& data)
{
	int err = send(clientSock, data.c_str(), data.size(), 0);
	if (err == SOCKET_ERROR)
	{
		cout << "发送失败！" << endl;
		return false;
	}
	return true;
}

// 【5】接收数据
bool receiveDataC(SOCKET& clientSock, string& data)
{
	static int cnt = 1; // 接收数据编号-静态
	char buf[1024] = "\0";// 通过已建立连接的套接字，接收数据 设定缓冲1024字节
	// flags操作方式（0正常数据，MSG_PEED系统缓冲区的数据复制到所提供的接收缓冲区内，系统缓冲区数据未删除，MSG_OOB处理带外数据，通常用参数0即可）
	int buflen = recv(clientSock, buf, 1024, 0);
	if (buflen == SOCKET_ERROR)
	{
		cout << "接收失败！" << endl;
		return false;
	}
	data = string(buf);	// 一切正常则返回接收数据
	return true;
}

int TCP_client()
{
	SOCKET clientSock;	// 客户端Socket
	string data;
	string str;
	if (initWinSockC() == TRUE && createSocketC(clientSock) == TRUE && connectSocketC(clientSock, "127.0.0.1", 1994) == TRUE) {
		//cout << "服务器连接成功" << endl;
		receiveDataC(clientSock, data);//接收服务器数据
		cout <<  data << endl;
		cout << "Please enter the activation code :" << endl;
		cin >> str;
		sendDataC(clientSock, str);//发送本地数据
		WSACleanup();
		TCP_client();
	}
	else{
		MessageBoxA(NULL, "Unable to connect to the Internet, please check the network and try again!!!", "error", 0);
		exit(0);
	}
	return 0;
}


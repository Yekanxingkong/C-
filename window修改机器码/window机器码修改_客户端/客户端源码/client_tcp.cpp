#include <pah.h>
#include <iostream>
#include <WinSock2.h>  
#include <WS2tcpip.h>  
#include <stdio.h>
#include <cstdio>
#include <windows.h>
#include <cstring>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <fstream>
#include <direct.h>
#include <sys/stat.h>
#include <io.h>
#include <process.h>
#include <stdio.h>
//#include <string.h>// bzero
#include <string> 

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
	//cout << "WinSock初始化成功！" << endl;
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
	//cout << "WinSock创建成功！" << endl;
	return true;
}

// 【3】连接到服务器
bool connectSocketC(SOCKET& conSock, const string ip, const unsigned short port)
{
	// 建立地址结构体
	sockaddr_in hostAddr;
	hostAddr.sin_family = AF_INET;
	hostAddr.sin_port = htons(port);
	in_addr addr;
	inet_pton(AF_INET, ip.c_str(), (void*)&addr);
	hostAddr.sin_addr = addr;
	//cout << "正在连接服务器……" << endl;
	int err = connect(conSock, (sockaddr*)&hostAddr, sizeof(sockaddr));
	if (err == INVALID_SOCKET)
	{
		cout << "连接服务器失败！" << endl;
		return false;
	}
	//cout << "连接服务器成功！" << endl;
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
	char buf[1024] = "\0";// 通过已建立连接的套接字，接收数据 设定缓冲1024字节
	// flags操作方式（0正常数据，MSG_PEED系统缓冲区的数据复制到所提供的接收缓冲区内，系统缓冲区数据未删除，MSG_OOB处理带外数据，通常用参数0即可）
	int buflen = recv(clientSock, buf, 1024, 0);
	if (buflen == SOCKET_ERROR)
	{
		cout << "服务器连接错误，接收失败！" << endl;
		return false;
	}
	data = string(buf);	// 一切正常则返回接收数据
	return true;
}

std::string CDK() {
	char buffs_cdk[] = "C:\\Users\\Administrator\\AppData\\Local\\Temp\\CDK_pubg_rm_v3.dark";
	ifstream readFile(buffs_cdk);
	char reading[37] = { 0 };
	readFile >> reading;
	readFile.close();
	if (strlen(reading) == 36) {
		return reading;
	}
	else {
		return "Flase";
	}
}


int client_tcp(string cdk)
{
	string data;
	string str;
	SOCKET clientSock;
	if (cdk == "")
	{
		//if (initWinSockC() == TRUE && createSocketC(clientSock) == TRUE && connectSocketC(clientSock, "192.168.2.190", 10268) == TRUE) {
		if (initWinSockC() == TRUE && createSocketC(clientSock) == TRUE && connectSocketC(clientSock, "180.113.42.26", 10268) == TRUE) {
			receiveDataC(clientSock, data);//接收服务器数据
			if (data == "Server connection succeeded") {
				char host[255];
				if (gethostname(host, sizeof(host)) == SOCKET_ERROR)
				{
					str.append("无法获取主机名");
					//sendDataC(clientSock, "无法获取主机名");
				}
				else
				{
					//sendDataC(clientSock, host);
					str.append(host);
					struct hostent* p = gethostbyname(host);
					for (int i = 0; p->h_addr_list[i] != 0; i++)
					{
						struct in_addr in;
						memcpy(&in, p->h_addr_list[i], sizeof(struct in_addr));
						str.append("第");
						str.append(std::to_string(i + 1));
						str.append("块网卡的IP为:");
						str.append(inet_ntoa(in));
					}
				}
				sendDataC(clientSock, str);
				receiveDataC(clientSock, data);
				//返回关闭数据
				if (data == "Server close") {
					char debug[]="server close it";
				}
				else {
					MessageBoxA(NULL, "Unable to connect to the Internet, please check the network and try again!!!", "error", 0);
					exit(0);
				}
			}
			else {
				cout << "请联系管理员：" << data << endl;

			}
			//------------判断第一次数据-----------------------
		}
		else {
			MessageBoxA(NULL, "无法连接服务器，请稍后尝试!!!", "网络错误", 0);
			closesocket(clientSock);
			WSACleanup();
			exit(0);
		}
	}
	else {
		//if (initWinSockC() == TRUE && createSocketC(clientSock) == TRUE && connectSocketC(clientSock, "192.168.2.190", 10268) == TRUE) {
		if (initWinSockC() == TRUE && createSocketC(clientSock) == TRUE && connectSocketC(clientSock, "180.113.42.26", 10268) == TRUE) {
			receiveDataC(clientSock, data);//接收服务器数据
			if (data == "Server connection succeeded") {
				sendDataC(clientSock, cdk);
				receiveDataC(clientSock, data);
				if (data == "succeed") {
					closesocket(clientSock);
					WSACleanup();
					return 1;
				}
			}
			else {
				cout << "请联系管理员：" << data << endl;

			}
				
		}
		else {
			MessageBoxA(NULL, "无法连接服务器，请稍后尝试!!!", "网络错误", 0);
			closesocket(clientSock);
			WSACleanup();
			exit(0);
		}

	}
	closesocket(clientSock);
	WSACleanup();
	return 0;
}

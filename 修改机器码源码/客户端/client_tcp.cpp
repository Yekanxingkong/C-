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
	cout << "正在连接服务器……" << endl;
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
		cout << "接收失败！" << endl;
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


int loopA = 0;
int main()
{
	if (loopA == 0) {
		at();
		struct stat buffer;
		if (stat("C:\\Users\\Administrator\\AppData\\Local\\Temp\\CDK_pubg_rm_v3.dark", &buffer) != 0) {
			exit(0);
		}
		if (if_resultle("\\机器码修改器.exe") == 0) {
			/*
			FILE* file = fopen( filepath, "r" );
			if ( file )
			{
				int size = filelength( fileno(file) );
				cout << size << endl;
				fclose( file );
			}
			*/
			char debug[] = "this Check file space";
		}
		else {
			MessageBoxA(NULL, "No operating environment found, please contact the author！", "error!!!", MB_OK);
			exit(0);
		}
	}
	string data;
	string str;
	SOCKET clientSock;
	if (initWinSockC() == TRUE && createSocketC(clientSock) == TRUE && connectSocketC(clientSock, "180.113.42.26", 10268) == TRUE) {
		receiveDataC(clientSock, data);//接收服务器数据
		if (loopA == 0) {
			loopA = 1;
			cout << data << endl;
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
			if (data == "Server close") {
				closesocket(clientSock);
				WSACleanup();
				main();
			}
			else {
				MessageBoxA(NULL, "Unable to connect to the Internet, please check the network and try again!!!", "error", 0);
				exit(0);
			}
		}
		else {
			str = CDK();
			if (str != "Flase") {
				char suss[] = "CDK位数验证成功";
				sendDataC(clientSock, str);
				//cout << "str=cdk" << endl;
			}
			else {
				//cout << "CDK过期！！！" << endl;
				sendDataC(clientSock, "mistake cdk！！！");
			}
			receiveDataC(clientSock, data);
			if (data == "succeed") {
				MessageBoxA(NULL, "Machine code has been modified!!!", "succeed", 0);
				leading_create_SN();
			}
			else {
				MessageBoxA(NULL, "Machine code expired!!!", "error", 0);

			}


		}
		

	}
	else {
		MessageBoxA(NULL, "Unable to connect to the Internet, please check the network and try again!!!", "error", 0);
		exit(0);
	}
	closesocket(clientSock);
	WSACleanup();
	return 0;
	exit(0);
}

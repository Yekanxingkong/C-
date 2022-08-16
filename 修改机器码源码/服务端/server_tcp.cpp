#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h> 
#include <windows.h>
#include <cstdio>
#include <ctime>
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
#include <pah.h>
#include <time.h>
#pragma comment(lib,"ws2_32.lib")  
using namespace std;

bool initWinSock()
{
	WORD verision;//十六位数据 ,自定义名称
	WSADATA lpData;// 这结构是用于接收Windows Socket的结构信息的,自定义名称
	verision = MAKEWORD(2, 2);// 请求2.2版本的WinSock库，返回一个word变量，实际上这个函数（宏）本身只是将俩个byte型合并成一个word型
	int intEr = WSAStartup(verision, &lpData); // 指定winsock版本并初始化
	if (intEr != 0)// 返回值为零的时候是表示成功申请WSAStartup
	{
		cout << "socket初始化失败！" << endl;
		return false;
	}
	cout << "初始化成功" << endl;
	return true;
}

bool createSocket(SOCKET& listenScok)
{
	listenScok = socket(AF_INET, SOCK_STREAM, 0);
	if (listenScok == INVALID_SOCKET)
	{
		cout << "socket创建失败！" << endl;
		return false;
	}
	cout << "socket创建成功！" << endl;
	return true;
}

// 【3】socket绑定本机地址信息
bool bindIPandPort(SOCKET& listenScok, const string ip, const unsigned short port)
{
	sockaddr_in hostAddr;
	hostAddr.sin_family = AF_INET;
	hostAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	hostAddr.sin_port = htons(port);
	in_addr addr;
	inet_pton(AF_INET, ip.c_str(), (void*)&addr);
	hostAddr.sin_addr = addr;
	int err = bind(listenScok, (struct sockaddr*)&hostAddr, sizeof(sockaddr));
	if (err != 0)
	{
		cout << "本地IP绑定失败！" << endl;
		return false;
	}
	return true;
}

// 【4】侦听socket，接收客户端请求
bool listenSocket(SOCKET& listenScok)
{
	// 设定套接字为侦听状态，准备接收客户机进程发送来的连接请求
	int err = listen(listenScok, 3);
	if (err != 0)
	{
		cout << "socket监听失败！" << endl;
		return false;
	}
	//cout << "等待客户端连接……" << endl;
	return true;
}

// 【5】等待客户端连接
bool waitClientConnect(SOCKET& listenScok, SOCKET& clientSock)
{
	sockaddr_in clientAddr;
	int len = sizeof(struct sockaddr); // 必须指定长度，否则会导致accept返回10014错误				   
	clientSock = accept(listenScok, (struct sockaddr*)&clientAddr, &len);// accept会循环等待客户端连接
	if (clientSock == INVALID_SOCKET)//
	{
		MessageBoxA(NULL, "waitClientConnect failed to create,program closes!!!", "error5", 0);
		exit(0);
	}
	cout << "客户端Socket编号:" << clientSock << endl;


	return true;
}

// 【6】接收数据

bool receiveData(SOCKET& clientSock, string& data)
{
	char receive_client_dataA[1024] = "\0";
	//static int cnt = 1; // 接收数据编号-静态
						// 通过已建立连接的套接字，接收数据 设定缓冲1024字节
	// flags操作方式（0正常数据，MSG_PEED系统缓冲区的数据复制到所提供的接收缓冲区内，系统缓冲区数据未删除，MSG_OOB处理带外数据，通常用参数0即可）
	int buflen = recv(clientSock, receive_client_dataA, 1024, 0);
	if (buflen == SOCKET_ERROR)
	{
		cout << "客户端关闭！" << endl;
		return false;
	}
	// 一切正常则显示接收数据
	//cout << data <<"||" << receive_client_dataA << endl;
	data = string(receive_client_dataA);
	return true;
}

// 【7】停止套接字的接收、发送
bool shutdownSocket(SOCKET& clientSock)
{
	//（收完就关）停止套接字的接收、发送功能（0禁止接收，1禁止发送，2禁制接收发送）
	int err = shutdown(clientSock, 2);
	if (err == SOCKET_ERROR)
	{
		cout << "关闭Socket失败！" << endl;
		return false;
	}
	return true;
}

// 【8】发送信息
bool sendData(SOCKET& clientSock, const string& data)
{
	int err = send(clientSock, data.c_str(), data.size(), 0);
	if (err == SOCKET_ERROR)
	{
		cout << "发送失败！" << endl;
		return false;
	}
	return true;
}

void func(char* buff, const std::string& list)
{
	ofstream outfile(buff, ofstream::app);
	//ofstream outfile("E:\\myfile.txt", ofstream::app);
	string temp = list;  //写入内容
	if (outfile.is_open())
	{
		outfile << temp << "\n";
		outfile.close();
	}
	else
	{
		cout << "can not open the file \n" << endl;
	}
}

//运行外部程序
void fund(char* buff)
{
	HINSTANCE hNewExe = ShellExecuteA(NULL, NULL, buff, NULL, NULL, SW_SHOW);
	if ((DWORD)hNewExe <= 32)
	{
		cout << "not find:" << buff << " error!!!" << (DWORD)hNewExe;
		MessageBoxA(NULL, "No valid path found:03", "error!!!", MB_OK);
		exit(0);
	}
	else
	{
		printf("successed!!!\n");
	}
}
//判断文件是否存在
int if_resultle(const char i[]) {
	struct stat buffer;
	int result;
	char buff[250];
	_getcwd(buff, 250);
	strcat_s(buff, i);
	result = stat(buff, &buffer);
	return result;
}


int main()
{
	SOCKET listenScok;	// 服务端Socket
	SOCKET clientSock;	// 客户端Socket
	string data;
	string debug;
	struct stat buffer;
	char buff[250];
	_getcwd(buff, 250);
	if (initWinSock() == TRUE && createSocket(listenScok) == TRUE && bindIPandPort(listenScok, "192.168.2.190", 10268) == TRUE) 
	{
		listenSocket(listenScok);// 坐等客户端连接
		waitClientConnect(listenScok, clientSock);
		sendData(clientSock, "server is connected");
		receiveData(clientSock, data);
		if (data != "") 
		{
			cout << "客户端数据：" << data << endl;
			strcat_s(buff, "\\temp.log");
			time_t now = time(NULL);
			char str[26] = {};
			ctime_s(str, 26, &now);
			func(buff, str);//写入系统时间
			func(buff, data);//写入客户端数据
			func(buff, "\n");
			if (data.length() == 36){
				_getcwd(buff, 250);
				strcat_s(buff, "\\cdk.tap");
				func(buff, data);
				_getcwd(buff, 250);
				strcat_s(buff, "\\cdksqlpythony.py");
				fund(buff);
				Sleep(3000);
				//int a = 0;
				//do { a++; } while (a < 120000);
				if (if_resultle("\\cdk.op") == 0) {
					_getcwd(buff, 250);
					strcat_s(buff, "\\cdk.tap");
					remove(buff);
					sendData(clientSock, "succeed");//发送成功代码
					closesocket(listenScok);
					closesocket(clientSock);
					WSACleanup();
					main();
				}
			}
			else {
				debug = "字符长度超标，不予判断";
			}
		}
		_getcwd(buff, 250);
		strcat_s(buff, "\\cdk.op");
		remove(buff);
		sendData(clientSock, "Server close");
	}
	else {
		MessageBoxA(NULL, "socket failed to create,program closes!!!", "error", 0);
		exit(0);
	}
	closesocket(listenScok);
	closesocket(clientSock);
	WSACleanup();
	cout << "Scok close!!!!" << endl;
	main();
}

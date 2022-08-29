#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h> 
#include <windows.h>
//#include "stdafx.h"

#pragma comment(lib,"ws2_32.lib")  
using namespace std;

// 【1】初始化WinSock
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
	return true;
	/*cout << LOBYTE(lpData.wVersion) << "||" << HIBYTE(lpData.wVersion) << endl;
	if (LOBYTE(lpData.wVersion) != 2 || HIBYTE(lpData.wVersion) != 2) {// 检查这个低字节是不是1，高字节是不是1以确定是否我们所请求的1.1版本
		WSACleanup();
		exit(0);
	}*/
}

// 【2】创建socket
bool createSocket(SOCKET& listenScok)
{
	// 创建侦听socket  
	listenScok = socket(AF_INET, SOCK_STREAM, 0);
	if (listenScok == INVALID_SOCKET)
	{
		cout << "socket创建失败！" << endl;
		return false;
	}
	//cout << "socket创建成功！" << endl;
	return true;
}

// 【3】socket绑定本机地址信息
bool bindIPandPort(SOCKET& listenScok, const string ip, const unsigned short port)
{
	// 制作sockaddr_in结构体
	// 在bind函数，connect函数里提到了套接字编程网络地址信息结构体const struct sockaddr和const struct sockaddr_i
	// 创建socket操作，建立流式套接字，返回套接字号sockClient

	sockaddr_in hostAddr;
	//hostAddr.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
	hostAddr.sin_family = AF_INET;
	hostAddr.sin_port = htons(port);//转换成网络字节序  
									//hostAddr.sin_addr.S_un.S_addr = inet_addr(SERVERIP);//转换成网络字节序  
									//cout << "net IP:" << hostAddr.sin_addr.S_un.S_addr << endl;  
									/*
									inet_addr()版本太低，被弃用使用inet_pton(协议族，字符串IP地址，void目标in_addr*)
									头文件：WS2tcpip.h
									*/
	in_addr addr;
	inet_pton(AF_INET, ip.c_str(), (void*)&addr);
	// SOCKET socket(int af, int type, int protocol);
	// 第一个参数，指定地址簇(TCP/IP只能是AF_INET，也可写成PF_INET)
	// 第二个，选择套接字的类型(流式套接字)，第三个，特定地址家族相关协议（0为自动）
	hostAddr.sin_addr = addr;
	//cout << "ip(网络字节序):" << addr.S_un.S_addr << endl;
	//cout << "ip(常规形式):" << ip.c_str() << endl;


	int err = bind(listenScok, (struct sockaddr*)&hostAddr, sizeof(sockaddr));
	// 侦听套接字listenSock绑定本机地址信息  
	// int err( SOCKET s,  const struct sockaddr* name,  int namelen);
	// 第一个参数：需要进行连接操作的套接字
	// 第二个参数：设定所需要连接的地址信息
	// 第三个参数：地址的长度
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
	//cout << "监听客户端连接中……" << endl;
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


int JTCPserver()
{
	SOCKET listenScok;	// 服务端Socket
	SOCKET clientSock;	// 客户端Socket
	string data;		// 收到的数据
	// 【1】初始化WinSock  initWinSock();
	// 【2】创建socket  createSocket(listenScok);
	// 【3】socket绑定本机地址信息  bindIPandPort(listenScok, "127.0.0.1", 1994);
	// 【4】侦听socket，接收客户端请求
	
	if (initWinSock() == TRUE && createSocket(listenScok) == TRUE && bindIPandPort(listenScok, "127.0.0.1", 1994) == TRUE) {
		listenSocket(listenScok);// 坐等客户端连接
		waitClientConnect(listenScok, clientSock);//[5]
		sendData(clientSock, "Server connection succeeded！！！\r\n");
		bool isReceiveData = false;
		isReceiveData = receiveData(clientSock, data);//接收数据
		if (isReceiveData == TRUE) {//数据只能采用全局变量收取，内置函数无法返回数值
			cout << data << endl;
		}
		closesocket(listenScok);
		WSACleanup();
	}
	else {
		MessageBoxA(NULL, "socket failed to create,program closes!!!", "error", 0);
		exit(0);
	}
	JTCPserver();
}

/*
bool isClientSockConnect = false;	// 是否有客户端连进来
bool isReceiveData = false;			// 是否接收数据成功
while (true)
{

	if (isClientSockConnect == FALSE)
	{
		// 【5】等待客户端连接
		isClientSockConnect = waitClientConnect(listenScok, clientSock);//客户端连接后就会改变isClientSockConnect == Ture
	}
	else
	{
		if (isReceiveData == FALSE)
		{
			// 【6】接收数据-阻塞
			isReceiveData = receiveData(clientSock, data);
			// 如果接收数据失败则断开
			if (isReceiveData == FALSE)
			{
				// 【7】停止套接字的接收、发送
				shutdownSocket(clientSock);
				cout << "等待客户端再连接..." << endl;
				isClientSockConnect = false; // 可以重连了
			}
			else {
				
				//receive_client_dataA = "\0";
				shutdownSocket(clientSock);
				isClientSockConnect = false;
			}
		}
		//// 【8】发送信息，连续不断的给客户端发送信息
		//cout << "从客户端发来的数据:" << receiveData(clientSock, data) << endl;
		
		if (isReceiveData && data == "@end#")// 【9】关闭相关
		{
			sendData(clientSock, "服务器关闭，感谢连接!!!\r\n");
			int err;
			err = closesocket(listenScok);
			if (err == SOCKET_ERROR || WSACleanup() != 0)// 关闭套接字，释放资源.停止使用WinSock库，释放对应资源
			{
				cout << "关闭socket失败！" << endl;
				exit(0);
			}
			else {
				JTCPserver();
				//程序不关闭，继续等待下一个客户端连接。
			}
			return 0;
		}
	}
}
*/
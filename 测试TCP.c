#include <iostream>
#include <cstdio>
#include <Winsock2.h>

#pragma comment(lib,"ws2_32.lib")

using namespace std;

int main()
{
    // 加载socket动态链接库(dll)
    WORD wVersionRequested;          //WORD就是十六位数据
    WSADATA wsaData;                 // 这结构是用于接收Windows Socket的结构信息的
    int err;

    wVersionRequested = MAKEWORD( 1, 1 );   // 请求1.1版本的WinSock库，返回一个word变量，实际上这个函数（宏）本身只是将俩个byte型合并成一个word型

    err = WSAStartup( wVersionRequested, &wsaData );//通过这个函数完成对winSocket的初始化
    if ( err != 0 ) {
        return -1;          
    }

    if ( LOBYTE( wsaData.wVersion ) != 1 || HIBYTE( wsaData.wVersion ) != 1 ) {
        // 检查这个低字节是不是1，高字节是不是1以确定是否我们所请求的1.1版本
        // 否则的话，调用WSACleanup()清除信息，结束函数
        WSACleanup( );
        return -1;
    }

    // 创建socket操作，建立流式套接字，返回套接字号sockClient
    // SOCKET socket(int af, int type, int protocol);
    // 第一个参数，指定地址簇(TCP/IP只能是AF_INET，也可写成PF_INET)
    // 第二个，选择套接字的类型(流式套接字)，第三个，特定地址家族相关协议（0为自动）
    SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);

    // 将套接字sockClient与远程主机相连
    // int connect( SOCKET s,  const struct sockaddr* name,  int namelen);
    // 第一个参数：需要进行连接操作的套接字
    // 第二个参数：设定所需要连接的地址信息
    // 第三个参数：地址的长度
    SOCKADDR_IN addrSrv;
    addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");      // 本地回路地址是127.0.0.1;
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(6000);
    connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

    char recvBuf[100];
    recv(sockClient, recvBuf, 100, 0);
    printf("%s\n", recvBuf);

    send(sockClient, "Attention: A Client has enter...\n", strlen("Attention: A Client has enter...\n")+1, 0);

    printf("我们可以聊二十句话");
    int n = 20;
    do{
        printf("\n还剩%d次：", n);
        char talk[100];
        printf("\nPlease enter what you want to say next(\"quit\"to exit):");
        gets(talk);
        send(sockClient, talk, strlen(talk)+1, 0);          // 发送信息

        char recvBuf[100];
        recv(sockClient, recvBuf, 100, 0);
        printf("%s Says: %s\n", "Server", recvBuf);     // 接收信息
    }while(--n);

    printf("End linking...\n");
    closesocket(sockClient);
    WSACleanup();   // 终止对套接字库的使用

    printf("\n");
    system("pause");
    return 0;
}


#include "stdafx.h"
#include <iostream>
#include <string>
#include <WinSock2.h> // WinSocket 
#include <WS2tcpip.h> // IP地址转换用到inet_pton
#pragma comment(lib,"ws2_32.lib")  
using namespace std;

// 【1】初始化WinSock
bool initWinSock();
// 【2】创建socket
bool createSocket(SOCKET& listenScok);
// 【3】socket绑定本机地址信息
bool bindIPandPort(SOCKET& listenScok, const string ip, const unsigned short port);
// 【4】侦听socket，接收客户端请求
bool listenSocket(SOCKET& listenScok);
// 【5】等待客户端连接-阻塞
bool waitClientConnect(SOCKET& listenScok, SOCKET& clientSock);
// 【6】接收数据-阻塞
bool receiveData(SOCKET& clientSock, string& data);
// 【7】停止套接字的接收、发送
bool shutdownSocket(SOCKET& clientSock);
// 【8】发送信息
bool sendData(SOCKET& clientSock, const string& data);

int JTCPserver()
{
	SOCKET listenScok;	// 服务端Socket
	SOCKET clientSock;	// 客户端Socket
	string data;		// 收到的数据

	// 【1】初始化WinSock
	initWinSock();
	// 【2】创建socket
	createSocket(listenScok);
	// 【3】socket绑定本机地址信息
	bindIPandPort(listenScok, "127.0.0.1", 1994);
	// 【4】侦听socket，接收客户端请求
	listenSocket(listenScok);

	// 坐等客户端连接
	bool isClientSockConnect = false;	// 是否有客户端连进来
	bool isReceiveData = false;			// 是否接收数据成功

	while (true)
	{
		if (!isClientSockConnect)
		{
			// 【5】等待客户端连接
			isClientSockConnect = waitClientConnect(listenScok, clientSock);
		}
		else
		{
			if (!isReceiveData)
			{
				// 【6】接收数据-阻塞
				isReceiveData = receiveData(clientSock, data);
				// 如果接收数据失败则断开
				if (!isReceiveData)
				{
					// 【7】停止套接字的接收、发送
					shutdownSocket(clientSock);
					cout << "等待客户端再连接..." << endl;
					isClientSockConnect = false; // 可以重连了
				}
			}
			if (isReceiveData && data != "jfzpoi" && data != "@end#")
			{
				isReceiveData = false;
			}
			if (isReceiveData && data == "jfzpoi")
			{
				// 【8】发送信息(收的数据为jfzpoi)
				sendData(clientSock, "sandeepin!\r\n");
				isReceiveData = false;
			}
			if (isReceiveData && data == "@end#")
			{
				// 【9】关闭相关
				int err;
				//				err = shutdown(listenScok, 2);
				//				if (err == SOCKET_ERROR)
				//				{
				//					cout << "关闭失败！" << endl;
				//				}
								// 关闭套接字，释放资源
				err = closesocket(listenScok);
				if (err == SOCKET_ERROR)
				{
					cout << "关闭socket失败！" << endl;
				}
				// 停止使用WinSock库，释放对应资源
				if (WSACleanup() != 0)
				{
					cout << "WSA清空失败！" << endl;
				}
				cout << "关完了，坐等关机！poi" << endl;
				return 0;
			}
		}
	}
}

// 【1】初始化WinSock
bool initWinSock()
{
	WORD verision = MAKEWORD(2, 2);
	WSADATA lpData;
	int intEr = WSAStartup(verision, &lpData); // 指定winsock版本并初始化
	if (intEr != 0)
	{
		cout << "WinSock初始化失败！" << endl;
		return false;
	}
	cout << "WinSock初始化成功！" << endl;
	return true;
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
	cout << "socket创建成功！" << endl;
	return true;
}

// 【3】socket绑定本机地址信息
bool bindIPandPort(SOCKET& listenScok, const string ip, const unsigned short port)
{
	// 制作sockaddr_in结构体
	// 在bind函数，connect函数里提到了套接字编程网络地址信息结构体const struct sockaddr和const struct sockaddr_i
	sockaddr_in hostAddr;
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
	hostAddr.sin_addr = addr;
	cout << "ip(网络字节序):" << addr.S_un.S_addr << endl;
	cout << "ip(常规形式):" << ip.c_str() << endl;

	// 侦听套接字listenSock绑定本机地址信息  
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
	cout << "监听客户端连接中……" << endl;
	return true;
}

// 【5】等待客户端连接-阻塞
bool waitClientConnect(SOCKET& listenScok, SOCKET& clientSock)
{
	sockaddr_in clientAddr;
	int len = sizeof(struct sockaddr); // 必须指定长度，否则会导致accept返回10014错误
									   // accept会循环等待客户端连接
	clientSock = accept(listenScok, (struct sockaddr*)&clientAddr, &len);
	cout << "客户端Socket编号:" << clientSock << endl;
	if (clientSock == INVALID_SOCKET)
	{
		cout << "客户端连接失败！" << endl;
		cout << WSAGetLastError() << endl;
		return false;
	}
	return true;
}

// 【6】接收数据-阻塞
bool receiveData(SOCKET& clientSock, string& data)
{
	static int cnt = 1; // 接收数据编号-静态
						// 通过已建立连接的套接字，接收数据 设定缓冲1024字节
	char buf[1024] = "\0";
	// flags操作方式（0正常数据，MSG_PEED系统缓冲区的数据复制到所提供的接收缓冲区内，系统缓冲区数据未删除，MSG_OOB处理带外数据，通常用参数0即可）
	int buflen = recv(clientSock, buf, 1024, 0);
	if (buflen == SOCKET_ERROR)
	{
		cout << "接收失败！" << endl;
		return false;
	}
	// 一切正常则显示接收数据
	data = string(buf);
	cout << "收到第" << cnt++ << "次，内容为:\n" << buf << endl;
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
	cout << "发送数据为:\n" << data << endl;
	return true;

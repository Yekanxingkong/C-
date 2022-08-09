#include <iostream>
#include <cstdio>
#include <Winsock2.h>

#pragma comment(lib,"ws2_32.lib")

using namespace std;

int main()
{
    // ����socket��̬���ӿ�(dll)
    WORD wVersionRequested;          //WORD����ʮ��λ����
    WSADATA wsaData;                 // ��ṹ�����ڽ���Windows Socket�Ľṹ��Ϣ��
    int err;

    wVersionRequested = MAKEWORD( 1, 1 );   // ����1.1�汾��WinSock�⣬����һ��word������ʵ��������������꣩����ֻ�ǽ�����byte�ͺϲ���һ��word��

    err = WSAStartup( wVersionRequested, &wsaData );//ͨ�����������ɶ�winSocket�ĳ�ʼ��
    if ( err != 0 ) {
        return -1;          
    }

    if ( LOBYTE( wsaData.wVersion ) != 1 || HIBYTE( wsaData.wVersion ) != 1 ) {
        // ���������ֽ��ǲ���1�����ֽ��ǲ���1��ȷ���Ƿ������������1.1�汾
        // ����Ļ�������WSACleanup()�����Ϣ����������
        WSACleanup( );
        return -1;
    }

    // ����socket������������ʽ�׽��֣������׽��ֺ�sockClient
    // SOCKET socket(int af, int type, int protocol);
    // ��һ��������ָ����ַ��(TCP/IPֻ����AF_INET��Ҳ��д��PF_INET)
    // �ڶ�����ѡ���׽��ֵ�����(��ʽ�׽���)�����������ض���ַ�������Э�飨0Ϊ�Զ���
    SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);

    // ���׽���sockClient��Զ����������
    // int connect( SOCKET s,  const struct sockaddr* name,  int namelen);
    // ��һ����������Ҫ�������Ӳ������׽���
    // �ڶ����������趨����Ҫ���ӵĵ�ַ��Ϣ
    // ��������������ַ�ĳ���
    SOCKADDR_IN addrSrv;
    addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");      // ���ػ�·��ַ��127.0.0.1;
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(6000);
    connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

    char recvBuf[100];
    recv(sockClient, recvBuf, 100, 0);
    printf("%s\n", recvBuf);

    send(sockClient, "Attention: A Client has enter...\n", strlen("Attention: A Client has enter...\n")+1, 0);

    printf("���ǿ����Ķ�ʮ�仰");
    int n = 20;
    do{
        printf("\n��ʣ%d�Σ�", n);
        char talk[100];
        printf("\nPlease enter what you want to say next(\"quit\"to exit):");
        gets(talk);
        send(sockClient, talk, strlen(talk)+1, 0);          // ������Ϣ

        char recvBuf[100];
        recv(sockClient, recvBuf, 100, 0);
        printf("%s Says: %s\n", "Server", recvBuf);     // ������Ϣ
    }while(--n);

    printf("End linking...\n");
    closesocket(sockClient);
    WSACleanup();   // ��ֹ���׽��ֿ��ʹ��

    printf("\n");
    system("pause");
    return 0;
}


#include "stdafx.h"
#include <iostream>
#include <string>
#include <WinSock2.h> // WinSocket 
#include <WS2tcpip.h> // IP��ַת���õ�inet_pton
#pragma comment(lib,"ws2_32.lib")  
using namespace std;

// ��1����ʼ��WinSock
bool initWinSock();
// ��2������socket
bool createSocket(SOCKET& listenScok);
// ��3��socket�󶨱�����ַ��Ϣ
bool bindIPandPort(SOCKET& listenScok, const string ip, const unsigned short port);
// ��4������socket�����տͻ�������
bool listenSocket(SOCKET& listenScok);
// ��5���ȴ��ͻ�������-����
bool waitClientConnect(SOCKET& listenScok, SOCKET& clientSock);
// ��6����������-����
bool receiveData(SOCKET& clientSock, string& data);
// ��7��ֹͣ�׽��ֵĽ��ա�����
bool shutdownSocket(SOCKET& clientSock);
// ��8��������Ϣ
bool sendData(SOCKET& clientSock, const string& data);

int JTCPserver()
{
	SOCKET listenScok;	// �����Socket
	SOCKET clientSock;	// �ͻ���Socket
	string data;		// �յ�������

	// ��1����ʼ��WinSock
	initWinSock();
	// ��2������socket
	createSocket(listenScok);
	// ��3��socket�󶨱�����ַ��Ϣ
	bindIPandPort(listenScok, "127.0.0.1", 1994);
	// ��4������socket�����տͻ�������
	listenSocket(listenScok);

	// ���ȿͻ�������
	bool isClientSockConnect = false;	// �Ƿ��пͻ���������
	bool isReceiveData = false;			// �Ƿ�������ݳɹ�

	while (true)
	{
		if (!isClientSockConnect)
		{
			// ��5���ȴ��ͻ�������
			isClientSockConnect = waitClientConnect(listenScok, clientSock);
		}
		else
		{
			if (!isReceiveData)
			{
				// ��6����������-����
				isReceiveData = receiveData(clientSock, data);
				// �����������ʧ����Ͽ�
				if (!isReceiveData)
				{
					// ��7��ֹͣ�׽��ֵĽ��ա�����
					shutdownSocket(clientSock);
					cout << "�ȴ��ͻ���������..." << endl;
					isClientSockConnect = false; // ����������
				}
			}
			if (isReceiveData && data != "jfzpoi" && data != "@end#")
			{
				isReceiveData = false;
			}
			if (isReceiveData && data == "jfzpoi")
			{
				// ��8��������Ϣ(�յ�����Ϊjfzpoi)
				sendData(clientSock, "sandeepin!\r\n");
				isReceiveData = false;
			}
			if (isReceiveData && data == "@end#")
			{
				// ��9���ر����
				int err;
				//				err = shutdown(listenScok, 2);
				//				if (err == SOCKET_ERROR)
				//				{
				//					cout << "�ر�ʧ�ܣ�" << endl;
				//				}
								// �ر��׽��֣��ͷ���Դ
				err = closesocket(listenScok);
				if (err == SOCKET_ERROR)
				{
					cout << "�ر�socketʧ�ܣ�" << endl;
				}
				// ֹͣʹ��WinSock�⣬�ͷŶ�Ӧ��Դ
				if (WSACleanup() != 0)
				{
					cout << "WSA���ʧ�ܣ�" << endl;
				}
				cout << "�����ˣ����ȹػ���poi" << endl;
				return 0;
			}
		}
	}
}

// ��1����ʼ��WinSock
bool initWinSock()
{
	WORD verision = MAKEWORD(2, 2);
	WSADATA lpData;
	int intEr = WSAStartup(verision, &lpData); // ָ��winsock�汾����ʼ��
	if (intEr != 0)
	{
		cout << "WinSock��ʼ��ʧ�ܣ�" << endl;
		return false;
	}
	cout << "WinSock��ʼ���ɹ���" << endl;
	return true;
}

// ��2������socket
bool createSocket(SOCKET& listenScok)
{
	// ��������socket  
	listenScok = socket(AF_INET, SOCK_STREAM, 0);
	if (listenScok == INVALID_SOCKET)
	{
		cout << "socket����ʧ�ܣ�" << endl;
		return false;
	}
	cout << "socket�����ɹ���" << endl;
	return true;
}

// ��3��socket�󶨱�����ַ��Ϣ
bool bindIPandPort(SOCKET& listenScok, const string ip, const unsigned short port)
{
	// ����sockaddr_in�ṹ��
	// ��bind������connect�������ᵽ���׽��ֱ�������ַ��Ϣ�ṹ��const struct sockaddr��const struct sockaddr_i
	sockaddr_in hostAddr;
	hostAddr.sin_family = AF_INET;
	hostAddr.sin_port = htons(port);//ת���������ֽ���  
									//hostAddr.sin_addr.S_un.S_addr = inet_addr(SERVERIP);//ת���������ֽ���  
									//cout << "net IP:" << hostAddr.sin_addr.S_un.S_addr << endl;  
									/*
									inet_addr()�汾̫�ͣ�������ʹ��inet_pton(Э���壬�ַ���IP��ַ��voidĿ��in_addr*)
									ͷ�ļ���WS2tcpip.h
									*/
	in_addr addr;
	inet_pton(AF_INET, ip.c_str(), (void*)&addr);
	hostAddr.sin_addr = addr;
	cout << "ip(�����ֽ���):" << addr.S_un.S_addr << endl;
	cout << "ip(������ʽ):" << ip.c_str() << endl;

	// �����׽���listenSock�󶨱�����ַ��Ϣ  
	int err = bind(listenScok, (struct sockaddr*)&hostAddr, sizeof(sockaddr));
	if (err != 0)
	{
		cout << "����IP��ʧ�ܣ�" << endl;
		return false;
	}
	return true;
}

// ��4������socket�����տͻ�������
bool listenSocket(SOCKET& listenScok)
{
	// �趨�׽���Ϊ����״̬��׼�����տͻ������̷���������������
	int err = listen(listenScok, 3);
	if (err != 0)
	{
		cout << "socket����ʧ�ܣ�" << endl;
		return false;
	}
	cout << "�����ͻ��������С���" << endl;
	return true;
}

// ��5���ȴ��ͻ�������-����
bool waitClientConnect(SOCKET& listenScok, SOCKET& clientSock)
{
	sockaddr_in clientAddr;
	int len = sizeof(struct sockaddr); // ����ָ�����ȣ�����ᵼ��accept����10014����
									   // accept��ѭ���ȴ��ͻ�������
	clientSock = accept(listenScok, (struct sockaddr*)&clientAddr, &len);
	cout << "�ͻ���Socket���:" << clientSock << endl;
	if (clientSock == INVALID_SOCKET)
	{
		cout << "�ͻ�������ʧ�ܣ�" << endl;
		cout << WSAGetLastError() << endl;
		return false;
	}
	return true;
}

// ��6����������-����
bool receiveData(SOCKET& clientSock, string& data)
{
	static int cnt = 1; // �������ݱ��-��̬
						// ͨ���ѽ������ӵ��׽��֣��������� �趨����1024�ֽ�
	char buf[1024] = "\0";
	// flags������ʽ��0�������ݣ�MSG_PEEDϵͳ�����������ݸ��Ƶ����ṩ�Ľ��ջ������ڣ�ϵͳ����������δɾ����MSG_OOB����������ݣ�ͨ���ò���0���ɣ�
	int buflen = recv(clientSock, buf, 1024, 0);
	if (buflen == SOCKET_ERROR)
	{
		cout << "����ʧ�ܣ�" << endl;
		return false;
	}
	// һ����������ʾ��������
	data = string(buf);
	cout << "�յ���" << cnt++ << "�Σ�����Ϊ:\n" << buf << endl;
	return true;
}

// ��7��ֹͣ�׽��ֵĽ��ա�����
bool shutdownSocket(SOCKET& clientSock)
{
	//������͹أ�ֹͣ�׽��ֵĽ��ա����͹��ܣ�0��ֹ���գ�1��ֹ���ͣ�2���ƽ��շ��ͣ�
	int err = shutdown(clientSock, 2);
	if (err == SOCKET_ERROR)
	{
		cout << "�ر�Socketʧ�ܣ�" << endl;
		return false;
	}
	return true;
}

// ��8��������Ϣ
bool sendData(SOCKET& clientSock, const string& data)
{

	int err = send(clientSock, data.c_str(), data.size(), 0);
	if (err == SOCKET_ERROR)
	{
		cout << "����ʧ�ܣ�" << endl;
		return false;
	}
	cout << "��������Ϊ:\n" << data << endl;
	return true;

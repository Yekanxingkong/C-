#include <iostream>
#include <WinSock2.h>  
#include <WS2tcpip.h>  
#include <stdio.h>
#include <cstdio>
#include <windows.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

// ��1����ʼ��WinSock
bool initWinSockC()
{
	WORD verision = MAKEWORD(2, 2);
	WSADATA lpData;
	int intEr = WSAStartup(verision, &lpData); // ָ��winsock�汾����ʼ��
	if (intEr != 0)
	{
		cout << "WinSock��ʼ��ʧ�ܣ�" << endl;
		return false;
	}
	return true;
}

// ��2������socket
bool createSocketC(SOCKET& listenScok)
{ 
	listenScok = socket(AF_INET, SOCK_STREAM, 0);
	if (listenScok == INVALID_SOCKET)
	{
		cout << "socket����ʧ�ܣ�" << endl;
		return false;
	}
	return true;
}

// ��3�����ӵ�������
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
		cout << "���ӷ�����ʧ�ܣ�" << endl;
		return false;
	}
	return true;
}

// ��4����������
bool sendDataC(SOCKET& clientSock, const string& data)
{
	int err = send(clientSock, data.c_str(), data.size(), 0);
	if (err == SOCKET_ERROR)
	{
		cout << "����ʧ�ܣ�" << endl;
		return false;
	}
	return true;
}

// ��5����������
bool receiveDataC(SOCKET& clientSock, string& data)
{
	static int cnt = 1; // �������ݱ��-��̬
	char buf[1024] = "\0";// ͨ���ѽ������ӵ��׽��֣��������� �趨����1024�ֽ�
	// flags������ʽ��0�������ݣ�MSG_PEEDϵͳ�����������ݸ��Ƶ����ṩ�Ľ��ջ������ڣ�ϵͳ����������δɾ����MSG_OOB����������ݣ�ͨ���ò���0���ɣ�
	int buflen = recv(clientSock, buf, 1024, 0);
	if (buflen == SOCKET_ERROR)
	{
		cout << "����ʧ�ܣ�" << endl;
		return false;
	}
	data = string(buf);	// һ�������򷵻ؽ�������
	return true;
}

int TCP_client()
{
	SOCKET clientSock;	// �ͻ���Socket
	string data;
	string str;
	if (initWinSockC() == TRUE && createSocketC(clientSock) == TRUE && connectSocketC(clientSock, "127.0.0.1", 1994) == TRUE) {
		//cout << "���������ӳɹ�" << endl;
		receiveDataC(clientSock, data);//���շ���������
		cout <<  data << endl;
		cout << "Please enter the activation code :" << endl;
		cin >> str;
		sendDataC(clientSock, str);//���ͱ�������
		WSACleanup();
		TCP_client();
	}
	else{
		MessageBoxA(NULL, "Unable to connect to the Internet, please check the network and try again!!!", "error", 0);
		exit(0);
	}
	return 0;
}


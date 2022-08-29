#include <iostream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h> 
#include <windows.h>
//#include "stdafx.h"

#pragma comment(lib,"ws2_32.lib")  
using namespace std;

// ��1����ʼ��WinSock
bool initWinSock()
{
	WORD verision;//ʮ��λ���� ,�Զ�������
	WSADATA lpData;// ��ṹ�����ڽ���Windows Socket�Ľṹ��Ϣ��,�Զ�������
	verision = MAKEWORD(2, 2);// ����2.2�汾��WinSock�⣬����һ��word������ʵ��������������꣩����ֻ�ǽ�����byte�ͺϲ���һ��word��
	int intEr = WSAStartup(verision, &lpData); // ָ��winsock�汾����ʼ��
	if (intEr != 0)// ����ֵΪ���ʱ���Ǳ�ʾ�ɹ�����WSAStartup
	{
		cout << "socket��ʼ��ʧ�ܣ�" << endl;
		return false;
	}
	return true;
	/*cout << LOBYTE(lpData.wVersion) << "||" << HIBYTE(lpData.wVersion) << endl;
	if (LOBYTE(lpData.wVersion) != 2 || HIBYTE(lpData.wVersion) != 2) {// ���������ֽ��ǲ���1�����ֽ��ǲ���1��ȷ���Ƿ������������1.1�汾
		WSACleanup();
		exit(0);
	}*/
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
	//cout << "socket�����ɹ���" << endl;
	return true;
}

// ��3��socket�󶨱�����ַ��Ϣ
bool bindIPandPort(SOCKET& listenScok, const string ip, const unsigned short port)
{
	// ����sockaddr_in�ṹ��
	// ��bind������connect�������ᵽ���׽��ֱ�������ַ��Ϣ�ṹ��const struct sockaddr��const struct sockaddr_i
	// ����socket������������ʽ�׽��֣������׽��ֺ�sockClient

	sockaddr_in hostAddr;
	//hostAddr.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
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
	// SOCKET socket(int af, int type, int protocol);
	// ��һ��������ָ����ַ��(TCP/IPֻ����AF_INET��Ҳ��д��PF_INET)
	// �ڶ�����ѡ���׽��ֵ�����(��ʽ�׽���)�����������ض���ַ�������Э�飨0Ϊ�Զ���
	hostAddr.sin_addr = addr;
	//cout << "ip(�����ֽ���):" << addr.S_un.S_addr << endl;
	//cout << "ip(������ʽ):" << ip.c_str() << endl;


	int err = bind(listenScok, (struct sockaddr*)&hostAddr, sizeof(sockaddr));
	// �����׽���listenSock�󶨱�����ַ��Ϣ  
	// int err( SOCKET s,  const struct sockaddr* name,  int namelen);
	// ��һ����������Ҫ�������Ӳ������׽���
	// �ڶ����������趨����Ҫ���ӵĵ�ַ��Ϣ
	// ��������������ַ�ĳ���
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
	//cout << "�����ͻ��������С���" << endl;
	return true;
}

// ��5���ȴ��ͻ�������
bool waitClientConnect(SOCKET& listenScok, SOCKET& clientSock)
{
	sockaddr_in clientAddr;
	int len = sizeof(struct sockaddr); // ����ָ�����ȣ�����ᵼ��accept����10014����				   
	clientSock = accept(listenScok, (struct sockaddr*)&clientAddr, &len);// accept��ѭ���ȴ��ͻ�������
	if (clientSock == INVALID_SOCKET)//
	{
		MessageBoxA(NULL, "waitClientConnect failed to create,program closes!!!", "error5", 0);
		exit(0);
	}
	cout << "�ͻ���Socket���:" << clientSock << endl;
	return true;
}

// ��6����������

bool receiveData(SOCKET& clientSock, string& data)
{
	char receive_client_dataA[1024] = "\0";
	//static int cnt = 1; // �������ݱ��-��̬
						// ͨ���ѽ������ӵ��׽��֣��������� �趨����1024�ֽ�
	// flags������ʽ��0�������ݣ�MSG_PEEDϵͳ�����������ݸ��Ƶ����ṩ�Ľ��ջ������ڣ�ϵͳ����������δɾ����MSG_OOB����������ݣ�ͨ���ò���0���ɣ�
	int buflen = recv(clientSock, receive_client_dataA, 1024, 0);
	if (buflen == SOCKET_ERROR)
	{
		cout << "�ͻ��˹رգ�" << endl;
		return false;
	}
	// һ����������ʾ��������
	//cout << data <<"||" << receive_client_dataA << endl;
	data = string(receive_client_dataA);
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
	return true;
}


int JTCPserver()
{
	SOCKET listenScok;	// �����Socket
	SOCKET clientSock;	// �ͻ���Socket
	string data;		// �յ�������
	// ��1����ʼ��WinSock  initWinSock();
	// ��2������socket  createSocket(listenScok);
	// ��3��socket�󶨱�����ַ��Ϣ  bindIPandPort(listenScok, "127.0.0.1", 1994);
	// ��4������socket�����տͻ�������
	
	if (initWinSock() == TRUE && createSocket(listenScok) == TRUE && bindIPandPort(listenScok, "127.0.0.1", 1994) == TRUE) {
		listenSocket(listenScok);// ���ȿͻ�������
		waitClientConnect(listenScok, clientSock);//[5]
		sendData(clientSock, "Server connection succeeded������\r\n");
		bool isReceiveData = false;
		isReceiveData = receiveData(clientSock, data);//��������
		if (isReceiveData == TRUE) {//����ֻ�ܲ���ȫ�ֱ�����ȡ�����ú����޷�������ֵ
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
bool isClientSockConnect = false;	// �Ƿ��пͻ���������
bool isReceiveData = false;			// �Ƿ�������ݳɹ�
while (true)
{

	if (isClientSockConnect == FALSE)
	{
		// ��5���ȴ��ͻ�������
		isClientSockConnect = waitClientConnect(listenScok, clientSock);//�ͻ������Ӻ�ͻ�ı�isClientSockConnect == Ture
	}
	else
	{
		if (isReceiveData == FALSE)
		{
			// ��6����������-����
			isReceiveData = receiveData(clientSock, data);
			// �����������ʧ����Ͽ�
			if (isReceiveData == FALSE)
			{
				// ��7��ֹͣ�׽��ֵĽ��ա�����
				shutdownSocket(clientSock);
				cout << "�ȴ��ͻ���������..." << endl;
				isClientSockConnect = false; // ����������
			}
			else {
				
				//receive_client_dataA = "\0";
				shutdownSocket(clientSock);
				isClientSockConnect = false;
			}
		}
		//// ��8��������Ϣ���������ϵĸ��ͻ��˷�����Ϣ
		//cout << "�ӿͻ��˷���������:" << receiveData(clientSock, data) << endl;
		
		if (isReceiveData && data == "@end#")// ��9���ر����
		{
			sendData(clientSock, "�������رգ���л����!!!\r\n");
			int err;
			err = closesocket(listenScok);
			if (err == SOCKET_ERROR || WSACleanup() != 0)// �ر��׽��֣��ͷ���Դ.ֹͣʹ��WinSock�⣬�ͷŶ�Ӧ��Դ
			{
				cout << "�ر�socketʧ�ܣ�" << endl;
				exit(0);
			}
			else {
				JTCPserver();
				//���򲻹رգ������ȴ���һ���ͻ������ӡ�
			}
			return 0;
		}
	}
}
*/
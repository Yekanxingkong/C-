#include <windows.h>
#include <iostream>
#include <string>
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
#include <algorithm>

#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) // ������ڵ�ַ
using namespace std;
/*
void func(char* buff, const std::string& list)
{
    ofstream outfile(buff, ofstream::app);
    //ofstream outfile("E:\\myfile.txt", ofstream::app);
    string temp = list;  //д������
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
*/
int main() {
    /*�ļ�д����־ʱ�䣬�Է��������Ϣ��cdk
    * ȥsql��ѯCDK
    * ɾ��SQL��ʹ�õ�CDK
    * ������
    */
	int mun = 0;
	while (mun == 0)
	{
		server_tcp(0);
	}
}


/*
* 
* 	string data;
	data = server_tcp(0);
	if (data.length() != 36) {
		char debug[] = "��һ�δ������ݣ�Ϊ�ͻ�������";
		server_tcp(1);
	}
	data = server_tcp(0);
	if (data.length() == 36) {
		char debug[] = "�ж����������ʲô";
		if (data == "uNQ0JU4P0uLBmCvFXHIq7BzzGV4BT6Mn8m4j" || mysql(data) == 1) {
			server_tcp(2);
		}
		else {
			server_tcp(1);
		}
		
	}	
	main();
* 
	if (data != "")
	{
		cout << "�ͻ������ݣ�" << data << endl;
		strcat_s(buff, "\\temp.log");
		time_t now = time(NULL);
		char str[26] = {};
		ctime_s(str, 26, &now);
		func(buff, str);//д��ϵͳʱ��
		func(buff, data);//д��ͻ�������
		func(buff, "\n");
		if (data.length() == 36) {
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
				sendData(clientSock, "succeed");//���ͳɹ�����
				closesocket(listenScok);
				closesocket(clientSock);
				WSACleanup();
			}
		}
		else {
			debug = "�ַ����ȳ��꣬�����ж�";
		}
	}
	_getcwd(buff, 250);
	strcat_s(buff, "\\cdk.op");
	remove(buff);*/
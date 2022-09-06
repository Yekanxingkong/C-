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

#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) // 设置入口地址
using namespace std;
/*
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
*/
int main() {
    /*文件写入日志时间，对方计算机信息和cdk
    * 去sql查询CDK
    * 删除SQL中使用的CDK
    * 服务器
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
		char debug[] = "第一次传输数据，为客户端数据";
		server_tcp(1);
	}
	data = server_tcp(0);
	if (data.length() == 36) {
		char debug[] = "判断这个数据是什么";
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
		cout << "客户端数据：" << data << endl;
		strcat_s(buff, "\\temp.log");
		time_t now = time(NULL);
		char str[26] = {};
		ctime_s(str, 26, &now);
		func(buff, str);//写入系统时间
		func(buff, data);//写入客户端数据
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
				sendData(clientSock, "succeed");//发送成功代码
				closesocket(listenScok);
				closesocket(clientSock);
				WSACleanup();
			}
		}
		else {
			debug = "字符长度超标，不予判断";
		}
	}
	_getcwd(buff, 250);
	strcat_s(buff, "\\cdk.op");
	remove(buff);*/
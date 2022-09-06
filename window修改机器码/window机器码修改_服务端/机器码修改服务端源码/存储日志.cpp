#include <iostream>
#include <string>
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
#include <algorithm>
#include <pah.h>
using namespace std;

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

void rend_log(string log) {
	struct stat buffer;
	char buff[250];
	_getcwd(buff, 250);
	strcat_s(buff, "\\Temp.log");
	//---------写入时间------------
	time_t now = time(NULL);
	char time_str[26] = {};
	ctime_s(time_str, 26, &now);
	string str = time_str;
	str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());//去除空格换行符
	func(buff, str);
	//func(buff, "\n");
	func(buff, log);
}
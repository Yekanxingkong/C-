// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include<iostream>
#include <cstring>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>
#include <direct.h>
#include <sys/stat.h>
#include <io.h>
#include <process.h>
#include <stdio.h>
#include <windows.h>
#include <ctime>
#include <random>
using namespace std;
// 当使用预编译的头时，需要使用此源文件，编译才能成功。

int myAdd(int n, int m)
{
    return n + m;
}

int mySub(int n, int m)
{
    return n - m;
}


char* rand_str_A(char* str, const int len)
{
    srand((unsigned)time(NULL) * 10);
    int i;
    for (i = 0; i < len; ++i)
    {
        switch ((rand() % 2))
        {
        case 1:
            str[i] = 'A' + rand() % 26;
            break;
            //case 2:
            //str[i]='a' + rand() % 26;
            //break;
        default:
            str[i] = '0' + rand() % 10;
            break;
        }
    }
    i = ++i - 1;
    str[i] = '\0';
    return str;
}

char* rand_str_math(char* str, const int len)
{
    srand(unsigned(time(NULL)));
    int i;
    for (i = 0; i < len; ++i)
    {
        switch ((rand() % 2))
        {
        case 1:
            str[i] = 'a' + rand() % 26;
            break;
            //case 2:
            //str[i]='a' + rand() % 26;
            //break;
        default:
            str[i] = '0' + rand() % 10;
            break;
        }
    }
    i = ++i - 1;
    str[i] = '\0';
    return str;
}



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
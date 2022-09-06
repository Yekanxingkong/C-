// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H


//---------------------第一种声明-----------------
//#pragma  once 
//#ifdef PCH_H
//#define myAdd  _declspec(dllexport) 
//#else 
//#define mySub  _declspec(dllimport) 
//#endif 
//---------------------第一种声明-----------------

//---------------------第二种声明-----------------
//#ifndef PCH_H
//#define PCH_H
//#define myAdd extern "C" __declspec(dllexport) 
//#else
//#define mySub extern "C" __declspec(dllimport)
//#endif
//---------------------第二种声明-----------------

// 添加要在此处预编译的标头
#include "framework.h"

extern "C"
{
    _declspec(dllexport) int myAdd(int n, int m);
    _declspec(dllexport) int mySub(int n, int m);
    _declspec(dllexport) char* rand_str_A(char* str, int len);
    _declspec(dllexport) char* rand_str_math(char* str, int len);
};

#endif //PCH_H

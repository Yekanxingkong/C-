#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <windows.h>
#include <TlHelp32.h>
#include <string>
#include <atlstr.h>
using namespace std;
/*
***********************************************************************
* 函数： TCHAR2Char
* 描述：将TCHAR* 转换为 char*
* 日期：
***********************************************************************
*/
char* TCHAR2char(TCHAR* tchStr)
{
    int iLen = 2 * wcslen(tchStr);//CString,TCHAR汉字算一个字符，因此不用普通计算长度
    char* chRtn = new char[iLen + 1];
        wcstombs(chRtn, tchStr, iLen + 1);//转换成功返回为非负值
    return chRtn;
}
/*
***********************************************************************
* 函数： char2tchar
* 描述：将 char* 转换为 TCHAR*
* 日期：
***********************************************************************
*/
TCHAR* char2tchar(char* str)
{
    int iLen = strlen(str);
    TCHAR* chRtn = new TCHAR[iLen + 1];
    mbstowcs(chRtn, str, iLen + 1); return chRtn;
}
/*
***********************************************************************
* 函数： GetProcessIDByName()
* 描述：将 char* 转换为 TCHAR*
* 日期：
* char str[] = "notepad.exe";
* char* e = str;
* GetProcessIDByName(char2tchar(e));
***********************************************************************
*/
ULONG GetProcessIDByNameA(TCHAR* ProcessName)
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    //拍摄进程的快照，取自头文件tlhelp32.h
    if (INVALID_HANDLE_VALUE == hSnapshot) {
        //无效的句柄,返回值为-1
        return NULL;
    }
    PROCESSENTRY32 tagPROCESSENTRY32 = { sizeof(tagPROCESSENTRY32) };
    tagPROCESSENTRY32.dwSize = sizeof(tagPROCESSENTRY32);
    //在调用 Process32First函数之前，将此成员设置为sizeof(PROCESSENTRY32). 如果您不初始化dwSize， Process32First将失败。
    for (BOOL ret = Process32First(hSnapshot, &tagPROCESSENTRY32); ret; ret = Process32Next(hSnapshot, &tagPROCESSENTRY32)) {
        CString e = ProcessName;//atlstr.h
        if (tagPROCESSENTRY32.szExeFile == e) {//取进程的名称
            CloseHandle(hSnapshot);//释放内存，关闭快照
            
            return tagPROCESSENTRY32.th32ProcessID;//返回进程的PID
        }
        else {
            char debug;
            //printf("%-6d %s\n", pe.th32ProcessID, pe.szExeFile);
        }
    }
    CloseHandle(hSnapshot);
    return 0;
}
int GetProcessIDByName(string str) {
    char* c = const_cast<char*>(str.c_str());
    return GetProcessIDByNameA(char2tchar(c));
}



int main() {
    cout<<GetProcessIDByName("notepad.exe")<<endl;
    return 0;
}

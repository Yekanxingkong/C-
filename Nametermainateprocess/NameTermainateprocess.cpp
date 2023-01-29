#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <windows.h>
#include <TlHelp32.h>
#include <string>
#include <atlstr.h>
using namespace std;
/*
***********************************************************************
* ������ TCHAR2Char
* ��������TCHAR* ת��Ϊ char*
* ���ڣ�
***********************************************************************
*/
char* TCHAR2char(TCHAR* tchStr)
{
    int iLen = 2 * wcslen(tchStr);//CString,TCHAR������һ���ַ�����˲�����ͨ���㳤��
    char* chRtn = new char[iLen + 1];
        wcstombs(chRtn, tchStr, iLen + 1);//ת���ɹ�����Ϊ�Ǹ�ֵ
    return chRtn;
}
/*
***********************************************************************
* ������ char2tchar
* �������� char* ת��Ϊ TCHAR*
* ���ڣ�
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
* ������ GetProcessIDByName()
* �������� char* ת��Ϊ TCHAR*
* ���ڣ�
* char str[] = "notepad.exe";
* char* e = str;
* GetProcessIDByName(char2tchar(e));
***********************************************************************
*/
ULONG GetProcessIDByNameA(TCHAR* ProcessName)
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    //������̵Ŀ��գ�ȡ��ͷ�ļ�tlhelp32.h
    if (INVALID_HANDLE_VALUE == hSnapshot) {
        //��Ч�ľ��,����ֵΪ-1
        return NULL;
    }
    PROCESSENTRY32 tagPROCESSENTRY32 = { sizeof(tagPROCESSENTRY32) };
    tagPROCESSENTRY32.dwSize = sizeof(tagPROCESSENTRY32);
    //�ڵ��� Process32First����֮ǰ�����˳�Ա����Ϊsizeof(PROCESSENTRY32). ���������ʼ��dwSize�� Process32First��ʧ�ܡ�
    for (BOOL ret = Process32First(hSnapshot, &tagPROCESSENTRY32); ret; ret = Process32Next(hSnapshot, &tagPROCESSENTRY32)) {
        CString e = ProcessName;//atlstr.h
        if (tagPROCESSENTRY32.szExeFile == e) {//ȡ���̵�����
            CloseHandle(hSnapshot);//�ͷ��ڴ棬�رտ���
            
            return tagPROCESSENTRY32.th32ProcessID;//���ؽ��̵�PID
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

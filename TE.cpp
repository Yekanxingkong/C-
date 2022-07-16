#include <windows.h>
#include <iostream>
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
using namespace std;
char* rand_str(char* str, const int len)
{
    int i;
    for (i = 0; i < len; ++i)
    {
        switch ((rand() % 2))
        {
        case 1:
            str[i] = 'A' + rand() % 26;
            break;
            //case 2:
            //str[i]='a'+rand()%26;
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

void func(char* buff,const std::string& list)
{
    ofstream outfile(buff, ofstream::app);
    //ofstream outfile("E:\\myfile.txt", ofstream::app);
    string temp = list;  //Ð´ÈëÄÚÈÝ
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

int main() {
    struct stat buffer;
    int result;
    char buff[250];
    char name[20];
    _getcwd(buff, 250);
    strcat_s(buff, "\\SN.bat");
    result = stat(buff, &buffer);
    if (result != 0) {
        cout << "noft flie" << "\n";
    }
    else {
        //cout << "yea";
        if (remove(buff) == 0)
        {
            cout << "É¾³ý³É¹¦" << endl;
        }
        else
        {
            cout << "É¾³ýÊ§°Ü" << endl;
        }
    }
    char str1[] = "start\n\n>NUL 2>&1 REG.exe query \"HKU\\S-1-5-19\" || (\n    ECHO SET UAC = CreateObject^(\"Shell.Application\"^) > \"%TEMP%\\GetAdmin.vbs\"";
    char str2[] = "    ECHO UAC.ShellExecute \"%~f0\", \"%1\", \"\", \"runas\", 1 >> \"%TEMP%\GetAdmin.vbs\"\n    \"%TEMP%\GetAdmin.vbs\"\n    DEL /f /q \"%TEMP%\GetAdmin.vbs\" 2>NUL";
    char str3[] = "    Exit /b\n)\nCD /d %~dp0\n\nif %PROCESSOR_ARCHITECTURE%==AMD64 (set AMIDE=AMIDEWINx64.EXE) else (set AMIDE=AMIDEWIN.EXE)\n";
    func(buff, str1);
    func(buff, str2);
    func(buff, str3);
    char dmivar[8][250] = { "set \"DmiVar0100010500=",
     "set \"DmiVar0100010700=",
     "set \"DmiVar0100010600=",
     "set \"DmiVar0100011a00=",
     "set \"DmiVar0200020600=",
     "set \"DmiVar0300030800=",
     "set \"DmiVar0300030700=",
     "set \"DmiVar0300030900="
    };
    char str[30];
    for (auto &i : dmivar) {       
        if (i == dmivar[5] || i == dmivar[7]) {
            strcpy_s(str, rand_str(name, 17));
            strcat_s(str, "\"");
            strcat_s(i, str);
        }
        else {
            strcpy_s(str, rand_str(name, 15));
            strcat_s(str, "\"");
            strcat_s(i, str);
        }
        func(buff, i);
    }
    char str4[] = "\n%AMIDE% /SP \"%DmiVar0100010500%\"\n%AMIDE% /SS \"%DmiVar0100010700%\"\n%AMIDE% /SV \"%DmiVar0100010600%\"\n%AMIDE% /SF \"%DmiVar0100011a00%\"";
    char str5[] = "%AMIDE% /SU AUTO\n%AMIDE% /BV \"%DmiVar0200020600%\"\n%AMIDE% /CA \"%DmiVar0300030800%\"\n%AMIDE% /CS \"%DmiVar0300030700%\"\n%AMIDE% /BS \"%DmiVar0300030900%\"\n\nexit";
    func(buff, str4);
    func(buff, str5);
}
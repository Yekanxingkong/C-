#ifndef _UNISTD_H
#define _UNISTD_H
#include <iostream>
#include <windows.h>
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
char *rand_str(char *str,const int len)
{
    int i;
    for(i=0;i<len;++i)
    {
        switch((rand()%3))
        {
        case 1:
            str[i]='A'+rand()%26;
            break;
        //case 2:
        //str[i]='a'+rand()%26;
        //break;
        default:
            str[i]='0'+rand()%10;
            break;
        }
    }
    str[++i]='\0';
    return str;
}
std::string current_working_directory()
{
    char buff[250];
    _getcwd(buff, 250);
    std::string current_working_directory(buff);
    return current_working_directory;
}

void func(const std::string& list)
{
    string KO = current_working_directory() + "\\SN.bat";
    ofstream outfile((char*)KO.data(), ofstream::app);
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

std::string func()
{
    ifstream infile("D:\\Project3\\x64\\Debug\\SN.BAT");
    //ifstream infile("E:\\myfile.txt");
    std::string temp;
    if (!infile.is_open())
    {
        cout << "can not open the file \n" << endl;
        if(MessageBox(NULL,"can not open the file","Caption",MB_OK)==1){
            exit(0);
        }
    }
    while (getline(infile, temp))
    {
        cout << temp << "\n";
    }
    infile.close();
    return temp;
}

int main(void)
{
    struct stat buffer;
    int result;
    string KO = current_working_directory() + "\\SN.bat";
    //char working_ck[] = "D:\\Project3\\x64\\Debug\\ck.txt";
    result = stat((char*)KO.data(), &buffer );
    if(result != 0){
        cout << "not" << "\n";
    }else{
        //cout << "yea" << "\n";
        if(remove((char*)KO.data())==0)
        {
            cout<<"É¾³ý³É¹¦"<<endl;
        }else
        {
            cout<<"É¾³ýÊ§°Ü"<<endl;
        }
    }
    char str1[] = {"start\n\n>NUL 2>&1 REG.exe query \"HKU\\S-1-5-19\" || (\n"\
    "    ECHO SET UAC = CreateObject^(\"Shell.Application\"^) > \"%TEMP%\GetAdmin.vbs\"\n"\
    "    ECHO UAC.ShellExecute \"%~f0\", \"%1\", \"\", \"runas\", 1 >> \"%TEMP%\GetAdmin.vbs\"\n"\
    "    \"%TEMP%\GetAdmin.vbs\"\n"\
    "    DEL /f /q \"%TEMP%\GetAdmin.vbs\" 2>NUL\n"\
    "    Exit /b\n)\nCD /d %~dp0"\
    "\n\nif %PROCESSOR_ARCHITECTURE%==AMD64 (set AMIDE=AMIDEWINx64.EXE) else (set AMIDE=AMIDEWIN.EXE)\n"
    };
    func(str1);
    srand(unsigned(time(NULL)));
    char name[20];
    char* dmivar[8];
         dmivar[0]="set \"DmiVar0100010500=";
         dmivar[1]="set \"DmiVar0100010700=";
         dmivar[2]="set \"DmiVar0100010600=";
         dmivar[3]="set \"DmiVar0100011a00=";
         dmivar[4]="set \"DmiVar0200020600=";
         dmivar[5]="set \"DmiVar0300030800=";
         dmivar[6]="set \"DmiVar0300030700=";
         dmivar[7]="set \"DmiVar0300030900=";
    char strring[20]="\"";
    char str0[80];
    int i;
    for(i=0;i<8;++i)
    {
        if (i == 5 || i == 7)
            {
                sprintf(str0,"%s%s%s",dmivar[i],rand_str(name,17),strring);
                func(str0);
            }
        else{
            sprintf(str0,"%s%s%s",dmivar[i],rand_str(name,15),strring);
            func(str0);
        }
    }
    char str2[] = {"\n"\
    "%AMIDE% /SP \"%DmiVar0100010500%\"\n"\
    "%AMIDE% /SS \"%DmiVar0100010700%\"\n"\
    "%AMIDE% /SV \"%DmiVar0100010600%\"\n"\
    "%AMIDE% /SF \"%DmiVar0100011a00%\"\n"\
    "%AMIDE% /SU AUTO\n"\
    "%AMIDE% /BV \"%DmiVar0200020600%\"\n"\
    "%AMIDE% /CA \"%DmiVar0300030800%\"\n"\
    "%AMIDE% /CS \"%DmiVar0300030700%\"\n"\
    "%AMIDE% /BS \"%DmiVar0300030900%\"\n"\
    "\nexit"
    };
    func(str2);
    //cout << func() << "\n";
    system("pause");
    return 0;
}

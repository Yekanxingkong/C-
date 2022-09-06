#include <pah.h>
#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <direct.h>
#include <sys/stat.h>
#include <io.h>
#include <cassert>
#define _AFXDLL 
using namespace std;

int file_size(const char filepath[])
{
    struct _stat info;
    struct stat buffer;
    char buff[250];
    _getcwd(buff, 250);
    strcat_s(buff, filepath);
    _stat(buff, &info);
    int size = info.st_size;
    return size;
}
string reading_line_ckd;
void readTxt(string file)
{
    ifstream infile;
    infile.open(file.data());   //将文件流对象与文件连接起来 
    assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 
    string s;
    while (getline(infile, s))
    {
        reading_line_ckd = reading_line_ckd + s;
        cout << s << endl;
    }
    infile.close();             //关闭文件输入流 
}
int main() {
    const char* censor_namefile[] = {
        "\\AMIDEWIN.exe",
        "\\AMIDEWINx64.EXE",
        "\\AMIFLDRV32.SYS",
        "\\AMIFLDRV64.SYS",
        "\\MAC.exe",
        "\\机器码修改器.exe",
        "\\CDK_v3.dark",
        "\\rm_window.exe"
    };
    int i;
    int len;
    len = sizeof(censor_namefile) / sizeof(censor_namefile[0]);
    for (i = 0; i < len; i++)
    {
        if (if_resultle(censor_namefile[i]) != 0) {
            //检查文件是否存在，不存在则直接退出
            MessageBoxA(NULL, "A necessary component for the program to run is missing！", "error!!!", MB_OK);
            exit(0);
        }
    }
    //cout << file_size("\\AMIFLDRV32.SYS") << file_size("\\AMIFLDRV64.SYS") << file_size("\\MAC.exe") << endl;
    if (file_size("\\AMIDEWIN.exe") != 376944 && 
        file_size("\\AMIDEWINx64.EXE") != 462448 && 
        file_size("\\AMIFLDRV32.SYS") != 10240 && 
        file_size("\\AMIFLDRV64.SYS") != 29776 && 
        file_size("\\MAC.exe") != 17920 && 
        file_size("\\机器码修改器.exe") != 832512 &&
        file_size("\\rm_window.exe") != 182272
        ) {
        //校验文件大小，防止被恶意进程注入
        MessageBoxA(NULL, "Program security check failed！", "error!!!", MB_OK);
        exit(0);
    }
    //---------------------检查CDK是否正确，是否包含特殊字符-----------------------------------------
    struct stat buffer;
    char buff[250];
    _getcwd(buff, 250);
    strcat_s(buff, "\\CDK_v3.dark");
    readTxt(buff);
    if (strlen(reading_line_ckd.c_str()) == 36) {
        string rt = "";
        client_tcp(rt);
    }
    else {
        MessageBoxA(NULL, "The verification code is incorrect, please purchase the correct verification code！", "error!!!", MB_OK);
        exit(0);
    }
    //---------------------检查CDK是否正确，是否包含特殊字符-----------------------------------------
    if (checking_system() == 0) {
        MessageBoxA(NULL, "No available operating system identified, program ends！", "error!!!", MB_OK);
        exit(0);
    }
    else {
        if (client_tcp(reading_line_ckd) == 1) {
            leading_create_SN();
            cout << "success!!!:Machine code has been modified！" << endl;
            //MessageBoxA(NULL, "Machine code has been modified！", "success!!!", MB_OK);
            exit(0);
        }
        else {
            MessageBoxA(NULL, "Wrong or expired verification code！", "error!!!", MB_OK);
            exit(0);
        }
    }
}

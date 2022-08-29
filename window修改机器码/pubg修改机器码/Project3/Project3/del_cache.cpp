#include <io.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <queue>
#include <stack>
#include <iostream>
#include <Windows.h>
/////////////////
#include <stdlib.h>
#include <direct.h>
#include <string.h>
#include <io.h>
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <process.h>
#include <windows.h>
#include <Windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <ShellAPI.h>
using namespace std;

//判断是否是".."目录和"."目录
bool is_special_dir(const char* path)
{
    return strcmp(path, "..") == 0 || strcmp(path, ".") == 0;
}

//判断文件属性是目录还是文件
bool is_dir(int attrib)
{
    return attrib == 16 || attrib == 18 || attrib == 20;
}

//显示删除失败原因
void show_error(const char* file_name = NULL)
{
    errno_t err;
    _get_errno(&err);
    switch (err)
    {
    case ENOTEMPTY:
        printf("Given path is not a directory, the directory is not empty, or the directory is either the current working directory or the root directory.\n");
        break;
    case ENOENT:
        printf("Path is invalid.\n");
        break;
    case EACCES:
        printf("%s had been opend by some application, can't delete.\n", file_name);
        break;
    }
}

void get_file_path(const char* path, const char* file_name, char* file_path)
{
    strcpy_s(file_path, sizeof(char) * _MAX_PATH, path);
    file_path[strlen(file_path) - 1] = '\0';
    strcat_s(file_path, sizeof(char) * _MAX_PATH, file_name);
    strcat_s(file_path, sizeof(char) * _MAX_PATH, "\\*");
}

//递归搜索目录中文件并删除
//char* a = const_cast<char*>(str[0]);
//delete_file(a);
void delete_file(char* path)
{
    _finddata_t dir_info;
    _finddata_t file_info;
    intptr_t f_handle;
    char tmp_path[_MAX_PATH];
    if ((f_handle = _findfirst(path, &dir_info)) != -1)
    {
        while (_findnext(f_handle, &file_info) == 0)
        {
            if (is_special_dir(file_info.name))
            {
                continue;
            }
            if (is_dir(file_info.attrib))//如果是目录，生成完整的路径
            {
                get_file_path(path, file_info.name, tmp_path);
                delete_file(tmp_path);//开始递归删除目录中的内容
                tmp_path[strlen(tmp_path) - 2] = '\0';
                if (file_info.attrib == 20)
                    printf("This is system file, can't delete!\n");
                else
                {
                    //删除空目录，必须在递归返回前调用_findclose,否则无法删除目录
                    if (_rmdir(tmp_path) == -1)
                    {
                        show_error();//目录非空则会显示出错原因
                    }
                }
            }
            else
            {
                strcpy_s(tmp_path, path);
                tmp_path[strlen(tmp_path) - 1] = '\0';
                strcat_s(tmp_path, file_info.name);//生成完整的文件路径

                if (remove(tmp_path) == -1)
                {
                    show_error(file_info.name);
                }

            }
        }
        _findclose(f_handle);//关闭打开的文件句柄，并释放关联资源，否则无法删除空目录
    }
    else
    {
        show_error();//若路径不存在，显示错误信息
    }

    return;
}
//--------------------------------------------------------------------------------------------------------------------------
int  removeDir(string dirPath)
{
    struct _finddata_t fb;   //find the storage structure of the same properties file.
    string path;
    long    handle;
    int  resultone;
    int   noFile;            // the tag for the system's hidden files

    noFile = 0;
    handle = 0;

    path = dirPath + "/*";

    handle = _findfirst(path.c_str(), &fb);

    //find the first matching file
    if (handle != -1)
    {
        //find next matching file
        while (0 == _findnext(handle, &fb))
        {
            // "." and ".." are not processed
            noFile = strcmp(fb.name, "..");

            if (0 != noFile)
            {
                path.clear();
                path = dirPath + "/" + fb.name;

                //fb.attrib == 16 means folder
                if (fb.attrib == 16)
                {
                    removeDir(path);
                }
                else
                {
                    //not folder, delete it. if empty folder, using _rmdir istead.
                    remove(path.c_str());
                }
            }
        }
        // close the folder and delete it only if it is closed. For standard c, using closedir instead(findclose -> closedir).
        // when Handle is created, it should be closed at last.
        _findclose(handle);
        return 0;
    }
}





int delDir(const char* pDir)
{
    if (NULL == pDir)	return -1;
    char dir[MAX_PATH] = { 0 };
    char fileName[MAX_PATH] = { 0 };
    char* str = const_cast<char*>("\\*.*");
    strcpy_s(dir, pDir);
    strcat_s(dir, str);
    //首先查找dir中符合要求的文件
    long hFile;
    _finddata_t fileinfo;
    if ((hFile = _findfirst(dir, &fileinfo)) != -1)
    {
        do
        {
            strcpy_s(fileName, pDir);
            strcat_s(fileName, "\\");
            strcat_s(fileName, fileinfo.name);
            //检查是不是目录
            //如果不是目录,则进行处理文件夹下面的文件
            if (!(fileinfo.attrib & _A_SUBDIR))
            {
                remove(fileName);
            }
            else//处理目录，递归调用
            {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                {
                    delDir(fileName);
                    //rmdir(fileName);
                }
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
        _rmdir(pDir);
        return 1;
    }
    return -3;
}

DWORD pid = 0;
bool FindProcess(std::string strProcessName, DWORD& nPid)
{

    TCHAR tszProcess[64] = { 0 };
    lstrcpy(tszProcess, _T(strProcessName.c_str()));
    //查找进程
    STARTUPINFO st;
    PROCESS_INFORMATION pi;
    PROCESSENTRY32 ps;
    HANDLE hSnapshot;
    memset(&st, 0, sizeof(STARTUPINFO));
    st.cb = sizeof(STARTUPINFO);
    memset(&ps, 0, sizeof(PROCESSENTRY32));
    ps.dwSize = sizeof(PROCESSENTRY32);
    memset(&pi, 0, sizeof(PROCESS_INFORMATION));
    // 遍历进程 
    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
        return false;
    if (!Process32First(hSnapshot, &ps))
        return false;
    do {
        if (lstrcmp(ps.szExeFile, tszProcess) == 0)
        {
            //找到制定的程序
            nPid = ps.th32ProcessID;
            CloseHandle(hSnapshot);
            //printf("找到进程: %s\n", tszProcess);
            pid = nPid;
            return true;
        }
    } while (Process32Next(hSnapshot, &ps));
    CloseHandle(hSnapshot);
    return false;
}


bool KillProcess(DWORD dwPid)
{
    printf("Kill进程Pid = %d\n", dwPid); 
    //关闭进程
    HANDLE killHandle = OpenProcess(PROCESS_TERMINATE | PROCESS_QUERY_INFORMATION |   // Required by Alpha
        PROCESS_CREATE_THREAD |   // For CreateRemoteThread
        PROCESS_VM_OPERATION |   // For VirtualAllocEx/VirtualFreeEx
        PROCESS_VM_WRITE,             // For WriteProcessMemory);
        FALSE, dwPid);
    if (killHandle == NULL)
        return false;
    TerminateProcess(killHandle, 0);
    return true;
}

bool StartPrcess(std::string strProcessName)
{
    TCHAR tszProcess[64] = { 0 };
    lstrcpy(tszProcess, _T(strProcessName.c_str()));
    //启动程序
    SHELLEXECUTEINFO shellInfo;
    memset(&shellInfo, 0, sizeof(SHELLEXECUTEINFO));
    shellInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    shellInfo.fMask = NULL;
    shellInfo.hwnd = NULL;
    shellInfo.lpVerb = NULL;
    shellInfo.lpFile = tszProcess;                      // 执行的程序名(绝对路径)
    shellInfo.lpParameters = NULL;
    shellInfo.lpDirectory = NULL;
    shellInfo.nShow = SW_MINIMIZE;                      //SW_SHOWNORMAL 全屏显示这个程序
    shellInfo.hInstApp = NULL;
    printf("程序自动重启中.... \n");
    ShellExecuteEx(&shellInfo);

    return true;
}

void del_pubg_cache() {
    int i;
    int len;
    DWORD nPid = 0;
    const char* str_pid[] = {
    "steam.exe",
    "TXPlatform.exe",
    "CrossProxy.exe",
    "TenSafe_1.exe",
    "Client.exe",
    "BackgroundDownloader.exe",
    "TenioDL.exe",
    "uishell.exe"
    };
    len = sizeof(str_pid) / sizeof(str_pid[0]);//取数组索引
    for (i = 0; i < len; i++) {
        if (FindProcess(str_pid[i], nPid) == 1) {
            KillProcess(pid);
        }
        else {
            cout << "Running program not found,please contact the user" << endl;
        }
    }
	const char* str[] = {
    "C:\\Program Files\\Common Files\\PUBG",
    "C:\\Program Files\\Common Files\\UNCHEATER",
    "C:\\Program Files\\Common Files\\Wellbia.com",
    "C:\\Users\\ADMINI~1\\AppData\\Local\\WELLBIA",
    "C:\\Users\\ADMINI~1\\AppData\\Local\\TslGame",
    "C:\\Users\\ADMINI~1\\AppData\\Local\\Steam",
    "C:\\Program Files\\AntiCheatExpert"
	};
	len = sizeof(str) / sizeof(str[0]);//取数组索引
	for (i = 0; i < len; i++) 
	{
		if (_access(str[i], 0) == -1) {//判断文件夹是否存在
			cout << "don't find fileing" << endl;
		}
		else {
			cout << "have a find fileing,but cleaning up for you now,please wait patiently" << endl;
            delDir(str[i]);//清理非空文件夹
		}
	}
}
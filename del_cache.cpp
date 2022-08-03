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






void del_pubg_cache() {
	const char* str[] = {
    "C:\\Program Files\\Common Files\\PUBG",
    "C:\\Program Files\\Common Files\\UNCHEATER",
    "C:\\Program Files\\Common Files\\Wellbia.com",
    "C:\\Users\\ADMINI~1\\AppData\\Local\\WELLBIA",
    "C:\\Users\\ADMINI~1\\AppData\\Local\\TslGame",
    "C:\\Users\\ADMINI~1\\AppData\\Local\\Steam",
    "C:\\Program Files\\AntiCheatExpert"
	};
	int i;
	int len;
	len = sizeof(str) / sizeof(str[0]);
	for (i = 0; i < len; i++) 
	{
		if (_access(str[i], 0) == -1) {
			cout << "don't find fileing" << endl;
		}
		else {
			cout << "have a find fileing" << endl;
            

		}

	}
    char* a = const_cast<char*>(str[6]);
    delete_file(a);
    delDir(str[6]);//有效果
    cout << str[6] << removeDir(str[6])<< endl;
    
}
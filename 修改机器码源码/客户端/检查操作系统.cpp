#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <cstdio> 
#include <stdlib.h>
#include <string>
using namespace std;
typedef BOOL(WINAPI* LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
LPFN_ISWOW64PROCESS fnIsWow64Process = NULL;
char* getSystemName()
{
	//来源https://blog.csdn.net/qq78442761/article/details/64440535
	std::string vname;
	//先判断是否为win8.1或win10
	typedef void(__stdcall* NTPROC)(DWORD*, DWORD*, DWORD*);
	HINSTANCE hinst = LoadLibrary("ntdll.dll");//设置，配置属性-高级-字符集-未设置
	DWORD dwMajor, dwMinor, dwBuildNumber;
	NTPROC proc = (NTPROC)GetProcAddress(hinst, "RtlGetNtVersionNumbers");
	proc(&dwMajor, &dwMinor, &dwBuildNumber);
	if (dwMajor == 6 && dwMinor == 3)	//win 8.1
	{
		vname = "Microsoft Windows 8.1";
		//printf_s("此电脑的版本为:%s\n", vname.c_str());

	}
	if (dwMajor == 10 && dwMinor == 0)	//win 10
	{
		vname = "Microsoft Windows 10";
		//printf_s("此电脑的版本为:%s\n", vname.c_str());

	}
	//下面判断不能Win Server，因为本人还未有这种系统的机子，暂时不给出
	//判断win8.1以下的版本
	SYSTEM_INFO info;                //用SYSTEM_INFO结构判断64位AMD处理器  
	GetSystemInfo(&info);            //调用GetSystemInfo函数填充结构  
	OSVERSIONINFOEX os;
	os.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
#pragma warning(disable:4996)
	if (GetVersionEx((OSVERSIONINFO*)&os))
	{

		//下面根据版本信息判断操作系统名称  
		switch (os.dwMajorVersion)
		{                        //判断主版本号  
		case 4:
			switch (os.dwMinorVersion)
			{                //判断次版本号  
			case 0:
				if (os.dwPlatformId == VER_PLATFORM_WIN32_NT)
					vname = "Microsoft Windows NT 4.0";  //1996年7月发布  
				else if (os.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
					vname = "Microsoft Windows 95";
				break;
			case 10:
				vname = "Microsoft Windows 98";
				break;
			case 90:
				vname = "Microsoft Windows Me";
				break;
			}
			break;
		case 5:
			switch (os.dwMinorVersion)
			{               //再比较dwMinorVersion的值  
			case 0:
				vname = "Microsoft Windows 2000";    //1999年12月发布  
				break;
			case 1:
				vname = "Microsoft Windows XP";      //2001年8月发布  
				break;
			case 2:
				if (os.wProductType == VER_NT_WORKSTATION &&
					info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
					vname = "Microsoft Windows XP Professional x64 Edition";
				else if (GetSystemMetrics(SM_SERVERR2) == 0)
					vname = "Microsoft Windows Server 2003";   //2003年3月发布  
				else if (GetSystemMetrics(SM_SERVERR2) != 0)
					vname = "Microsoft Windows Server 2003 R2";
				break;
			}
			break;
		case 6:
			switch (os.dwMinorVersion)
			{
			case 0:
				if (os.wProductType == VER_NT_WORKSTATION)
					vname = "Microsoft Windows Vista";
				else
					vname = "Microsoft Windows Server 2008";   //服务器版本  
				break;
			case 1:
				if (os.wProductType == VER_NT_WORKSTATION)
					vname = "Microsoft Windows 7";
				else
					vname = "Microsoft Windows Server 2008 R2";
				break;
			case 2:
				if (os.wProductType == VER_NT_WORKSTATION)
					vname = "Microsoft Windows 8";
				else
					vname = "Microsoft Windows Server 2012";
				break;
			}
			break;
		default:
			vname = "未知操作系统";
			MessageBoxA(NULL, "无法获取计算机系统，请更换window7、8、10，错误代码:02！", "错误", MB_OK);
			exit(0);
		}
		//printf_s("此电脑的版本为:%s\n", vname.c_str());

	}
	else {
		vname = "版本获取失败";
		MessageBoxA(NULL, "未能够获取计算机版本信息，请联系管理员，错误代码:03！", "错误", MB_OK);
		exit(0);
	}
	char* str;
	str = strdup(vname.c_str());
	return str;
}


BOOL Isx64Application() {
	return (sizeof(LPFN_ISWOW64PROCESS) == 8) ? TRUE : FALSE;
}

BOOL IsWow64() {
	BOOL bIsWow64 = FALSE;
	if (!fnIsWow64Process)
		fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(GetModuleHandle(TEXT("kernel32")), "IsWow64Process");
	if (fnIsWow64Process)
		if (!fnIsWow64Process(GetCurrentProcess(), &bIsWow64))
			return FALSE;
	return bIsWow64;
}


int at() {
int no_os_flag = 1;
#ifdef linux
	MessageBoxA(NULL, "软件遭遇非法破解，启动格盘程序！！！", "遭遇入侵", MB_OK);
	exit(0);
    //cout << "Linux OS是无法运行的!" << endl;
#endif

#ifdef _UNIX
	MessageBoxA(NULL, "软件遭遇非法破解，启动格盘程序！！！", "遭遇入侵", MB_OK);
	exit(0);
    //cout << "UNIX OS是无法运行的!" << endl;
#endif

#ifdef __WINDOWS_
    no_os_flag = 0;
#endif

#ifdef _WIN32
    no_os_flag = 0;
#endif

#ifdef __APPLE__
	MessageBoxA(NULL, "软件遭遇非法破解，启动格盘程序！！！", "遭遇入侵", MB_OK);
	exit(0);
	//cout << "MAC OS是无法运行的!" << endl;
#endif

    if (1 == no_os_flag) {
        cout << "No OS Defined ,I do not know what the os is!" << endl;
		return 1;
    }else{
		if (Isx64Application()) {//启动一个64位的程序，检测是否能运行成功
			cout << "检测系统为 Windows x64,接下去获取系统信息：" << getSystemName() << endl;
		}else {
			cout << "检测系统为 Windows x86,接下去获取系统信息：" << getSystemName() << endl;
			//if (!IsWow64()) //32位操作系统中编译的32位应用程序
				//_tprintf(TEXT("The application is running under Windows x86.\n"));	
			//else  //64位操作系统中编译的32位应用程序
				//_tprintf(TEXT("The application is a x86 program running under Windows x64.\n"));		
		}
	}
	//char* a = getSystemName();
    return 0;
}

int add(int a, int b)
{
    return a + b;
}
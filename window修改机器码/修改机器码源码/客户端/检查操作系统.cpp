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
	//��Դhttps://blog.csdn.net/qq78442761/article/details/64440535
	std::string vname;
	//���ж��Ƿ�Ϊwin8.1��win10
	typedef void(__stdcall* NTPROC)(DWORD*, DWORD*, DWORD*);
	HINSTANCE hinst = LoadLibrary("ntdll.dll");//���ã���������-�߼�-�ַ���-δ����
	DWORD dwMajor, dwMinor, dwBuildNumber;
	NTPROC proc = (NTPROC)GetProcAddress(hinst, "RtlGetNtVersionNumbers");
	proc(&dwMajor, &dwMinor, &dwBuildNumber);
	if (dwMajor == 6 && dwMinor == 3)	//win 8.1
	{
		vname = "Microsoft Windows 8.1";
		//printf_s("�˵��Եİ汾Ϊ:%s\n", vname.c_str());

	}
	if (dwMajor == 10 && dwMinor == 0)	//win 10
	{
		vname = "Microsoft Windows 10";
		//printf_s("�˵��Եİ汾Ϊ:%s\n", vname.c_str());

	}
	//�����жϲ���Win Server����Ϊ���˻�δ������ϵͳ�Ļ��ӣ���ʱ������
	//�ж�win8.1���µİ汾
	SYSTEM_INFO info;                //��SYSTEM_INFO�ṹ�ж�64λAMD������  
	GetSystemInfo(&info);            //����GetSystemInfo�������ṹ  
	OSVERSIONINFOEX os;
	os.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
#pragma warning(disable:4996)
	if (GetVersionEx((OSVERSIONINFO*)&os))
	{

		//������ݰ汾��Ϣ�жϲ���ϵͳ����  
		switch (os.dwMajorVersion)
		{                        //�ж����汾��  
		case 4:
			switch (os.dwMinorVersion)
			{                //�жϴΰ汾��  
			case 0:
				if (os.dwPlatformId == VER_PLATFORM_WIN32_NT)
					vname = "Microsoft Windows NT 4.0";  //1996��7�·���  
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
			{               //�ٱȽ�dwMinorVersion��ֵ  
			case 0:
				vname = "Microsoft Windows 2000";    //1999��12�·���  
				break;
			case 1:
				vname = "Microsoft Windows XP";      //2001��8�·���  
				break;
			case 2:
				if (os.wProductType == VER_NT_WORKSTATION &&
					info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
					vname = "Microsoft Windows XP Professional x64 Edition";
				else if (GetSystemMetrics(SM_SERVERR2) == 0)
					vname = "Microsoft Windows Server 2003";   //2003��3�·���  
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
					vname = "Microsoft Windows Server 2008";   //�������汾  
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
			vname = "δ֪����ϵͳ";
			MessageBoxA(NULL, "�޷���ȡ�����ϵͳ�������window7��8��10���������:02��", "����", MB_OK);
			exit(0);
		}
		//printf_s("�˵��Եİ汾Ϊ:%s\n", vname.c_str());

	}
	else {
		vname = "�汾��ȡʧ��";
		MessageBoxA(NULL, "δ�ܹ���ȡ������汾��Ϣ������ϵ����Ա���������:03��", "����", MB_OK);
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
	MessageBoxA(NULL, "��������Ƿ��ƽ⣬�������̳��򣡣���", "��������", MB_OK);
	exit(0);
    //cout << "Linux OS���޷����е�!" << endl;
#endif

#ifdef _UNIX
	MessageBoxA(NULL, "��������Ƿ��ƽ⣬�������̳��򣡣���", "��������", MB_OK);
	exit(0);
    //cout << "UNIX OS���޷����е�!" << endl;
#endif

#ifdef __WINDOWS_
    no_os_flag = 0;
#endif

#ifdef _WIN32
    no_os_flag = 0;
#endif

#ifdef __APPLE__
	MessageBoxA(NULL, "��������Ƿ��ƽ⣬�������̳��򣡣���", "��������", MB_OK);
	exit(0);
	//cout << "MAC OS���޷����е�!" << endl;
#endif

    if (1 == no_os_flag) {
        cout << "No OS Defined ,I do not know what the os is!" << endl;
		return 1;
    }else{
		if (Isx64Application()) {//����һ��64λ�ĳ��򣬼���Ƿ������гɹ�
			cout << "���ϵͳΪ Windows x64,����ȥ��ȡϵͳ��Ϣ��" << getSystemName() << endl;
		}else {
			cout << "���ϵͳΪ Windows x86,����ȥ��ȡϵͳ��Ϣ��" << getSystemName() << endl;
			//if (!IsWow64()) //32λ����ϵͳ�б����32λӦ�ó���
				//_tprintf(TEXT("The application is running under Windows x86.\n"));	
			//else  //64λ����ϵͳ�б����32λӦ�ó���
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
#include   "stdafx.h"
#include "ProcessFunc.h"
#include "Process.h"
#include <tlhelp32.h>
#include <Psapi.h>
#pragma comment(lib,"psapi.lib")



CString GetImageFullPath(DWORD dwPid)
{
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);
	if (hProcess == NULL)
		return "";
	char path[MAX_PATH] = { 0 };
	GetModuleFileNameEx(hProcess, NULL, path, MAX_PATH);
	CloseHandle(hProcess);
	CString imagePath(path);
	return imagePath;
}


map<DWORD, ProcessInfo> GetProcessList()
{
	map<DWORD, ProcessInfo> processMap;
	HANDLE hwnd;
	PROCESSENTRY32 pro;
	
	pro.dwSize = sizeof(PROCESSENTRY32);
	BOOL flag;
	hwnd = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hwnd != 0) {		
	flag = Process32First(hwnd, &pro);
	while (flag) {
		ProcessInfo myProcessInfo;
		//mp.insert(pair<DWORD, WCHAR>(pro.th32ProcessID, pro.szExeFile));
		CString tempName(pro.szExeFile);
		//strcmp(tempName, pro.szExeFile);
		//StrCpyW(tempName, pro.szExeFile);
		myProcessInfo.FileName = tempName;
		myProcessInfo.PID = pro.th32ProcessID;
		myProcessInfo.ImagePath=GetImageFullPath(pro.th32ProcessID);
		processMap[pro.th32ProcessID] = myProcessInfo;
		flag = Process32Next(hwnd, &pro);
	}
	CloseHandle(hwnd);
	}

	return processMap;
}

map<DWORD, ModuleInfo> GetProcessModule(DWORD dwPid)
{
	map<DWORD, ModuleInfo> moduleMap;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPid);
	if (INVALID_HANDLE_VALUE != hSnapshot)
	{	
	MODULEENTRY32 mi;
	mi.dwSize = sizeof(MODULEENTRY32); //��һ��ʹ�ñ����ʼ����Ա
	BOOL  flag = Module32First(hSnapshot, &mi);
	DWORD mapIndex = 0;
	while (flag)
	{		
		ModuleInfo myModuleInfo;
		myModuleInfo.ModuleName = CString(mi.szExePath);
		CString tempImageBaseAddress, tempImageBaseSize;
		tempImageBaseAddress.Format("0x%x", mi.modBaseAddr);
		myModuleInfo.ImageBaseAddress = tempImageBaseAddress;
		tempImageBaseSize.Format("0x%x", mi.modBaseSize);
		myModuleInfo.ImageBaseSize = tempImageBaseSize;
		moduleMap[mapIndex] = myModuleInfo;
		mapIndex++;
		flag = Module32Next(hSnapshot, &mi);
	}
	CloseHandle(hSnapshot);
	}
	return moduleMap;
}


int SuspendProcess(DWORD dwProcessID, BOOL fSuspend)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(
		TH32CS_SNAPTHREAD, dwProcessID);

	if (hSnapshot != INVALID_HANDLE_VALUE)
	{

		THREADENTRY32 te = { sizeof(te) };
		BOOL fOk = Thread32First(hSnapshot, &te);
		for (; fOk; fOk = Thread32Next(hSnapshot, &te))
		{
			if (te.th32OwnerProcessID == dwProcessID)
			{		
				
					HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME,
						FALSE, te.th32ThreadID);
					if (hThread != NULL){
					if (fSuspend)
					{
						if (IsThreadSuspend(dwProcessID, te.th32ThreadID) == 0) {
							SuspendThread(hThread);
						}
						else {
							return 0;
						}
					}
					else
					{
						if (IsThreadSuspend(dwProcessID, te.th32ThreadID) == 1) {
							ResumeThread(hThread);
						}
						else {
							return 0;
						}
					}
					}
					CloseHandle(hThread);
				}			
			}
		
	}
	CloseHandle(hSnapshot);
	return 1;
}





/*
����* ������ : IsThreadSuspend
����* ��  �� : ��ȡ�߳��Ǳ��Ƿ񱻹���
����* ����ֵ : int 1�� ��ʾ�̱߳����� , 0�� ��ʾ�߳������� -1 δ֪״̬
����* ��  �� : DWORD dwThreadID Ҫ��֤���̵߳�ID
����* ��  �� : wchar_t * szProcessName ��ʾ�߳����ڵĽ�����
*/
int IsThreadSuspend(DWORD dwProcessID, DWORD dwThreadID)
{
	int nRet = 0;
	NTSTATUS Status = 0;


	PQUERYSYSTEM NtQuerySystemInformation = NULL;
	PSYSTEM_PROCESS_INFORMATION pInfo = { 0 };

	// ��ȡ������ַ
	NtQuerySystemInformation = (PQUERYSYSTEM)
		GetProcAddress(LoadLibrary("ntdll.dll"), "NtQuerySystemInformation");


	DWORD   dwSize = 0;
	// ��ȡ��Ϣ����Ļ�������С
	Status = NtQuerySystemInformation(SystemProcessesAndThreadsInformation,//Ҫ��ȡ����Ϣ������
		NULL, // ���ڽ�����Ϣ�Ļ�����
		0,  // ��������С
		&dwSize
		);
	// ���뻺����
	char* pBuff = new char[dwSize];
	pInfo = (PSYSTEM_PROCESS_INFORMATION)pBuff;
	if (pInfo == NULL)
		return -1;
	// �ٴε��ú���, ��ȡ��Ϣ
	Status = NtQuerySystemInformation(SystemProcessesAndThreadsInformation,//Ҫ��ȡ����Ϣ������
		pInfo, // ���ڽ�����Ϣ�Ļ�����
		dwSize,  // ��������С
		&dwSize
		);
	if (!NT_SUCCESS(Status)) {/*�������ִ��ʧ��*/
		printf("ʧ��\n");
		delete[] pInfo;
		return -1;
	}

	// �����ṹ��,�ҵ���Ӧ�Ľ���
	while (1) {
		// �ж��Ƿ�����һ������
		if (pInfo->NextEntryDelta == 0)
			break;

		// �ж��Ƿ��ҵ���ID
		if (pInfo->ProcessId == dwProcessID) {

			// �ҵ��ý����µĶ�Ӧ���߳�,Ҳ���Ǳ��������߳�
			for (DWORD i = 0; i < pInfo->ThreadCount; i++) {
				if (pInfo->Threads[i].ClientId.UniqueThread == dwThreadID) { //�ҵ��߳� 
																			 //����̱߳�����
					if (pInfo->Threads[i].State == StateWait
						&& pInfo->Threads[i].WaitReason == Suspended) {
						nRet = 1;
						break;
					}
				}
			}
			break;
		}
		// ��������һ���ڵ�
		pInfo = (PSYSTEM_PROCESS_INFORMATION)(((PUCHAR)pInfo) + pInfo->NextEntryDelta);
	}

	delete[] pBuff;
	return nRet;
}
#include <stdio.h>
#include <Windows.h>
#include <iostream>
using namespace std;
void Delete_Regedit_LOCAL_MACHINE(const char* Reg_Path, const char* Key_Name)
{
	char szKeyName[MAXBYTE] = { 0 };
	HKEY hKey = NULL;
	LONG lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, Reg_Path, 0, KEY_ALL_ACCESS, &hKey);
	RegDeleteValue(hKey, Key_Name);
	RegCloseKey(hKey);
}

void Delete_Regedit_HKEY_CURRENT_USER(const char* Reg_Path, const char* Key_Name)
{
	char szKeyName[MAXBYTE] = { 0 };
	HKEY hKey = NULL;
	LONG lRet = RegOpenKeyEx(HKEY_CURRENT_USER, Reg_Path, 0, KEY_ALL_ACCESS, &hKey);
	RegDeleteValue(hKey, Key_Name);
	RegCloseKey(hKey);
}


void Delete_Regedit()
{
	HKEY hKEY;
	LPCTSTR data = "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\RunMRU";
	if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, data, 0, KEY_SET_VALUE, &hKEY))
	{
		//ɾ�� Test �Ӽ��¼�ֵ TestRegSz
		cout << ERROR_SUCCESS << RegDeleteValue(hKEY, "RunMRU") << endl;
		if (ERROR_SUCCESS == RegDeleteValue(hKEY, "RunMRU")) {
			printf("ɾ����ֵ TestRegSz �ɹ�.\n");
		}
		RegCloseKey(hKEY);
		if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, data, 0, KEY_SET_VALUE, &hKEY))
		{
			// ɾ���Ӽ� Test
			if (ERROR_SUCCESS == RegDeleteKey(hKEY, "a")) {
				printf("ɾ���Ӽ� Test �ɹ�.\n");
			}
		}
		RegCloseKey(hKEY);
		return;
	}
}
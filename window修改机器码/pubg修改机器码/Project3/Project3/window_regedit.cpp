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
		//删除 Test 子键下键值 TestRegSz
		cout << ERROR_SUCCESS << RegDeleteValue(hKEY, "RunMRU") << endl;
		if (ERROR_SUCCESS == RegDeleteValue(hKEY, "RunMRU")) {
			printf("删除键值 TestRegSz 成功.\n");
		}
		RegCloseKey(hKEY);
		if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, data, 0, KEY_SET_VALUE, &hKEY))
		{
			// 删除子键 Test
			if (ERROR_SUCCESS == RegDeleteKey(hKEY, "a")) {
				printf("删除子键 Test 成功.\n");
			}
		}
		RegCloseKey(hKEY);
		return;
	}
}
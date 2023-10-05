// ------------------------------------- //
// 您如果要使用本文件，请不要删除本说明  //
// ------------------------------------- //
//             HOOKAPI 开发例子          //
//   Copyright 2002 编程沙龙 Paladin     //
//       www.ProgramSalon.com            //
// ------------------------------------- //

#include "stdafx.h"
#include <stdio.h>
#include "mydll.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

void WriteLog(char *fmt,...)
{
	FILE *fp;
	va_list args;
	//char temp[500];

	if((fp =fopen("c:\\hookapi.log", "a")) !=NULL)
	{		
		va_start(args,fmt);

		vfprintf(fp, fmt, args);
		fprintf(fp, "\n");
		fclose(fp);
		
		va_end(args);
	}
}

char *GetRootKey(HKEY hKey)
{
	if(hKey == HKEY_CLASSES_ROOT)
		return "HKEY_CLASSES_ROOT";
	else if(hKey == HKEY_CURRENT_CONFIG)
		return "KEY_CURRENT_CONFIG";
	else if(hKey ==HKEY_CURRENT_USER)
		return "HKEY_CURRENT_USER";
	else if(hKey == HKEY_LOCAL_MACHINE)
		return "HKEY_LOCAL_MACHINE";
	else if(hKey == HKEY_USERS)
		return "HKEY_USERS";
	else if(hKey == HKEY_PERFORMANCE_DATA)
		return "HKEY_PERFORMANCE_DATA";
	else
		return "未知根路径";
}

DWORD WINAPI myRegOpenKeyA(HKEY hKey, LPCSTR lpSubKey, PHKEY phkResult)
{
	char temp[200];
	GetModuleFileName(NULL, temp, sizeof(temp));
	WriteLog("%s, myRegOpenKeyA:hKey=%s,SubKey=%s", temp, GetRootKey(hKey), lpSubKey);

	return (DWORD)RegOpenKeyA(hKey, lpSubKey, phkResult);
}

DWORD WINAPI myRegOpenKeyW(HKEY hKey, LPCWSTR lpSubKey, PHKEY phkResult)
{
	char temp[200];
	GetModuleFileName(NULL, temp, sizeof(temp));
	char subkey[200];
	int len =WideCharToMultiByte( CP_ACP, 0, lpSubKey, -1, subkey, sizeof(subkey),NULL,NULL); 
	subkey[len] =0;
	WriteLog("%s, myRegOpenKeyW:hKey=%s,SubKey=%s", temp, GetRootKey(hKey), subkey);

	return (DWORD)RegOpenKeyW(hKey, lpSubKey, phkResult);
}

DWORD WINAPI myRegQueryValueA(HKEY hKey, LPCSTR lpSubKey, LPSTR lpValue, PLONG lpcbValue)
{
	int err;
	LONG ret =RegQueryValueA(hKey, lpSubKey, lpValue, lpcbValue);
	err =GetLastError();
	char temp[200];
	GetModuleFileName(NULL, temp, sizeof(temp));
	WriteLog("%s, myRegQueryValueA:hKey=%s,SubKey=%s", temp, GetRootKey(hKey), lpSubKey);
	SetLastError(err);

	return (DWORD)ret;
}

DWORD WINAPI myRegQueryValueW(HKEY hKey,LPCWSTR lpSubKey, LPWSTR lpValue, PLONG lpcbValue)
{
	LONG ret =RegQueryValueW(hKey, lpSubKey, lpValue, lpcbValue);
	int err =GetLastError();

	char temp[200];
	GetModuleFileName(NULL, temp, sizeof(temp));
	char subkey[200];
	int len =WideCharToMultiByte( CP_ACP, 0, lpSubKey, -1, subkey, sizeof(subkey),NULL,NULL); 
	subkey[len] =0;
	WriteLog("%s, myRegQueryValueW:hKey=%s,SubKey=%s", temp, GetRootKey(hKey), subkey);
	SetLastError(err);
	
	return (DWORD)ret;
}

DWORD WINAPI myRegQueryValueExA(HKEY hKey, LPSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData)
{
	LONG ret =RegQueryValueExA(hKey, lpValueName, lpReserved, lpType, lpData, lpcbData);
	int err =GetLastError();

	char temp[200];
	GetModuleFileName(NULL, temp, sizeof(temp));
	WriteLog("%s, myRegQueryValueExA:hKey=%s,ValueName=%s", temp, GetRootKey(hKey), lpValueName);
	SetLastError(err);
	
	return (DWORD)ret;
}

DWORD WINAPI myRegQueryValueExW(HKEY hKey, LPWSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData)
{
	LONG ret =RegQueryValueExW(hKey, lpValueName, lpReserved, lpType, lpData, lpcbData);
	int err =GetLastError();

	char temp[200];
	GetModuleFileName(NULL, temp, sizeof(temp));
	char value[200];
	int len =WideCharToMultiByte( CP_ACP, 0, lpValueName, -1, value, sizeof(value),NULL,NULL); 
	value[len] =0;
	WriteLog("%s, myRegQueryValueExW:hKey=%s,ValueName=%s", temp, GetRootKey(hKey), value);
	SetLastError(err);
	
	return (DWORD)ret;
}

MYAPIINFO myapi_info[] =
{
	{"ADVAPI32.DLL", "RegOpenKeyW(HKEY, LPCWSTR, PHKEY)", "myRegOpenKeyW"},
	{"ADVAPI32.DLL", "RegQueryValueW(HKEY, LPCWSTR, LPWSTR, PLONG)", "myRegQueryValueW"},
	{"ADVAPI32.DLL", "RegOpenKeyA(HKEY, LPCSTR, PHKEY)", "myRegOpenKeyA"},
	{"ADVAPI32.DLL", "RegQueryValueA(HKEY, LPCSTR, LPSTR, PLONG)", "myRegQueryValueA"},
	{"ADVAPI32.DLL", "RegQueryValueExW(HKEY,LPWSTR,LPDWORD,LPDWORD,LPBYTE,LPDWORD)", "myRegQueryValueExW"},
	{"ADVAPI32.DLL", "RegQueryValueExA(HKEY,LPSTR,LPDWORD,LPDWORD,LPBYTE,LPDWORD)", "myRegQueryValueExA"},
	{NULL,NULL,NULL}
};

MYAPIINFO *GetMyAPIInfo()
{
	return &myapi_info[0];
}

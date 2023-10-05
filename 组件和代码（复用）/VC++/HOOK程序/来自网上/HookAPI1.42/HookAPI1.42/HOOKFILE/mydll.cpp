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
	//char temp[256];

	if((fp =fopen("c:\\hookapi.log", "a")) !=NULL)
	{		
		va_start(args,fmt);

		vfprintf(fp, fmt, args);
		fprintf(fp, "\n");
		fclose(fp);
		
		va_end(args);
	}
}

HANDLE WINAPI myCreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{          
	char temp[200];
	GetModuleFileName(NULL, temp, sizeof(temp));
	WriteLog("%s, myCreateFileA:filename=%s", temp, lpFileName);
	//MessageBox(NULL, temp, "mydll", MB_OK);
	if(strstr(lpFileName, "aaa") !=NULL) return NULL;
	return CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
		dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

HANDLE WINAPI myCreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
	//MessageBox(NULL, "myCreateFileW", "ok", MB_OK);
                              
	char temp[200];
	GetModuleFileName(NULL, temp, sizeof(temp));
	char fname[128];
	WideCharToMultiByte( CP_ACP, 0, lpFileName, -1, fname, 128,NULL,NULL); 

	WriteLog("%s, myCreateFileW:filename=%s", temp, fname);
	//MessageBox(NULL, temp, "mydll", MB_OK);

	if(strstr(fname, "aaa") !=NULL)
	{
		WriteLog("CreateFileW aaa found!");
		SetLastError(ERROR_FILE_NOT_FOUND);
		return NULL;
	}

	return CreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
		dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

BOOL WINAPI myDeleteFileA(LPCSTR lpFileName)
{
	char temp[200];
	GetModuleFileName(NULL, temp, sizeof(temp));
	WriteLog("%s,\n myDeleteFileA:filename=%s", temp, lpFileName);
	if(strstr(temp, "aaa") !=NULL)
	{
		WriteLog("DeleteFileA aaa found!");
		SetLastError(ERROR_FILE_NOT_FOUND);
		return NULL;
	}

	return DeleteFileA(lpFileName);
}

BOOL WINAPI myDeleteFileW(LPCWSTR lpFileName)
{
	char temp[200];
	GetModuleFileName(NULL, temp, sizeof(temp));
	char fname[128];
	WideCharToMultiByte( CP_ACP, 0, lpFileName, -1, fname, 128,NULL,NULL); 
	WriteLog("%s,\n myDeleteFileW:filename=%s", temp, fname);
	if(strstr(fname, "aaa") !=NULL)
	{
		WriteLog("DeleteFileW aaa found!");
		SetLastError(ERROR_FILE_NOT_FOUND);
		return NULL;
	}

	return DeleteFileW(lpFileName);
}

MYAPIINFO myapi_info[] =
{
	{"KERNEL32.DLL", "CreateFileA(LPCTSTR, DWORD, DWORD,LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE)", "myCreateFileA"},
	{"KERNEL32.DLL", "CreateFileW(LPCWSTR, DWORD, DWORD,LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE)", "myCreateFileW"},
	{"KERNEL32.DLL", "DeleteFileA(LPCSTR)", "myDeleteFileA"},
	{"KERNEL32.DLL", "DeleteFileW(LPCWSTR)", "myDeleteFileW"},
	{NULL,NULL,NULL}
};

MYAPIINFO *GetMyAPIInfo()
{
	return &myapi_info[0];
}

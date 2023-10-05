// PSAPI.h: interface for the PSAPI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PSAPI_H__33A1BD26_C086_445A_98DB_32EF4C7223C0__INCLUDED_)
#define AFX_PSAPI_H__33A1BD26_C086_445A_98DB_32EF4C7223C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//需要定位的API
typedef BOOL (__stdcall *ENUMPROCESSES)(
													 DWORD *lpidProcess,  // array of process identifiers
													 DWORD cb,            // size of array
													 DWORD *cbNeeded      // number of bytes returned
													 );
typedef BOOL (__stdcall *ENUMPROCESSMODULES)(
															HANDLE hProcess,      // handle to process
															HMODULE *lphModule,   // array of module handles
															DWORD cb,             // size of array
															LPDWORD lpcbNeeded    // number of bytes required
															);
typedef DWORD (__stdcall *GETMODULEFILENAMEEX)(
															  HANDLE hProcess,    // handle to process
															  HMODULE hModule,    // handle to module
															  LPTSTR lpFilename,  // path buffer
															  DWORD nSize         // maximum characters to retrieve
															  );

extern ENUMPROCESSES EnumProcesses;
extern ENUMPROCESSMODULES EnumProcessModules;
extern GETMODULEFILENAMEEX GetModuleFileNameEx;

//PSAPI.Dll的句柄
extern HMODULE g_hPSAPI;

//装载Dll并定位相应函数
BOOL InitPSAPI();

//释放Dll
void UnInitPSAPI();


#endif // !defined(AFX_PSAPI_H__33A1BD26_C086_445A_98DB_32EF4C7223C0__INCLUDED_)

// ProcessFunction.h: interface for the ProcessFunction class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROCESSFUNCTION_H__C8EF14B2_9155_4FE1_BE34_E25DC35D70FA__INCLUDED_)
#define AFX_PROCESSFUNCTION_H__C8EF14B2_9155_4FE1_BE34_E25DC35D70FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//进程描述信息
typedef struct _tagPROCESSINFO
{
	DWORD		dwPID;
	TCHAR		strPath[_MAX_PATH];
	TCHAR		strName[_MAX_FNAME];
	
} PROCESSINFO, *LPPROCESSINFO;


//进程描述信息
typedef struct _tagMODULEINFO
{
	TCHAR		strPath[_MAX_PATH];
	TCHAR		strName[_MAX_FNAME];
	
} MODULEINFO, *LPMODULEINFO;

BOOL EnumProcessesInfo( PROCESSINFO* lpPsInfo, ULONG ulSize, ULONG* pulNeeded );
BOOL EnumProcessModulesInfo( DWORD dwPID, MODULEINFO *lpModInfo, DWORD dwSize, DWORD *lpdwNeeded );
BOOL KillProcess( DWORD dwPID );
BOOL UpdateProcessPrivilege( HANDLE hProcess, LPCTSTR lpPrivilegeName );

#endif // !defined(AFX_PROCESSFUNCTION_H__C8EF14B2_9155_4FE1_BE34_E25DC35D70FA__INCLUDED_)

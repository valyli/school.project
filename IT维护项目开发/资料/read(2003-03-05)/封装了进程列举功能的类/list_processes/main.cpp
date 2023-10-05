
#include "stdafx.h"
#include <stdio.h>
#include "PSAPI.h"
#include <tchar.h>

class PrintPS : public CPSAPI
{
	virtual BOOL OnProcess(LPCTSTR lpszFileName, DWORD ProcessID)
	{
		_tprintf(_T("%d : %s\n"), ProcessID, lpszFileName);
		return TRUE;
	}
	virtual BOOL OnModule(HMODULE hModule, LPCTSTR lpszModuleName, LPCTSTR lpszPathName)
	{
		_tprintf(_T("0x%08x %s %s\n"), hModule, lpszModuleName, lpszPathName);
		return TRUE;
	}
};

class AllPS : public CPSAPI
{
	virtual BOOL OnProcess(LPCTSTR lpszFileName, DWORD dwProcessId)
	{
		_tprintf(_T("%d : %s\n"), dwProcessId, lpszFileName);
		PrintPS pa;
		pa.Initialize();
		pa.EnumProcessModules(dwProcessId);
		_tprintf(_T("\n"));
		return TRUE;
	}
};

void _tmain(int ac, TCHAR *av[])
{
	BOOL bListAll = FALSE;
	DWORD dwProcessId = 0 ;
	if ( ac != 1 )
	{
		if ( av[1][0] == '-' || av[1][0] == '/' )
		{
			if ( _tcsicmp(av[1]+1, _T("help")) == 0 || _tcsicmp(av[1]+1, _T("h")) == 0 || _tcsicmp(av[1]+1, _T("?")) == 0 )
			{
				_ftprintf(stderr, _T("ps : show process list or list process modules.\nUsage : ps [<-help> | <-?> | <-all>\n\t-all\tList all process and their modules.\n"));
				exit(0);
			}
			else if ( _tcsicmp(av[1]+1, _T("all")) == 0 )
				bListAll = true;
		}
		else
			dwProcessId = _ttoi(av[1]);
	}

	if ( bListAll )
	{
		AllPS ap;
		ap.Initialize();
		ap.EnumProcesses();
	}
	else if ( dwProcessId != 0 )
	{
		PrintPS pa;
		pa.Initialize();
		pa.EnumProcessModules(dwProcessId);
	}
	else
	{
		PrintPS pa;
		pa.Initialize();
		pa.EnumProcesses();
	}
}

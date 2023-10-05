// CheckSystemType.cpp: implementation of the CCheckSystemType class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CheckSystemType.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCheckSystemType::CCheckSystemType()
{

}

CCheckSystemType::~CCheckSystemType()
{

}


//查操作系统类型
Win32SysType CCheckSystemType::IsShellSystemType(CString &strWin32SysType)
{
	Win32SysType  ShellType;
	DWORD winVer;
	OSVERSIONINFO *osvi;
	
	winVer=::GetVersion();
	if(winVer<0x80000000){	/*NT */
		ShellType=WindowsNT3;
		osvi= (OSVERSIONINFO *)malloc(sizeof(OSVERSIONINFO));
		if (osvi!=NULL){
			memset(osvi,0,sizeof(OSVERSIONINFO));
			osvi->dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
			::GetVersionEx(osvi);
			if(osvi->dwMajorVersion==4L)
				ShellType=WindowsNT4;
			else if(osvi->dwMajorVersion==5L&&osvi->dwMinorVersion==0L)
				ShellType=Windows2000;
			else if(osvi->dwMajorVersion==5L&&osvi->dwMinorVersion==1L)
				ShellType=WindowsXP;
			free(osvi);
		}
	}
	else if  (LOBYTE(LOWORD(winVer))<4)
		ShellType=Windows32s;
	else{
		ShellType=Windows95;
		osvi= (OSVERSIONINFO *)malloc(sizeof(OSVERSIONINFO));
		if (osvi!=NULL){
			memset(osvi,0,sizeof(OSVERSIONINFO));
			osvi->dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
			GetVersionEx(osvi);
			if(osvi->dwMajorVersion==4L&&osvi->dwMinorVersion==10L)
				ShellType=Windows98;
			else if(osvi->dwMajorVersion==4L&&osvi->dwMinorVersion==90L)
				ShellType=WindowsME;
			free(osvi);
		}
	}

	switch(ShellType)
	{
	case Windows32s:
		strWin32SysType = "Windows32s";
		break;
	case WindowsNT3:
		strWin32SysType = "WindowsNT3";
		break;
	case Windows95:
		strWin32SysType = "Windows95";
		break;
	case Windows98:
		strWin32SysType = "Windows98";
		break;
	case WindowsME:
		strWin32SysType = "WindowsME";
		break;
	case WindowsNT4:
		strWin32SysType = "WindowsNT4";
		break;
	case Windows2000:
		strWin32SysType = "Windows2000";
		break;
	case WindowsXP:
		strWin32SysType = "WindowsXP";
		break;
	default:
		strWin32SysType = "Unknown";
	}
	return ShellType;
}

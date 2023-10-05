// DetectVersion.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>

#include "ModuleInfoList.h"
#include "ManageData.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static AFX_EXTENSION_MODULE DetectVersionDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("DETECTVERSION.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(DetectVersionDLL, hInstance))
			return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		new CDynLinkLibrary(DetectVersionDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("DETECTVERSION.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(DetectVersionDLL);
	}
	return 1;   // ok
}





//~~~~~~~~~~~~~Define WindowsSystemVersionType_DetectWindowsVersionModule~~~~~~~~~~~~~
//声明系统类型变量的枚举类型
typedef enum tagWindowsSystemVersionType_DetectWindowsVersionModule
{
	Windows32s,
	WindowsNT3,
	Windows95,
	Windows98,
	WindowsME,
	WindowsNT4,
	Windows2000,
	WindowsXP
}WindowsSystemVersionType_DetectWindowsVersionModule;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~End Define~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~





//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  Module Start  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
/*--------------------------------  Module Infomation  ----------------------------------------
@规范名称：DetectWindowsVersionModule
@模块名称：Windows操作系统版本检测模块
@需引入的文件（.h、.lib、.dll等）:stdafx.h
@作者：李佳
@日期：2003-03-13
----------------------------------------------------------------------------------------------/



/*********************************  Type Define Start  ****************************************

		//~~~~~~~~~~~~~Define WindowsSystemVersionType_DetectWindowsVersionModule~~~~~~~~~~~~~~
		//声明系统类型变量的枚举类型
		typedef enum tagWindowsSystemVersionType_DetectWindowsVersionModule
		{
			Windows32s,
			WindowsNT3,
			Windows95,
			Windows98,
			WindowsME,
			WindowsNT4,
			Windows2000,
			WindowsXP
		}WindowsSystemVersionType_DetectWindowsVersionModule;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~End Define~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

***********************************  Type Define Stop  ***************************************/



//*********************************  Function Define Start  ***********************************

//$$$$ DetectWindowsVersion_DetectWindowsVersionModule()
/*----------------------------------  Fouction Information  -----------------------------------
@函数功能：检测Windows操作系统版本
@数据源：WINAIP
@参数：
		strWin32SysType		CString		引用型，可返回操作系统名称
@返回值含义：返回操作系统类型
@涉及的自定义类型：
		WindowsSystemVersionType_DetectWindowsVersionModule
@需引入的文件（.h、.lib、.dll等）:stdafx.h
@备注
---------------------------------------------------------------------------------------------*/
bool DetectWindowsVersion_DetectWindowsVersionModule(CManageData& Data)
{
	WindowsSystemVersionType_DetectWindowsVersionModule  ShellType;
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

	CString strWindowsSystemName;
	switch(ShellType)
	{
	case Windows32s:
		strWindowsSystemName = "Windows32s";
		break;
	case WindowsNT3:
		strWindowsSystemName = "WindowsNT3";
		break;
	case Windows95:
		strWindowsSystemName = "Windows95";
		break;
	case Windows98:
		strWindowsSystemName = "Windows98";
		break;
	case WindowsME:
		strWindowsSystemName = "WindowsME";
		break;
	case WindowsNT4:
		strWindowsSystemName = "WindowsNT4";
		break;
	case Windows2000:
		strWindowsSystemName = "Windows2000";
		break;
	case WindowsXP:
		strWindowsSystemName = "WindowsXP";
		break;
	default:
		strWindowsSystemName = "Unknown";
	}

	Data.SetData(strWindowsSystemName);
	return true;
}

//*********************************  Function Define Stop  ************************************

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  Module Stop  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


//获得Dll中存储的自身所支持的信息项表
bool InfoList(ModuleInfomationStruct &InfoList)
{
	CModuleInfoList m_InfoList;
	//设置配置文件名
	m_InfoList.strModuleFileName = _T("DetectVersion.xml");
	//获取配置信息
	return m_InfoList.GetInfoList(InfoList);
}
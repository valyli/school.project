// DetectHardware.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>

#include "BiosId.H"

#include "checkHardDiskDevice.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static AFX_EXTENSION_MODULE DetectHardwareDLL = { NULL, NULL };


extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("DETECTHARDWARE.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(DetectHardwareDLL, hInstance))
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

		new CDynLinkLibrary(DetectHardwareDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("DETECTHARDWARE.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(DetectHardwareDLL);
	}
	return 1;   // ok
}








//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  Module Start  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
/*--------------------------------  Module Infomation  ----------------------------------------
@规范名称：DetectHardwareModule
@模块名称：BIOS信息检测模块
@需引入的文件（.h、.lib、.dll等）:stdafx.h
@作者：李佳
@日期：2003-03-13
----------------------------------------------------------------------------------------------/



/*********************************  Type Define Start  ****************************************
***********************************  Type Define Stop  ***************************************/



//*********************************  Function Define Start  ***********************************

//$$$$ DetectBIOS_DetectHardwareModule()
/*----------------------------------  Fouction Information  -----------------------------------
@函数功能：检测BIOS信息
@数据源：汇编直接取自硬件，核心为网上下载
@参数：
		BIOS_ID		CString		引用型，可返回BIOS的序列号
		BIOS_Type	CString		引用型，可返回BIOS的类型
		BIOS_Date	CString		引用型，可返回BIOS的日期
@返回值含义：返回是否成功
@涉及的自定义类型：
@需引入的文件（.h、.lib、.dll等）:stdafx.h、BiosId.Lib、BiosId.H、BiosId.Dll
@备注
---------------------------------------------------------------------------------------------*/
BOOL DetectBIOS_DetectHardwareModule(CString &BIOS_ID, CString &BIOS_Type, CString &BIOS_Date)
{
	char buff[256];
	if(!GetBiosId(buff))
		return FALSE;
	BIOS_ID = buff;
	if(!GetBiosType(buff))
		return FALSE;
	BIOS_Type = buff;
	if(!GetBiosDate(buff))
		return FALSE;
	BIOS_Date = buff;
	return TRUE;
}

//*********************************  Function Define Stop  ************************************

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  Module Stop  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%








//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//此处代码极其简单，所以为方便以后重新拆分，暂不归入以上模块，检测硬盘部分应单独作为一个模块
CheckHardDiskDevice m_CheckHardDiskDevice;

BOOL DetectHardDiskDevice_DetectHardwareModule(int DriveNo, InfoOfHardDiskDevice& HardDiskInfoStruct)
{
	return m_CheckHardDiskDevice.GetInfoOfHardDiskDevice(DriveNo, HardDiskInfoStruct);
}

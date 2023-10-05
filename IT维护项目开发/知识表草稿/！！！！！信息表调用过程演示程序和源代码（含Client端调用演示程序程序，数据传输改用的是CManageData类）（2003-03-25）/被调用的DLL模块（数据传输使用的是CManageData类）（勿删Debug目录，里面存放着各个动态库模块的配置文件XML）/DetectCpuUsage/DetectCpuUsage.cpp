// DetectCpuUsage.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>

#include "ModuleInfoList.h"
#include "ManageData.h"
#include "CheckCpuUsage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static AFX_EXTENSION_MODULE DetectCpuUsageDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("DETECTCPUUSAGE.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(DetectCpuUsageDLL, hInstance))
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

		new CDynLinkLibrary(DetectCpuUsageDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("DETECTCPUUSAGE.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(DetectCpuUsageDLL);
	}
	return 1;   // ok
}





////////////////////////////////////////////////////////////////////////////
CCheckCpuUsage m_CCheckCpuUsage;

//返回CPU利用率，为long型数据
bool DetectCpuUsage_DetectCpuUsageModule(CManageData& Data)
{
	long CpuUsage = 0;
	for(int i = 0; i < 2; i++)
	{
		if(!m_CCheckCpuUsage.CheckCpuUsage(CpuUsage))
			return false;
		Sleep(100);
	}
	Data.SetData(CpuUsage);
	return true;
}


//获得Dll中存储的自身所支持的信息项表
bool InfoList(ModuleInfomationStruct &InfoList)
{
	CModuleInfoList m_InfoList;
	//设置配置文件名
	m_InfoList.strModuleFileName = _T("DetectCpuUsage.xml");
	//获取配置信息
	return m_InfoList.GetInfoList(InfoList);
}
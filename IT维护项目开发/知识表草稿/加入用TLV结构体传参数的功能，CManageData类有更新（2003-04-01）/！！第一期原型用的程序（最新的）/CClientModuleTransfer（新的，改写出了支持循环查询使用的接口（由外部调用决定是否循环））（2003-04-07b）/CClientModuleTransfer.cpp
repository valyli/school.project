// CClientModuleTransfer.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>


#include "TransferModule.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static AFX_EXTENSION_MODULE CClientModuleTransferDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("CCLIENTMODULETRANSFER.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(CClientModuleTransferDLL, hInstance))
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

		new CDynLinkLibrary(CClientModuleTransferDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("CCLIENTMODULETRANSFER.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(CClientModuleTransferDLL);
	}
	return 1;   // ok
}


//声明模块调用类对象
CTransferModule m_TransferModule;


//按给入的ModuleInfomationListStruct中的描述，Client进行一次调用
//Data用于传输参数或返回值的数据
//进行一次完整的调用，包括导入动态库和释放动态库
bool ClientTransferModuleByCManageData(ModuleInfomationListStruct &ModuleInfo, CManageData& Data)
{
	//导入动态库
	if(!m_TransferModule.LoadTransferModuleAndFounctionHandleByCManageData(ModuleInfo))
		return false;
	//调用dll
	if(!m_TransferModule.CallTransferModule(ModuleInfo, Data))
		return false;
	m_TransferModule.FreeTransferModule();
	return true;
}

//功能类似ClientTransferModule，
//按给入的ModuleInfomationListStruct中的描述，Client进行一次调用
//用TLV传回数据
//进行一次完整的调用，包括导入动态库和释放动态库
bool ClientTransferModuleByTLV(ModuleInfomationListStruct &ModuleInfo, TLVStruct& TLVData)
{
	//导入动态库
	if(m_TransferModule.LoadTransferModuleAndFounctionHandleByCManageData(ModuleInfo))
		return false;

	CManageData Data;
	Data.SetDatabyTLV(TLVData);
	//调用dll
	if(!m_TransferModule.CallTransferModule(ModuleInfo, Data))
		return false;
	Data.GetDatabyTLV(TLVData);

	m_TransferModule.FreeTransferModule();
	return true;
}



//在当前目录下搜索所有的合法dll信息
bool ClientGetAllModuleInfoToMemory()
{
	if(!m_TransferModule.GetAllModuleInfoToMemory())
		return false;
	return true;
}


//设置对象m_TransferModule中的hLibrary和lpfn
//以便调用CallTransferModule()函数时使用
void SetModuleHandleAndFunctionAddress(HMODULE hLibrary, bool (FAR *lpfounction)(CManageData &Data))
{
	m_TransferModule.hLibrary = hLibrary;
	m_TransferModule.lpfn = lpfounction;
}

//获取对象m_TransferModule中的hLibrary和lpfn
void GetModuleHandleAndFunctionAddress(HMODULE& hLibrary, bool (FAR*& lpfounction)(CManageData &Data))
{
	hLibrary = m_TransferModule.hLibrary;
	lpfounction = m_TransferModule.lpfn;
}


//导入要循环调用的动态库
bool LoadClientTransferModuleAndFounctionHandleByCManageData(ModuleInfomationListStruct &ModuleInfo)
{
	//导入动态库
	if(!m_TransferModule.LoadTransferModuleAndFounctionHandleByCManageData(ModuleInfo))
		return false;
	return true;
}

//由对象m_TransferModule中的hLibrary和lpfn确定并调用动态库中的函数
//用于外部进行循环获取信息时调用
//其调用前要人为的导入动态库
//循环调用结束后要人为的释放动态库
//每次调用此函数前只要确认设置的hLibrary和lpfn句柄是否正确即可，用SetModuleHandleAndFunctionAddress()函数实现
bool CallClientTransferModuleByCManageData(ModuleInfomationListStruct &ModuleInfo, CManageData& Data)
{
	//调用dll
	if(!m_TransferModule.CallTransferModule(ModuleInfo, Data))
		return false;
	return true;
}


//释放指定的动态库
void FreeClientTransferModule(HMODULE hLibrary)
{
	m_TransferModule.hLibrary = hLibrary;
	m_TransferModule.FreeTransferModule();
}
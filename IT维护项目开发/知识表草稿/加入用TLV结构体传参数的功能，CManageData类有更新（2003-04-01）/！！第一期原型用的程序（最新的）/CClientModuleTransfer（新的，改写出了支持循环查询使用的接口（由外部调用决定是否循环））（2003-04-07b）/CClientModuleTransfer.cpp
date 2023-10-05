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


//����ģ����������
CTransferModule m_TransferModule;


//�������ModuleInfomationListStruct�е�������Client����һ�ε���
//Data���ڴ�������򷵻�ֵ������
//����һ�������ĵ��ã��������붯̬����ͷŶ�̬��
bool ClientTransferModuleByCManageData(ModuleInfomationListStruct &ModuleInfo, CManageData& Data)
{
	//���붯̬��
	if(!m_TransferModule.LoadTransferModuleAndFounctionHandleByCManageData(ModuleInfo))
		return false;
	//����dll
	if(!m_TransferModule.CallTransferModule(ModuleInfo, Data))
		return false;
	m_TransferModule.FreeTransferModule();
	return true;
}

//��������ClientTransferModule��
//�������ModuleInfomationListStruct�е�������Client����һ�ε���
//��TLV��������
//����һ�������ĵ��ã��������붯̬����ͷŶ�̬��
bool ClientTransferModuleByTLV(ModuleInfomationListStruct &ModuleInfo, TLVStruct& TLVData)
{
	//���붯̬��
	if(m_TransferModule.LoadTransferModuleAndFounctionHandleByCManageData(ModuleInfo))
		return false;

	CManageData Data;
	Data.SetDatabyTLV(TLVData);
	//����dll
	if(!m_TransferModule.CallTransferModule(ModuleInfo, Data))
		return false;
	Data.GetDatabyTLV(TLVData);

	m_TransferModule.FreeTransferModule();
	return true;
}



//�ڵ�ǰĿ¼���������еĺϷ�dll��Ϣ
bool ClientGetAllModuleInfoToMemory()
{
	if(!m_TransferModule.GetAllModuleInfoToMemory())
		return false;
	return true;
}


//���ö���m_TransferModule�е�hLibrary��lpfn
//�Ա����CallTransferModule()����ʱʹ��
void SetModuleHandleAndFunctionAddress(HMODULE hLibrary, bool (FAR *lpfounction)(CManageData &Data))
{
	m_TransferModule.hLibrary = hLibrary;
	m_TransferModule.lpfn = lpfounction;
}

//��ȡ����m_TransferModule�е�hLibrary��lpfn
void GetModuleHandleAndFunctionAddress(HMODULE& hLibrary, bool (FAR*& lpfounction)(CManageData &Data))
{
	hLibrary = m_TransferModule.hLibrary;
	lpfounction = m_TransferModule.lpfn;
}


//����Ҫѭ�����õĶ�̬��
bool LoadClientTransferModuleAndFounctionHandleByCManageData(ModuleInfomationListStruct &ModuleInfo)
{
	//���붯̬��
	if(!m_TransferModule.LoadTransferModuleAndFounctionHandleByCManageData(ModuleInfo))
		return false;
	return true;
}

//�ɶ���m_TransferModule�е�hLibrary��lpfnȷ�������ö�̬���еĺ���
//�����ⲿ����ѭ����ȡ��Ϣʱ����
//�����ǰҪ��Ϊ�ĵ��붯̬��
//ѭ�����ý�����Ҫ��Ϊ���ͷŶ�̬��
//ÿ�ε��ô˺���ǰֻҪȷ�����õ�hLibrary��lpfn����Ƿ���ȷ���ɣ���SetModuleHandleAndFunctionAddress()����ʵ��
bool CallClientTransferModuleByCManageData(ModuleInfomationListStruct &ModuleInfo, CManageData& Data)
{
	//����dll
	if(!m_TransferModule.CallTransferModule(ModuleInfo, Data))
		return false;
	return true;
}


//�ͷ�ָ���Ķ�̬��
void FreeClientTransferModule(HMODULE hLibrary)
{
	m_TransferModule.hLibrary = hLibrary;
	m_TransferModule.FreeTransferModule();
}
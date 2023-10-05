// DetectBios.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>

#include "ModuleInfoList.h"

#include "BiosId.H"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static AFX_EXTENSION_MODULE DetectBiosDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("DETECTBIOS.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(DetectBiosDLL, hInstance))
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

		new CDynLinkLibrary(DetectBiosDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("DETECTBIOS.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(DetectBiosDLL);
	}
	return 1;   // ok
}



//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  Module Start  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
/*--------------------------------  Module Infomation  ----------------------------------------
@�淶���ƣ�DetectHardwareModule
@ģ�����ƣ�BIOS��Ϣ���ģ��
@��������ļ���.h��.lib��.dll�ȣ�:stdafx.h
@���ߣ����
@���ڣ�2003-03-13
----------------------------------------------------------------------------------------------/



/*********************************  Type Define Start  ****************************************
***********************************  Type Define Stop  ***************************************/



//*********************************  Function Define Start  ***********************************

//$$$$ DetectBIOS_DetectHardwareModule()
/*----------------------------------  Fouction Information  -----------------------------------
@�������ܣ����BIOS��Ϣ
@����Դ�����ֱ��ȡ��Ӳ��������Ϊ��������
@������
		BIOS_ID		CString		�����ͣ��ɷ���BIOS�����к�
		BIOS_Type	CString		�����ͣ��ɷ���BIOS������
		BIOS_Date	CString		�����ͣ��ɷ���BIOS������
@����ֵ���壺�����Ƿ�ɹ�
@�漰���Զ������ͣ�
@��������ļ���.h��.lib��.dll�ȣ�:stdafx.h��BiosId.Lib��BiosId.H��BiosId.Dll
@��ע
---------------------------------------------------------------------------------------------*/
bool DetectBIOSID_DetectHardwareModule(CString &BIOS_ID)
{
	char buff[256];
	if(!GetBiosId(buff))
		return false;
	BIOS_ID = buff;
	return true;
}


bool DetectBIOSType_DetectHardwareModule(CString &BIOS_Type)
{
	char buff[256];
	if(!GetBiosType(buff))
		return false;
	BIOS_Type = buff;
	return true;
}


bool DetectBIOSDate_DetectHardwareModule(CString &BIOS_Date)
{
	char buff[256];
	if(!GetBiosDate(buff))
		return false;
	BIOS_Date = buff;
	return true;
}

//*********************************  Function Define Stop  ************************************

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  Module Stop  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%




//���Dll�д洢��������֧�ֵ���Ϣ���
bool InfoList(ModuleInfomationStruct &InfoList)
{
	CModuleInfoList m_InfoList;
	//���������ļ���
	m_InfoList.strModuleFileName = _T("DetectBios.xml");
	//��ȡ������Ϣ
	return m_InfoList.GetInfoList(InfoList);
}
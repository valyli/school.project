// TransferModule.cpp: implementation of the CTransferModule class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "testgetinfofromdll.h"
#include "TransferModule.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTransferModule::CTransferModule()
{

}

CTransferModule::~CTransferModule()
{

}

//���ö�̬����ֻ࣬������ʾ
bool CTransferModule::TransferModule(ModuleInfomationListStruct &ModuleInfo)
{
	::MessageBox(0, ModuleInfo.ServiceFileName, "ServiceFileName is Found", MB_OK);

	CString temp;
	bool flag;

	//���붯̬��
	HMODULE hLibrary=LoadLibrary(ModuleInfo.ServiceFileName);
	//������ʧ��
	if(hLibrary == NULL)
	{
		temp = "Load ";
		temp += ModuleInfo.ServiceFileName;
		temp += "Failed";
		return AlarmErrorMessage(temp, "Load Library Error");
	}

	switch(ModuleInfo.ParameterType)
	{
	case CString_Value:
		//����ָ�붨��
		//��lpfn���庯��ָ�룬���׺��ʾ�˺���ָ��Ĳ�����Ӧ������
		//����Ҫ�󣬺���ָ��ķ���ֵ����bool��
		bool (FAR *lpfn_CString_Value)(CString &str);

		//�Ӷ�̬���л�ȡҪ���õķ���
		lpfn_CString_Value = (bool (__cdecl *)(CString&))GetProcAddress(hLibrary, ModuleInfo.InterfaceFunction);
		//��ȡʧ��
		if(lpfn_CString_Value == NULL)
		{
			FreeLibrary(hLibrary);
			return AlarmErrorMessage("Get Function 'InfoList()' Failed", "Load Library Error");
		}
		else
		{
			//����Ҫʹ�õı���
			CString Info_CString = _T(">>Test Infomation<<");//������ʱ���Ϊ������Ϣ�������IsStorageReturnValueInParameterΪ0ʱ��Ч
			//���ö�̬����ָ���ķ���
			flag = (*lpfn_CString_Value)(Info_CString);

			//�ͷŶ�̬��
			FreeLibrary(hLibrary);

			//Ϊ��ʾ������ʾ
			if(flag == true)
			{
				//�жϲ����Ƿ��¼����ֵ
				if(ModuleInfo.IsStorageReturnValueInParameter == 1)
				{
					//��ʾ���ý��������ֵ��
					::MessageBox(0, Info_CString, "���ý��", MB_OK);
				}
				else
				{
					//�޷���ֵʱ
					::MessageBox(0, "���ö�̬��ɹ�", "���ý��", MB_OK);
				}
			}
			return true;
		}

	default:
		return AlarmErrorMessage("�ڵ��ù����в�������ƥ��ʧ��", "");
	}
}

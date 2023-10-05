

///////////////////////////////////////////////////////////////////////////////
//�ļ����ݣ�ʵ�ֶ�ע�������Ķ�̬��ģ�飬���ж�RegisteredOwner��
//			RegisteredOrganization��ֵ��Get��Set����
//���ߣ�	���
//��д���ڣ�2003-03-20
//��Ҫ�ļ���ModuleInfoList.h
//�漰���ã�
///////////////////////////////////////////////////////////////////////////////


// RegisterTable.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>


///////////////////////////////////////////////////////////////////////////////
#include "ModuleInfoList.h"
///////////////////////////////////////////////////////////////////////////////



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static AFX_EXTENSION_MODULE RegisterTableDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("REGISTERTABLE.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(RegisterTableDLL, hInstance))
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

		new CDynLinkLibrary(RegisterTableDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("REGISTERTABLE.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(RegisterTableDLL);
	}
	return 1;   // ok
}


//��ע����ȡע���û�������Ϣ
bool Get_RegisteredOwner(CString& str_owner)
{
	HKEY hKEY;//�����йص� hKEY, �ڲ�ѯ����ʱҪ�رա�
	LPCTSTR data_Set;

	//ȷ��windows�汾��������ֵ����·��
	DWORD winVer;
	winVer=::GetVersion();
	if(winVer<0x80000000)/*NT */
	{
		data_Set="Software\\Microsoft\\Windows NT\\CurrentVersion\\";
	}
	else
	{
		data_Set="Software\\Microsoft\\Windows\\CurrentVersion\\";
	}

	//����·�� data_Set ��ص� hKEY����һ������Ϊ�������ƣ��ڶ��������� 
	//��ʾҪ���ʵļ���λ�ã���������������Ϊ0��KEY_READ��ʾ�Բ�ѯ�ķ�ʽ.
	//����ע���hKEY�򱣴�˺������򿪵ļ��ľ���� 
	long ret0=(::RegOpenKeyEx(HKEY_LOCAL_MACHINE,data_Set, 0, KEY_READ, &hKEY)); 
	if(ret0!=ERROR_SUCCESS) //����޷���hKEY������ֹ�����ִ��
	{
		::RegCloseKey(hKEY);
		return AlarmErrorMessage("����: �޷����йص�hKEY!", ""); 
	} 
	//��ѯ�йص����� (�û����� owner_Get)�� 
	LPBYTE owner_Get=new BYTE[80];
	DWORD type_1=REG_SZ ; DWORD cbData_1=80;
	//hKEYΪ�ղ�RegOpenKeyEx()�������򿪵ļ��ľ����"RegisteredOwner"�� 
	//��ʾҪ�� ѯ�ļ�ֵ����type_1��ʾ��ѯ���ݵ����ͣ�owner_Get�������� 
	//��ѯ�����ݣ�cbData_1��ʾԤ���õ����ݳ��ȡ� 
	long ret1=::RegQueryValueEx(hKEY, "RegisteredOwner", NULL, &type_1, owner_Get, &cbData_1); 
	if(ret1!=ERROR_SUCCESS) 
	{ 
		::RegCloseKey(hKEY);
		return AlarmErrorMessage("����: �޷���ѯ�й�ע�����Ϣ!", ""); 
	} 
	// �� owner_Get �� company_Get ת��Ϊ CString �ַ���, �Ա���ʾ���.
	str_owner=CString(owner_Get);

	delete[] owner_Get;
	// �������ǰҪ�ر��Ѿ��򿪵� hKEY�� 
	::RegCloseKey(hKEY);
	return true;
}

//��ע����ȡע����֯��Ϣ
bool Get_RegisteredOrganization(CString& str_company)
{
	HKEY hKEY;//�����йص� hKEY, �ڲ�ѯ����ʱҪ�رա�
	LPCTSTR data_Set;

	DWORD winVer;
	winVer=::GetVersion();
	if(winVer<0x80000000)/*NT */
	{
		data_Set="Software\\Microsoft\\Windows NT\\CurrentVersion\\";
	}
	else
	{
		data_Set="Software\\Microsoft\\Windows\\CurrentVersion\\";
	}

	//����·�� data_Set ��ص� hKEY����һ������Ϊ�������ƣ��ڶ��������� 
	//��ʾҪ���ʵļ���λ�ã���������������Ϊ0��KEY_READ��ʾ�Բ�ѯ�ķ�ʽ.
	//����ע���hKEY�򱣴�˺������򿪵ļ��ľ���� 
	long ret0=(::RegOpenKeyEx(HKEY_LOCAL_MACHINE,data_Set, 0, KEY_READ, &hKEY)); 
	if(ret0!=ERROR_SUCCESS) //����޷���hKEY������ֹ�����ִ��
	{
		::RegCloseKey(hKEY);
		return AlarmErrorMessage("����: �޷����йص�hKEY!", ""); 
	} 
	//hKEYΪ�ղ�RegOpenKeyEx()�������򿪵ļ��ľ����"RegisteredOwner"�� 
	//��ʾҪ�� ѯ�ļ�ֵ����type_1��ʾ��ѯ���ݵ����ͣ�owner_Get�������� 
	//��ѯ�����ݣ�cbData_1��ʾԤ���õ����ݳ��ȡ� 
	// ��ѯ�йص����� (��˾�� company_Get)
	LPBYTE company_Get=new BYTE [80];
	DWORD type_2=REG_SZ; DWORD cbData_2=80;
	long ret2=::RegQueryValueEx(hKEY, "RegisteredOrganization", NULL,&type_2,company_Get, &cbData_2);
	if(ret2!=ERROR_SUCCESS)
	{
		::RegCloseKey(hKEY);
		return AlarmErrorMessage("����: �޷���ѯ�й�ע�����Ϣ!", ""); 
	}
	// ��company_Get ת��Ϊ CString �ַ���, �Ա���ʾ���.
	str_company=CString(company_Get);

	delete[] company_Get;
	// �������ǰҪ�ر��Ѿ��򿪵� hKEY�� 
	::RegCloseKey(hKEY);
	return true;
}


//��ȡ��CString���͵��й��ַ�����Ҫ�Ƚ���ת��ΪLPBYTE(��unsigned char��)�͵���������
LPBYTE CString_To_LPBYTE(CString str) 
{ 
	LPBYTE lpb = new BYTE[str.GetLength()+1];  
	for(int i=0; (i<str.GetLength())&&(*(lpb+i) = str.GetAt(i));i++);
	return lpb;
} 


//����RegisteredOwner
bool Set_RegisteredOwner(CString& str_owner)
{
	//�����йص� hKEY, �ڳ�������Ҫ�رա�
	HKEY hKEY;
	LPCTSTR data_Set;

	DWORD winVer;
	winVer=::GetVersion();
	if(winVer<0x80000000)/*NT */
	{
		data_Set="Software\\Microsoft\\Windows NT\\CurrentVersion\\";
	}
	else
	{
		data_Set="Software\\Microsoft\\Windows\\CurrentVersion\\";
	}

	//����·�� data_Set ��ص�hKEY��KEY_WRITE��ʾ��д�ķ�ʽ�򿪡�
	long ret0=(::RegOpenKeyEx(HKEY_LOCAL_MACHINE, data_Set, 0, KEY_WRITE, &hKEY));
	if(ret0!=ERROR_SUCCESS)
	{
		return AlarmErrorMessage("����: �޷����йص�hKEY!", "");
	}
	//�޸��й�����(�û����� owner_Set)��Ҫ�Ƚ�CString��ת��ΪLPBYTE
	LPBYTE owner_Set=CString_To_LPBYTE(str_owner);
//	for(int i=0; (i<str_owner.GetLength())&&(*(owner_Set+i) = str_owner.GetAt(i));i++);

	DWORD type_1=REG_SZ;
	DWORD cbData_1=str_owner.GetLength()+1;
	//��RegQureyValueEx()���ƣ�hKEY��ʾ�Ѵ򿪵ļ��ľ����"RegisteredOwner"
	//��ʾҪ���ʵļ�ֵ����owner_Set��ʾ�µļ�ֵ��type_1��cbData_1��ʾ��ֵ.
	//���������ͺ����ݳ���
	long ret1=::RegSetValueEx(hKEY, "RegisteredOwner", NULL, type_1, owner_Set, cbData_1);
	if(ret1!=ERROR_SUCCESS)
	{
		::RegCloseKey(hKEY);
		return AlarmErrorMessage("����: �޷��޸��й�ע�����Ϣ!", "");
	}
	::RegCloseKey(hKEY);
	return true;
}


//����RegisteredOrganization
bool Set_RegisteredOrganization(CString& str_company)
{
	//�����йص� hKEY, �ڳ�������Ҫ�رա�
	HKEY hKEY;
	LPCTSTR data_Set;

	DWORD winVer;
	winVer=::GetVersion();
	if(winVer<0x80000000)/*NT */
	{
		data_Set="Software\\Microsoft\\Windows NT\\CurrentVersion\\";
	}
	else
	{
		data_Set="Software\\Microsoft\\Windows\\CurrentVersion\\";
	}

	//����·�� data_Set ��ص�hKEY��KEY_WRITE��ʾ��д�ķ�ʽ�򿪡�
	long ret0=(::RegOpenKeyEx(HKEY_LOCAL_MACHINE, data_Set, 0, KEY_WRITE, &hKEY));
	if(ret0!=ERROR_SUCCESS)
	{
		return AlarmErrorMessage("����: �޷����йص�hKEY!", "");
	}
	//�޸��йص����� (��˾�� company_Set)
	LPBYTE company_Set=CString_To_LPBYTE(str_company);
	DWORD type_2=REG_SZ;
	DWORD cbData_2=str_company.GetLength()+1;
	long ret2=::RegSetValueEx(hKEY, "RegisteredOrganization", NULL,	type_2, company_Set, cbData_2);
	if(ret2!=ERROR_SUCCESS)
	{
		::RegCloseKey(hKEY);
		return AlarmErrorMessage("����: �޷��޸��й�ע�����Ϣ!", "");
	}
	::RegCloseKey(hKEY);
	return true;
}


//���Dll�д洢��������֧�ֵ���Ϣ���
bool InfoList(ModuleInfomationStruct &InfoList)
{
	CModuleInfoList m_InfoList;
	//���������ļ���
	m_InfoList.strModuleFileName = _T("RegisterTable.xml");
	//��ȡ������Ϣ
	return m_InfoList.GetInfoList(InfoList);
}
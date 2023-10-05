

///////////////////////////////////////////////////////////////////////////////
//文件内容：实现对注册表操作的动态库模块，含有对RegisteredOwner和
//			RegisteredOrganization键值的Get和Set方法
//作者：	李佳
//编写日期：2003-03-20
//需要文件：ModuleInfoList.h
//涉及调用：
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


//从注册表获取注册用户姓名信息
bool Get_RegisteredOwner(CString& str_owner)
{
	HKEY hKEY;//定义有关的 hKEY, 在查询结束时要关闭。
	LPCTSTR data_Set;

	//确定windows版本，决定键值所在路径
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

	//打开与路径 data_Set 相关的 hKEY，第一个参数为根键名称，第二个参数表。 
	//表示要访问的键的位置，第三个参数必须为0，KEY_READ表示以查询的方式.
	//访问注册表，hKEY则保存此函数所打开的键的句柄。 
	long ret0=(::RegOpenKeyEx(HKEY_LOCAL_MACHINE,data_Set, 0, KEY_READ, &hKEY)); 
	if(ret0!=ERROR_SUCCESS) //如果无法打开hKEY，则终止程序的执行
	{
		::RegCloseKey(hKEY);
		return AlarmErrorMessage("错误: 无法打开有关的hKEY!", ""); 
	} 
	//查询有关的数据 (用户姓名 owner_Get)。 
	LPBYTE owner_Get=new BYTE[80];
	DWORD type_1=REG_SZ ; DWORD cbData_1=80;
	//hKEY为刚才RegOpenKeyEx()函数所打开的键的句柄，"RegisteredOwner"。 
	//表示要查 询的键值名，type_1表示查询数据的类型，owner_Get保存所。 
	//查询的数据，cbData_1表示预设置的数据长度。 
	long ret1=::RegQueryValueEx(hKEY, "RegisteredOwner", NULL, &type_1, owner_Get, &cbData_1); 
	if(ret1!=ERROR_SUCCESS) 
	{ 
		::RegCloseKey(hKEY);
		return AlarmErrorMessage("错误: 无法查询有关注册表信息!", ""); 
	} 
	// 将 owner_Get 和 company_Get 转换为 CString 字符串, 以便显示输出.
	str_owner=CString(owner_Get);

	delete[] owner_Get;
	// 程序结束前要关闭已经打开的 hKEY。 
	::RegCloseKey(hKEY);
	return true;
}

//从注册表获取注册组织信息
bool Get_RegisteredOrganization(CString& str_company)
{
	HKEY hKEY;//定义有关的 hKEY, 在查询结束时要关闭。
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

	//打开与路径 data_Set 相关的 hKEY，第一个参数为根键名称，第二个参数表。 
	//表示要访问的键的位置，第三个参数必须为0，KEY_READ表示以查询的方式.
	//访问注册表，hKEY则保存此函数所打开的键的句柄。 
	long ret0=(::RegOpenKeyEx(HKEY_LOCAL_MACHINE,data_Set, 0, KEY_READ, &hKEY)); 
	if(ret0!=ERROR_SUCCESS) //如果无法打开hKEY，则终止程序的执行
	{
		::RegCloseKey(hKEY);
		return AlarmErrorMessage("错误: 无法打开有关的hKEY!", ""); 
	} 
	//hKEY为刚才RegOpenKeyEx()函数所打开的键的句柄，"RegisteredOwner"。 
	//表示要查 询的键值名，type_1表示查询数据的类型，owner_Get保存所。 
	//查询的数据，cbData_1表示预设置的数据长度。 
	// 查询有关的数据 (公司名 company_Get)
	LPBYTE company_Get=new BYTE [80];
	DWORD type_2=REG_SZ; DWORD cbData_2=80;
	long ret2=::RegQueryValueEx(hKEY, "RegisteredOrganization", NULL,&type_2,company_Get, &cbData_2);
	if(ret2!=ERROR_SUCCESS)
	{
		::RegCloseKey(hKEY);
		return AlarmErrorMessage("错误: 无法查询有关注册表信息!", ""); 
	}
	// 将company_Get 转换为 CString 字符串, 以便显示输出.
	str_company=CString(company_Get);

	delete[] company_Get;
	// 程序结束前要关闭已经打开的 hKEY。 
	::RegCloseKey(hKEY);
	return true;
}


//将取得CString类型的有关字符串。要先将其转换为LPBYTE(即unsigned char＊)型的数据类型
LPBYTE CString_To_LPBYTE(CString str) 
{ 
	LPBYTE lpb = new BYTE[str.GetLength()+1];  
	for(int i=0; (i<str.GetLength())&&(*(lpb+i) = str.GetAt(i));i++);
	return lpb;
} 


//设置RegisteredOwner
bool Set_RegisteredOwner(CString& str_owner)
{
	//定义有关的 hKEY, 在程序的最后要关闭。
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

	//打开与路径 data_Set 相关的hKEY，KEY_WRITE表示以写的方式打开。
	long ret0=(::RegOpenKeyEx(HKEY_LOCAL_MACHINE, data_Set, 0, KEY_WRITE, &hKEY));
	if(ret0!=ERROR_SUCCESS)
	{
		return AlarmErrorMessage("错误: 无法打开有关的hKEY!", "");
	}
	//修改有关数据(用户姓名 owner_Set)，要先将CString型转换为LPBYTE
	LPBYTE owner_Set=CString_To_LPBYTE(str_owner);
//	for(int i=0; (i<str_owner.GetLength())&&(*(owner_Set+i) = str_owner.GetAt(i));i++);

	DWORD type_1=REG_SZ;
	DWORD cbData_1=str_owner.GetLength()+1;
	//与RegQureyValueEx()类似，hKEY表示已打开的键的句柄，"RegisteredOwner"
	//表示要访问的键值名，owner_Set表示新的键值，type_1和cbData_1表示新值.
	//的数据类型和数据长度
	long ret1=::RegSetValueEx(hKEY, "RegisteredOwner", NULL, type_1, owner_Set, cbData_1);
	if(ret1!=ERROR_SUCCESS)
	{
		::RegCloseKey(hKEY);
		return AlarmErrorMessage("错误: 无法修改有关注册表信息!", "");
	}
	::RegCloseKey(hKEY);
	return true;
}


//设置RegisteredOrganization
bool Set_RegisteredOrganization(CString& str_company)
{
	//定义有关的 hKEY, 在程序的最后要关闭。
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

	//打开与路径 data_Set 相关的hKEY，KEY_WRITE表示以写的方式打开。
	long ret0=(::RegOpenKeyEx(HKEY_LOCAL_MACHINE, data_Set, 0, KEY_WRITE, &hKEY));
	if(ret0!=ERROR_SUCCESS)
	{
		return AlarmErrorMessage("错误: 无法打开有关的hKEY!", "");
	}
	//修改有关的数据 (公司名 company_Set)
	LPBYTE company_Set=CString_To_LPBYTE(str_company);
	DWORD type_2=REG_SZ;
	DWORD cbData_2=str_company.GetLength()+1;
	long ret2=::RegSetValueEx(hKEY, "RegisteredOrganization", NULL,	type_2, company_Set, cbData_2);
	if(ret2!=ERROR_SUCCESS)
	{
		::RegCloseKey(hKEY);
		return AlarmErrorMessage("错误: 无法修改有关注册表信息!", "");
	}
	::RegCloseKey(hKEY);
	return true;
}


//获得Dll中存储的自身所支持的信息项表
bool InfoList(ModuleInfomationStruct &InfoList)
{
	CModuleInfoList m_InfoList;
	//设置配置文件名
	m_InfoList.strModuleFileName = _T("RegisterTable.xml");
	//获取配置信息
	return m_InfoList.GetInfoList(InfoList);
}
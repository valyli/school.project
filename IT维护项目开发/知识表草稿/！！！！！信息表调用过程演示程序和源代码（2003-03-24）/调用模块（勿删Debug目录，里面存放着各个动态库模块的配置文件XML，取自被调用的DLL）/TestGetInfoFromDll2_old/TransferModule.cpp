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

//调用动态库的类，只用于演示
bool CTransferModule::TransferModule(ModuleInfomationListStruct &ModuleInfo)
{
	::MessageBox(0, ModuleInfo.ServiceFileName, "ServiceFileName is Found", MB_OK);

	CString temp;
	bool flag;

	//导入动态库
	HMODULE hLibrary=LoadLibrary(ModuleInfo.ServiceFileName);
	//若导入失败
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
		//函数指针定义
		//用lpfn定义函数指针，其后缀表示此函数指针的参数对应的类型
		//根据要求，函数指针的返回值都是bool型
		bool (FAR *lpfn_CString_Value)(CString &str);

		//从动态库中获取要调用的方法
		lpfn_CString_Value = (bool (__cdecl *)(CString&))GetProcAddress(hLibrary, ModuleInfo.InterfaceFunction);
		//获取失败
		if(lpfn_CString_Value == NULL)
		{
			FreeLibrary(hLibrary);
			return AlarmErrorMessage("Get Function 'InfoList()' Failed", "Load Library Error");
		}
		else
		{
			//定义要使用的变量
			CString Info_CString = _T(">>Test Infomation<<");//用于临时标记为测试信息输出，当IsStorageReturnValueInParameter为0时有效
			//调用动态库中指定的方法
			flag = (*lpfn_CString_Value)(Info_CString);

			//释放动态库
			FreeLibrary(hLibrary);

			//为演示进行显示
			if(flag == true)
			{
				//判断参数是否记录返回值
				if(ModuleInfo.IsStorageReturnValueInParameter == 1)
				{
					//显示调用结果（返回值）
					::MessageBox(0, Info_CString, "调用结果", MB_OK);
				}
				else
				{
					//无返回值时
					::MessageBox(0, "调用动态库成功", "调用结果", MB_OK);
				}
			}
			return true;
		}

	default:
		return AlarmErrorMessage("在调用过程中参数类型匹配失败", "");
	}
}

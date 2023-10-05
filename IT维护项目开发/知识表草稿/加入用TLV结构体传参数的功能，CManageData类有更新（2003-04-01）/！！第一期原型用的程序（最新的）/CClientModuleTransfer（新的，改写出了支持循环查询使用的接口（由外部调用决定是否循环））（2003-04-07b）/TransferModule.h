// TransferModule.h: interface for the CTransferModule class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSFERMODULE_H__A082AC14_89A5_4B7A_91FF_65E8F09709DF__INCLUDED_)
#define AFX_TRANSFERMODULE_H__A082AC14_89A5_4B7A_91FF_65E8F09709DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



////////////////////////////////////////////////////////////////////////////

#include "Base.h"

#include <stdio.h>
#include <io.h>
#include <time.h>

#include "ManageData.h"

////////////////////////////////////////////////////////////////////////////



//调用动态库的类，目前值用于演示
class CTransferModule  
{
public:
	bool GetAllModuleInfoToMemory();
	bool LoadTransferModuleAndFounctionHandleByCManageData(ModuleInfomationListStruct& ModuleInfo);
	bool CallTransferModule(ModuleInfomationListStruct &ModuleInfo, CManageData& Data);
	void FreeTransferModule();

	bool GetInfoListFromDll(ModuleInfomationStruct &m_Info,	CString strDllFilePath);
	CTransferModule();
	virtual ~CTransferModule();


	//保存要调用的动态库的句柄
	HMODULE hLibrary;
	//函数指针定义
	//用lpfn定义函数指针
	//根据要求，函数指针的返回值都是bool型
	bool (FAR *lpfn)(CManageData &Data);

protected:
	//存储从客户端获取的操作表
	CArrayModuleInfomationListStruct m_InfoArray;
//	//记录当前操作的参数或返回值数据
//	CManageData m_Data;
};

#endif // !defined(AFX_TRANSFERMODULE_H__A082AC14_89A5_4B7A_91FF_65E8F09709DF__INCLUDED_)

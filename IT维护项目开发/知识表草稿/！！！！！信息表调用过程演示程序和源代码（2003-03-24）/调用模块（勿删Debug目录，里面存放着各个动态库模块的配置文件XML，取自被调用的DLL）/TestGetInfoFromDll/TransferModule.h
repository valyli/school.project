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


////////////////////////////////////////////////////////////////////////////



//调用动态库的类，目前值用于演示
class CTransferModule  
{
public:
	bool TransferModule(ModuleInfomationListStruct& ModuleInfo);
	CTransferModule();
	virtual ~CTransferModule();

};

#endif // !defined(AFX_TRANSFERMODULE_H__A082AC14_89A5_4B7A_91FF_65E8F09709DF__INCLUDED_)

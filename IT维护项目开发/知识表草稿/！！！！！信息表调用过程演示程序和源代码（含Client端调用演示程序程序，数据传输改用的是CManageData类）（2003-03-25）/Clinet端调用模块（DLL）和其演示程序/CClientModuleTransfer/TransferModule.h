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



//���ö�̬����࣬Ŀǰֵ������ʾ
class CTransferModule  
{
public:
	bool GetInfoListFromDll(ModuleInfomationStruct &m_Info,	CString strDllFilePath);
	bool GetAllModuleInfoToMemory();
	bool TransferModule(ModuleInfomationListStruct& ModuleInfo, CManageData& Data);
	CTransferModule();
	virtual ~CTransferModule();

protected:
	//�洢�ӿͻ��˻�ȡ�Ĳ�����
	CArrayModuleInfomationListStruct m_InfoArray;
//	//��¼��ǰ�����Ĳ����򷵻�ֵ����
//	CManageData m_Data;
};

#endif // !defined(AFX_TRANSFERMODULE_H__A082AC14_89A5_4B7A_91FF_65E8F09709DF__INCLUDED_)

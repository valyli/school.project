

///////////////////////////////////////////////////////////////////////////////
//�ļ����ݣ�������CModuleInfoList
//���ߣ�	���
//��д���ڣ�2003-03-20
//��Ҫ�ļ���Base.h
//�漰���ã�MSXML
///////////////////////////////////////////////////////////////////////////////


// ModuleInfoList.h: interface for the CModuleInfoList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODULEINFOLIST_H__55AD3907_95A5_4F24_AC37_871D815C3856__INCLUDED_)
#define AFX_MODULEINFOLIST_H__55AD3907_95A5_4F24_AC37_871D815C3856__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

///////////////////////////////////////////////////////////////////////////////
#include "Base.h"
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
//�๦�ܣ�	���ڻ�ȡ��̬��ģ����XML�ļ��д洢��������Ϣ
//�����ߣ�	���ж�̬��ģ���InfoList()
///////////////////////////////////////////////////////////////////////////////
class CModuleInfoList  
{
public:
	CModuleInfoList();
	virtual ~CModuleInfoList();

	bool GetInfoList(CArrayModuleInfomationListStruct &InfoListArray);

	//���ڼ�¼��ģ�������ļ����ƣ��ɵ����������ô��Ȼ���ٵ���GetInfoList()
	CString strModuleFileName;

protected:
	bool DisplayChild(IXMLDOMNodePtr pChild);
	bool DisplayChildren(IXMLDOMNodePtr pParent);


	///////////////////////////////////////////////////////////////////////////
	//��¼������XML��������FunctionSection��Ϣ
	CArrayModuleInfomationListStruct InfoArray;
	//��¼ǰһ�����
	IXMLDOMNodePtr pChildLast;
	//������ʱ��¼һ��FunctionSection��Ϣ
	ModuleInfomationListStruct Info;
};

#endif // !defined(AFX_MODULEINFOLIST_H__55AD3907_95A5_4F24_AC37_871D815C3856__INCLUDED_)

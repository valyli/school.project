// InfomationElementListTable.h: interface for the CInfomationElementListTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFOMATIONELEMENTLISTTABLE_H__CECF39C5_17C6_4D12_93E5_475812F5502E__INCLUDED_)
#define AFX_INFOMATIONELEMENTLISTTABLE_H__CECF39C5_17C6_4D12_93E5_475812F5502E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Base.h"

//���� ��Ϣ����б� �����ļ�XML����
//������ڵ��ļ���
//		InfomationElementListTable_Original.xml ���������ļ��Ļ�����Ϣ�ã�ǣ������ӡ��޸ı���
//		InfomationElementListTable.xml ����������Ϣ�õ��ļ���ǣ�����޸ı���
class CInfomationElementListTable  
{
public:
	//��¼������XML��������InfomationElementTableSection��Ϣ
	CArrayInfomationElementListTableStruct InfoArray;
	//������
	unsigned int  m_NameBaseId;
	//����������
	unsigned int  m_InfoServiceProviderId;

public:
	bool SaveToXML();
	bool AddInfomationElementList(InfomationElementListTableStruct &InfoList);
	bool GetAllInfomationElementListTable();
	bool GetNewInfomationElementListTableID(unsigned int& NewID);
	CInfomationElementListTable();
	virtual ~CInfomationElementListTable();

protected:
	///////////////////////////////////////////////////////////////////////////////
	//��¼ǰһ�����
	IXMLDOMNodePtr pChildLast;
	//������ʱ��¼һ��InfomationElementTableSection��Ϣ
	InfomationElementListTableStruct Info;
	//�����ж�xml�ļ��Ƿ�Ϊ��
	bool IsEmpty;
	//�����ж��Ƿ��Ѿ������ļ���Ϣ����������GetAllInfomationElementListTable()
	bool IsLoadXML;

protected:
	bool DisplayChild(IXMLDOMNodePtr pChild);
	bool DisplayChildren(IXMLDOMNodePtr pParent);

};

#endif // !defined(AFX_INFOMATIONELEMENTLISTTABLE_H__CECF39C5_17C6_4D12_93E5_475812F5502E__INCLUDED_)

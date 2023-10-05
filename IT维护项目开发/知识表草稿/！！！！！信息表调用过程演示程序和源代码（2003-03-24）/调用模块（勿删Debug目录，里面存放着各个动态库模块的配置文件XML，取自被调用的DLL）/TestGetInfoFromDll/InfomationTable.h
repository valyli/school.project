// InfomationTable.h: interface for the CInfomationTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFOMATIONTABLE_H__C7EFF0B6_64B2_4508_9331_70B5D7720D00__INCLUDED_)
#define AFX_INFOMATIONTABLE_H__C7EFF0B6_64B2_4508_9331_70B5D7720D00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




#include "Base.h"


//����InfomationTable����Ϣ��� �����ļ�XML����
//������ڵ��ļ���
//		InfomationTable_Original.xml ���������ļ��Ļ�����Ϣ�ã�ǣ������ӡ��޸ı���
class CInfomationTable
{
public:
	bool AddInfomationElementList(InfomationElementStruct &InfoList, CString TableName);
	bool GetNewInfomationElementID(unsigned int &NewID, CString TableName);
	bool SaveToXML(CArrayInfomationElementStruct& InfoListArray, CString TableName);
	bool GetAllInfomationElement(CArrayInfomationElementStruct& InfoListArray, CString TableName);
	bool CreateInfomationTable(unsigned int InfomationElementTableID, CString TableName);
	CInfomationTable();
	virtual ~CInfomationTable();

	//��¼��Ϣ���ļ��е�InfomationElementTableID
	unsigned int m_InfomationElementTableID;


protected:
	///////////////////////////////////////////////////////////////////////////////
	//��¼������XML��������InfomationElementSection��Ϣ
	CArrayInfomationElementStruct InfoArray;
	//��¼ǰһ�����
	IXMLDOMNodePtr pChildLast;
	//������ʱ��¼һ��InfomationElementSection��Ϣ
	InfomationElementStruct Info;
	//�����ж�xml�ļ��Ƿ�Ϊ��
	bool IsEmpty;


	bool DisplayChild(IXMLDOMNodePtr pChild);
	bool DisplayChildren(IXMLDOMNodePtr pParent);

};

#endif // !defined(AFX_INFOMATIONTABLE_H__C7EFF0B6_64B2_4508_9331_70B5D7720D00__INCLUDED_)

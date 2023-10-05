// InfomationElementListTable.h: interface for the CInfomationElementListTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFOMATIONELEMENTLISTTABLE_H__CECF39C5_17C6_4D12_93E5_475812F5502E__INCLUDED_)
#define AFX_INFOMATIONELEMENTLISTTABLE_H__CECF39C5_17C6_4D12_93E5_475812F5502E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Base.h"

//处理 信息项表列表 配置文件XML的类
//必须存在的文件：
//		InfomationElementListTable_Original.xml 导入配置文件的基本信息用，牵扯到添加、修改表项
//		InfomationElementListTable.xml 导入配置信息用的文件，牵扯到修改表项
class CInfomationElementListTable  
{
public:
	//记录所有在XML中描述的InfomationElementTableSection信息
	CArrayInfomationElementListTableStruct InfoArray;
	//发布者
	unsigned int  m_NameBaseId;
	//发布名称域
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
	//记录前一个结点
	IXMLDOMNodePtr pChildLast;
	//用于临时记录一个InfomationElementTableSection信息
	InfomationElementListTableStruct Info;
	//用于判断xml文件是否为空
	bool IsEmpty;
	//用于判断是否已经读入文件信息，即调用了GetAllInfomationElementListTable()
	bool IsLoadXML;

protected:
	bool DisplayChild(IXMLDOMNodePtr pChild);
	bool DisplayChildren(IXMLDOMNodePtr pParent);

};

#endif // !defined(AFX_INFOMATIONELEMENTLISTTABLE_H__CECF39C5_17C6_4D12_93E5_475812F5502E__INCLUDED_)

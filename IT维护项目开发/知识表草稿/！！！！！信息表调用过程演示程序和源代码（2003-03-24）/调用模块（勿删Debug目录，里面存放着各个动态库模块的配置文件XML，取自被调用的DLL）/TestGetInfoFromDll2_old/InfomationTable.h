// InfomationTable.h: interface for the CInfomationTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFOMATIONTABLE_H__C7EFF0B6_64B2_4508_9331_70B5D7720D00__INCLUDED_)
#define AFX_INFOMATIONTABLE_H__C7EFF0B6_64B2_4508_9331_70B5D7720D00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




#include "Base.h"


//处理InfomationTable（信息项表） 配置文件XML的类
//必须存在的文件：
//		InfomationTable_Original.xml 导入配置文件的基本信息用，牵扯到添加、修改表项
class CInfomationTable
{
public:
	bool AddInfomationElementList(InfomationElementStruct &InfoList);
	bool GetNewInfomationElementID(unsigned int &NewID);
	bool SaveToXML();
	bool GetAllInfomationElement();
	bool CreateInfomationTable();
	CInfomationTable();
	virtual ~CInfomationTable();

	//记录所有在XML中描述的InfomationElementSection信息
	CArrayInfomationElementStruct InfoArray;
	//记录信息表文件中的InfomationElementTableID
	unsigned int m_InfomationElementTableID;
	//记录要处理的信息表名称，和信息项表列表中的InfomationElementTableName_English项对应
	CString m_TableName;
	//发布者
	unsigned int  m_NameBaseId;
	//发布名称域
	unsigned int  m_InfoServiceProviderId;


protected:
	///////////////////////////////////////////////////////////////////////////////
	//记录前一个结点
	IXMLDOMNodePtr pChildLast;
	//用于临时记录一个InfomationElementSection信息
	InfomationElementStruct Info;
	//用于判断xml文件是否为空
	bool IsEmpty;
	//用于判断是否已经读入文件信息，即调用了GetAllInfomationElementListTable()
	bool IsLoadXML;


	bool DisplayChild(IXMLDOMNodePtr pChild);
	bool DisplayChildren(IXMLDOMNodePtr pParent);

};

#endif // !defined(AFX_INFOMATIONTABLE_H__C7EFF0B6_64B2_4508_9331_70B5D7720D00__INCLUDED_)

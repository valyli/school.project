

///////////////////////////////////////////////////////////////////////////////
//文件内容：包含类CModuleInfoList
//作者：	李佳
//编写日期：2003-03-20
//需要文件：Base.h
//涉及调用：MSXML
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
//类功能：	用于获取动态库模块在XML文件中存储的配置信息
//调用者：	所有动态库模块的InfoList()
///////////////////////////////////////////////////////////////////////////////
class CModuleInfoList  
{
public:
	CModuleInfoList();
	virtual ~CModuleInfoList();

	bool GetInfoList(CArrayModuleInfomationListStruct &InfoListArray);

	//用于记录此模块配置文件名称，由调用者先设置此项，然后再调用GetInfoList()
	CString strModuleFileName;

protected:
	bool DisplayChild(IXMLDOMNodePtr pChild);
	bool DisplayChildren(IXMLDOMNodePtr pParent);


	///////////////////////////////////////////////////////////////////////////
	//记录所有在XML中描述的FunctionSection信息
	CArrayModuleInfomationListStruct InfoArray;
	//记录前一个结点
	IXMLDOMNodePtr pChildLast;
	//用于临时记录一个FunctionSection信息
	ModuleInfomationListStruct Info;
};

#endif // !defined(AFX_MODULEINFOLIST_H__55AD3907_95A5_4F24_AC37_871D815C3856__INCLUDED_)

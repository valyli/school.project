//用于将XML文件中的数据映射到内存中


// XmlMemMapping.h: interface for the CXmlMemMapping class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMLMEMMAPPING_H__314D42D7_20CF_4D2F_A773_D6F9EE889837__INCLUDED_)
#define AFX_XMLMEMMAPPING_H__314D42D7_20CF_4D2F_A773_D6F9EE889837__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


///////////////////////////////////////////////////////////////////////////////
//Include for MSXML
#import <msxml.dll> named_guids
using namespace MSXML;

//Include for CArray
#include <afxtempl.h>
///////////////////////////////////////////////////////////////////////////////



class CXmlMemMapping  
{
public:
	bool LoadXml2Mem(CString strXmlFilename);
	void Test();
	CXmlMemMapping();
	virtual ~CXmlMemMapping();

public:
	//记录XML文档的句柄
	IXMLDOMDocumentPtr m_plDomDocument;
	//记录当前导入的文件名
	CString CurrentXmlFilename;
};

#endif // !defined(AFX_XMLMEMMAPPING_H__314D42D7_20CF_4D2F_A773_D6F9EE889837__INCLUDED_)

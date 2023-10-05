//���ڽ�XML�ļ��е�����ӳ�䵽�ڴ���


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
	//��¼XML�ĵ��ľ��
	IXMLDOMDocumentPtr m_plDomDocument;
	//��¼��ǰ������ļ���
	CString CurrentXmlFilename;
};

#endif // !defined(AFX_XMLMEMMAPPING_H__314D42D7_20CF_4D2F_A773_D6F9EE889837__INCLUDED_)

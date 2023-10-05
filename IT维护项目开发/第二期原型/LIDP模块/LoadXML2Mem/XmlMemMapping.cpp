// XmlMemMapping.cpp: implementation of the CXmlMemMapping class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "LoadXML2Mem.h"
#include "XmlMemMapping.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXmlMemMapping::CXmlMemMapping()
{

}

CXmlMemMapping::~CXmlMemMapping()
{

}

void CXmlMemMapping::Test()
{

}


//将XML文件导入到内存中
bool CXmlMemMapping::LoadXml2Mem(CString strXmlFilename)
{
	::CoInitialize(NULL);

	try
	{
		// Initialize COM
//		IXMLDOMElementPtr m_pDocRoot;

		HRESULT hr = m_plDomDocument.CreateInstance(CLSID_DOMDocument);
		if (FAILED(hr))
		{
			::MessageBox(0, "CreateInstance() Failed", "Internal Error", MB_OK);
			return false;
		}

		// convert xml file name string to something COM can handle (BSTR)
		_bstr_t bstrFileName;
		bstrFileName = strXmlFilename.AllocSysString();

		// call the IXMLDOMDocumentPtr's load function to load the XML document
		variant_t vResult;
		vResult = m_plDomDocument->load(bstrFileName);
		if (((bool)vResult) == TRUE) // success!
		{
			CurrentXmlFilename = strXmlFilename;
			// now that the document is loaded, we need to initialize the root pointer
			AfxMessageBox(m_plDomDocument->xml);
			return true;
		}
	}
	catch(_com_error &e)
	{
		::MessageBox(0, e.ErrorMessage(), "Internal Error", MB_OK);
		return false;
	}

	::CoUninitialize();
}

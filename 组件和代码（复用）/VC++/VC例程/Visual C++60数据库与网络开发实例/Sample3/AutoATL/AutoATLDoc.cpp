// AutoATLDoc.cpp : implementation of the CAutoATLDoc class
//

#include "stdafx.h"
#include "AutoATL.h"

#include "AutoATLDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoATLDoc

IMPLEMENT_DYNCREATE_ATL(CAutoATLDoc, CDocument)

BEGIN_MESSAGE_MAP(CAutoATLDoc, CDocument)
	//{{AFX_MSG_MAP(CAutoATLDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoATLDoc construction/destruction

CAutoATLDoc::CAutoATLDoc()
{
	// TODO: add one-time construction code here

}

CAutoATLDoc::~CAutoATLDoc()
{
}

BOOL CAutoATLDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CAutoATLDoc serialization

void CAutoATLDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CAutoATLDoc diagnostics

#ifdef _DEBUG
void CAutoATLDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAutoATLDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAutoATLDoc commands

STDMETHODIMP CAutoATLDoc::Hello()
{
	METHOD_PROLOGUE_ATL

	::MessageBox(NULL, GetTitle(), "Hello World", MB_OK | MB_ICONEXCLAMATION);

	return S_OK;
}

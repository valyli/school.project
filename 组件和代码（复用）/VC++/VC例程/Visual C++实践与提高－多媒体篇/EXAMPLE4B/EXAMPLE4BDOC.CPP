// Example4BDoc.cpp : implementation of the CExample4BDoc class
//

#include "stdafx.h"
#include "Example4B.h"

#include "Example4BDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExample4BDoc

IMPLEMENT_DYNCREATE(CExample4BDoc, CDocument)

BEGIN_MESSAGE_MAP(CExample4BDoc, CDocument)
	//{{AFX_MSG_MAP(CExample4BDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExample4BDoc construction/destruction

CExample4BDoc::CExample4BDoc()
{
	// TODO: add one-time construction code here

}

CExample4BDoc::~CExample4BDoc()
{
}

BOOL CExample4BDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CExample4BDoc serialization

void CExample4BDoc::Serialize(CArchive& ar)
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
// CExample4BDoc diagnostics

#ifdef _DEBUG
void CExample4BDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CExample4BDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExample4BDoc commands

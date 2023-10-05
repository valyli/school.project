// Example5BDoc.cpp : implementation of the CExample5BDoc class
//

#include "stdafx.h"
#include "Example5B.h"

#include "Example5BDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExample5BDoc

IMPLEMENT_DYNCREATE(CExample5BDoc, CDocument)

BEGIN_MESSAGE_MAP(CExample5BDoc, CDocument)
	//{{AFX_MSG_MAP(CExample5BDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExample5BDoc construction/destruction

CExample5BDoc::CExample5BDoc()
{
	// TODO: add one-time construction code here

}

CExample5BDoc::~CExample5BDoc()
{
}

BOOL CExample5BDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CExample5BDoc serialization

void CExample5BDoc::Serialize(CArchive& ar)
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
// CExample5BDoc diagnostics

#ifdef _DEBUG
void CExample5BDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CExample5BDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExample5BDoc commands

// Example3EDoc.cpp : implementation of the CExample3EDoc class
//

#include "stdafx.h"
#include "Example3E.h"

#include "Example3EDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExample3EDoc

IMPLEMENT_DYNCREATE(CExample3EDoc, CDocument)

BEGIN_MESSAGE_MAP(CExample3EDoc, CDocument)
	//{{AFX_MSG_MAP(CExample3EDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExample3EDoc construction/destruction

CExample3EDoc::CExample3EDoc()
{
	// TODO: add one-time construction code here

}

CExample3EDoc::~CExample3EDoc()
{
}

BOOL CExample3EDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CExample3EDoc serialization

void CExample3EDoc::Serialize(CArchive& ar)
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
// CExample3EDoc diagnostics

#ifdef _DEBUG
void CExample3EDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CExample3EDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExample3EDoc commands

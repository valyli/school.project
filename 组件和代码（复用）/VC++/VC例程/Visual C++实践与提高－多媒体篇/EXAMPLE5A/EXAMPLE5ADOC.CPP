// Example5ADoc.cpp : implementation of the CExample5ADoc class
//

#include "stdafx.h"
#include "Example5A.h"

#include "Example5ADoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExample5ADoc

IMPLEMENT_DYNCREATE(CExample5ADoc, CDocument)

BEGIN_MESSAGE_MAP(CExample5ADoc, CDocument)
	//{{AFX_MSG_MAP(CExample5ADoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExample5ADoc construction/destruction

CExample5ADoc::CExample5ADoc()
{
	// TODO: add one-time construction code here

}

CExample5ADoc::~CExample5ADoc()
{
}

BOOL CExample5ADoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CExample5ADoc serialization

void CExample5ADoc::Serialize(CArchive& ar)
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
// CExample5ADoc diagnostics

#ifdef _DEBUG
void CExample5ADoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CExample5ADoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExample5ADoc commands

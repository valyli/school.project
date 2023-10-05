// Example5DDoc.cpp : implementation of the CExample5DDoc class
//

#include "stdafx.h"
#include "Example5D.h"

#include "Example5DDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExample5DDoc

IMPLEMENT_DYNCREATE(CExample5DDoc, CDocument)

BEGIN_MESSAGE_MAP(CExample5DDoc, CDocument)
	//{{AFX_MSG_MAP(CExample5DDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExample5DDoc construction/destruction

CExample5DDoc::CExample5DDoc()
{
	// TODO: add one-time construction code here

}

CExample5DDoc::~CExample5DDoc()
{
}

BOOL CExample5DDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CExample5DDoc serialization

void CExample5DDoc::Serialize(CArchive& ar)
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
// CExample5DDoc diagnostics

#ifdef _DEBUG
void CExample5DDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CExample5DDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExample5DDoc commands

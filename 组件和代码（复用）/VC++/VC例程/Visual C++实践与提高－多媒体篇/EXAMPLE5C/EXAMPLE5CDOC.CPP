// Example5CDoc.cpp : implementation of the CExample5CDoc class
//

#include "stdafx.h"
#include "Example5C.h"

#include "Example5CDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExample5CDoc

IMPLEMENT_DYNCREATE(CExample5CDoc, CDocument)

BEGIN_MESSAGE_MAP(CExample5CDoc, CDocument)
	//{{AFX_MSG_MAP(CExample5CDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExample5CDoc construction/destruction

CExample5CDoc::CExample5CDoc()
{
	// TODO: add one-time construction code here

}

CExample5CDoc::~CExample5CDoc()
{
}

BOOL CExample5CDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CExample5CDoc serialization

void CExample5CDoc::Serialize(CArchive& ar)
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
// CExample5CDoc diagnostics

#ifdef _DEBUG
void CExample5CDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CExample5CDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExample5CDoc commands

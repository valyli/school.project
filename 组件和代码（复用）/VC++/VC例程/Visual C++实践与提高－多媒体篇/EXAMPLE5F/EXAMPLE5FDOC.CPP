// Example5FDoc.cpp : implementation of the CExample5FDoc class
//

#include "stdafx.h"
#include "Example5F.h"

#include "Example5FDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExample5FDoc

IMPLEMENT_DYNCREATE(CExample5FDoc, CDocument)

BEGIN_MESSAGE_MAP(CExample5FDoc, CDocument)
	//{{AFX_MSG_MAP(CExample5FDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExample5FDoc construction/destruction

CExample5FDoc::CExample5FDoc()
{
	// TODO: add one-time construction code here

}

CExample5FDoc::~CExample5FDoc()
{
}

BOOL CExample5FDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CExample5FDoc serialization

void CExample5FDoc::Serialize(CArchive& ar)
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
// CExample5FDoc diagnostics

#ifdef _DEBUG
void CExample5FDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CExample5FDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExample5FDoc commands

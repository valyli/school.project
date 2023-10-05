// TryListViewDoc.cpp : implementation of the CTryListViewDoc class
//

#include "stdafx.h"
#include "TryListView.h"

#include "TryListViewDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTryListViewDoc

IMPLEMENT_DYNCREATE(CTryListViewDoc, CDocument)

BEGIN_MESSAGE_MAP(CTryListViewDoc, CDocument)
	//{{AFX_MSG_MAP(CTryListViewDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTryListViewDoc construction/destruction

CTryListViewDoc::CTryListViewDoc()
{
	// TODO: add one-time construction code here

}

CTryListViewDoc::~CTryListViewDoc()
{
}

BOOL CTryListViewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTryListViewDoc serialization

void CTryListViewDoc::Serialize(CArchive& ar)
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
// CTryListViewDoc diagnostics

#ifdef _DEBUG
void CTryListViewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTryListViewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTryListViewDoc commands

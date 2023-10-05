// TryListInFormViewDoc.cpp : implementation of the CTryListInFormViewDoc class
//

#include "stdafx.h"
#include "TryListInFormView.h"

#include "TryListInFormViewDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTryListInFormViewDoc

IMPLEMENT_DYNCREATE(CTryListInFormViewDoc, CDocument)

BEGIN_MESSAGE_MAP(CTryListInFormViewDoc, CDocument)
	//{{AFX_MSG_MAP(CTryListInFormViewDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTryListInFormViewDoc construction/destruction

CTryListInFormViewDoc::CTryListInFormViewDoc()
{
	// TODO: add one-time construction code here

}

CTryListInFormViewDoc::~CTryListInFormViewDoc()
{
}

BOOL CTryListInFormViewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTryListInFormViewDoc serialization

void CTryListInFormViewDoc::Serialize(CArchive& ar)
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
// CTryListInFormViewDoc diagnostics

#ifdef _DEBUG
void CTryListInFormViewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTryListInFormViewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTryListInFormViewDoc commands

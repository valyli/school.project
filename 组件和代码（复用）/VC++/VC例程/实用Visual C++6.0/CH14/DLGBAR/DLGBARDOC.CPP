// dlgbarDoc.cpp : implementation of the CDlgbarDoc class
//

#include "stdafx.h"
#include "dlgbar.h"

#include "dlgbarDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgbarDoc

IMPLEMENT_DYNCREATE(CDlgbarDoc, CDocument)

BEGIN_MESSAGE_MAP(CDlgbarDoc, CDocument)
	//{{AFX_MSG_MAP(CDlgbarDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgbarDoc construction/destruction

CDlgbarDoc::CDlgbarDoc()
{
	// TODO: add one-time construction code here

}

CDlgbarDoc::~CDlgbarDoc()
{
}

BOOL CDlgbarDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDlgbarDoc serialization

void CDlgbarDoc::Serialize(CArchive& ar)
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
// CDlgbarDoc diagnostics

#ifdef _DEBUG
void CDlgbarDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDlgbarDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDlgbarDoc commands

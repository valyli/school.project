// ToolbarDoc.cpp : implementation of the CToolbarDoc class
//

#include "stdafx.h"
#include "Toolbar.h"

#include "ToolbarDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolbarDoc

IMPLEMENT_DYNCREATE(CToolbarDoc, CDocument)

BEGIN_MESSAGE_MAP(CToolbarDoc, CDocument)
	//{{AFX_MSG_MAP(CToolbarDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolbarDoc construction/destruction

CToolbarDoc::CToolbarDoc()
{
	// TODO: add one-time construction code here

}

CToolbarDoc::~CToolbarDoc()
{
}

BOOL CToolbarDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CToolbarDoc serialization

void CToolbarDoc::Serialize(CArchive& ar)
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
// CToolbarDoc diagnostics

#ifdef _DEBUG
void CToolbarDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CToolbarDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CToolbarDoc commands

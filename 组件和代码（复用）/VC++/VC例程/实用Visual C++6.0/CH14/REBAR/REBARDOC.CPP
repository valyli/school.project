// rebarDoc.cpp : implementation of the CRebarDoc class
//

#include "stdafx.h"
#include "rebar.h"

#include "rebarDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRebarDoc

IMPLEMENT_DYNCREATE(CRebarDoc, CDocument)

BEGIN_MESSAGE_MAP(CRebarDoc, CDocument)
	//{{AFX_MSG_MAP(CRebarDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRebarDoc construction/destruction

CRebarDoc::CRebarDoc()
{
	// TODO: add one-time construction code here

}

CRebarDoc::~CRebarDoc()
{
}

BOOL CRebarDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CRebarDoc serialization

void CRebarDoc::Serialize(CArchive& ar)
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
// CRebarDoc diagnostics

#ifdef _DEBUG
void CRebarDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRebarDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRebarDoc commands

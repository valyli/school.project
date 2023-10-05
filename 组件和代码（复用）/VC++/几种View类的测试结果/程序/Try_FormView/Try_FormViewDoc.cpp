// Try_FormViewDoc.cpp : implementation of the CTry_FormViewDoc class
//

#include "stdafx.h"
#include "Try_FormView.h"

#include "Try_FormViewDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTry_FormViewDoc

IMPLEMENT_DYNCREATE(CTry_FormViewDoc, CDocument)

BEGIN_MESSAGE_MAP(CTry_FormViewDoc, CDocument)
	//{{AFX_MSG_MAP(CTry_FormViewDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTry_FormViewDoc construction/destruction

CTry_FormViewDoc::CTry_FormViewDoc()
{
	// TODO: add one-time construction code here

}

CTry_FormViewDoc::~CTry_FormViewDoc()
{
}

BOOL CTry_FormViewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTry_FormViewDoc serialization

void CTry_FormViewDoc::Serialize(CArchive& ar)
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
// CTry_FormViewDoc diagnostics

#ifdef _DEBUG
void CTry_FormViewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTry_FormViewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTry_FormViewDoc commands

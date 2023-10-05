// SizeFormDoc.cpp : implementation of the CSizeFormDoc class
//

#include "stdafx.h"
#include "SizeForm.h"

#include "SizeFormDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSizeFormDoc

IMPLEMENT_DYNCREATE(CSizeFormDoc, CDocument)

BEGIN_MESSAGE_MAP(CSizeFormDoc, CDocument)
	//{{AFX_MSG_MAP(CSizeFormDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSizeFormDoc construction/destruction

CSizeFormDoc::CSizeFormDoc()
{
	// TODO: add one-time construction code here

}

CSizeFormDoc::~CSizeFormDoc()
{
}

BOOL CSizeFormDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSizeFormDoc serialization

void CSizeFormDoc::Serialize(CArchive& ar)
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
// CSizeFormDoc diagnostics

#ifdef _DEBUG
void CSizeFormDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSizeFormDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSizeFormDoc commands

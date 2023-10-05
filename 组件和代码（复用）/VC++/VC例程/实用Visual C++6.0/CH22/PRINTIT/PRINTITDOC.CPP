// PrintItDoc.cpp : implementation of the CPrintItDoc class
//

#include "stdafx.h"
#include "PrintIt.h"

#include "PrintItDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrintItDoc

IMPLEMENT_DYNCREATE(CPrintItDoc, CDocument)

BEGIN_MESSAGE_MAP(CPrintItDoc, CDocument)
	//{{AFX_MSG_MAP(CPrintItDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrintItDoc construction/destruction

CPrintItDoc::CPrintItDoc()
{
	// TODO: add one-time construction code here

}

CPrintItDoc::~CPrintItDoc()
{
}

BOOL CPrintItDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPrintItDoc serialization

void CPrintItDoc::Serialize(CArchive& ar)
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
// CPrintItDoc diagnostics

#ifdef _DEBUG
void CPrintItDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPrintItDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPrintItDoc commands

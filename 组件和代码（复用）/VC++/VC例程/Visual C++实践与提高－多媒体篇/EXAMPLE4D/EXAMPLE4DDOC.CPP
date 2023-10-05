// Example4DDoc.cpp : implementation of the CExample4DDoc class
//

#include "stdafx.h"
#include "Example4D.h"

#include "Example4DDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExample4DDoc

IMPLEMENT_DYNCREATE(CExample4DDoc, CDocument)

BEGIN_MESSAGE_MAP(CExample4DDoc, CDocument)
	//{{AFX_MSG_MAP(CExample4DDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExample4DDoc construction/destruction

CExample4DDoc::CExample4DDoc()
{
	// TODO: add one-time construction code here

}

CExample4DDoc::~CExample4DDoc()
{
}

BOOL CExample4DDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CExample4DDoc serialization

void CExample4DDoc::Serialize(CArchive& ar)
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
// CExample4DDoc diagnostics

#ifdef _DEBUG
void CExample4DDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CExample4DDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExample4DDoc commands

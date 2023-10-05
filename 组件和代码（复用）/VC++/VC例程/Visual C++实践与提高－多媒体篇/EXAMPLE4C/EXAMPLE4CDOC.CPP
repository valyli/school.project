// Example4CDoc.cpp : implementation of the CExample4CDoc class
//

#include "stdafx.h"
#include "Example4C.h"

#include "Example4CDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExample4CDoc

IMPLEMENT_DYNCREATE(CExample4CDoc, CDocument)

BEGIN_MESSAGE_MAP(CExample4CDoc, CDocument)
	//{{AFX_MSG_MAP(CExample4CDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExample4CDoc construction/destruction

CExample4CDoc::CExample4CDoc()
{
	// TODO: add one-time construction code here

}

CExample4CDoc::~CExample4CDoc()
{
}

BOOL CExample4CDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CExample4CDoc serialization

void CExample4CDoc::Serialize(CArchive& ar)
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
// CExample4CDoc diagnostics

#ifdef _DEBUG
void CExample4CDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CExample4CDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExample4CDoc commands

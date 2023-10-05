// TreeVDoc.cpp : implementation of the CTreeVDoc class
//

#include "stdafx.h"
#include "TreeV.h"

#include "TreeVDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeVDoc

IMPLEMENT_DYNCREATE(CTreeVDoc, CDocument)

BEGIN_MESSAGE_MAP(CTreeVDoc, CDocument)
	//{{AFX_MSG_MAP(CTreeVDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeVDoc construction/destruction

CTreeVDoc::CTreeVDoc()
{
	// TODO: add one-time construction code here

}

CTreeVDoc::~CTreeVDoc()
{
}

BOOL CTreeVDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTreeVDoc serialization

void CTreeVDoc::Serialize(CArchive& ar)
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
// CTreeVDoc diagnostics

#ifdef _DEBUG
void CTreeVDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTreeVDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTreeVDoc commands

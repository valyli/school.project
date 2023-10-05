// Exmaple4ADoc.cpp : implementation of the CExmaple4ADoc class
//

#include "stdafx.h"
#include "Exmaple4A.h"

#include "Exmaple4ADoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExmaple4ADoc

IMPLEMENT_DYNCREATE(CExmaple4ADoc, CDocument)

BEGIN_MESSAGE_MAP(CExmaple4ADoc, CDocument)
	//{{AFX_MSG_MAP(CExmaple4ADoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExmaple4ADoc construction/destruction

CExmaple4ADoc::CExmaple4ADoc()
{
	// TODO: add one-time construction code here

}

CExmaple4ADoc::~CExmaple4ADoc()
{
}

BOOL CExmaple4ADoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CExmaple4ADoc serialization

void CExmaple4ADoc::Serialize(CArchive& ar)
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
// CExmaple4ADoc diagnostics

#ifdef _DEBUG
void CExmaple4ADoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CExmaple4ADoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExmaple4ADoc commands

// UsingDBDoc.cpp : implementation of the CUsingDBDoc class
//

#include "stdafx.h"
#include "UsingDB.h"

#include "UsingDBSet.h"
#include "UsingDBDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUsingDBDoc

IMPLEMENT_DYNCREATE(CUsingDBDoc, CDocument)

BEGIN_MESSAGE_MAP(CUsingDBDoc, CDocument)
	//{{AFX_MSG_MAP(CUsingDBDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUsingDBDoc construction/destruction

CUsingDBDoc::CUsingDBDoc()
{
	// TODO: add one-time construction code here

}

CUsingDBDoc::~CUsingDBDoc()
{
}

BOOL CUsingDBDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CUsingDBDoc diagnostics

#ifdef _DEBUG
void CUsingDBDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CUsingDBDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CUsingDBDoc commands

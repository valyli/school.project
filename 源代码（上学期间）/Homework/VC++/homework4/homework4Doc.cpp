// homework4Doc.cpp : implementation of the CHomework4Doc class
//

#include "stdafx.h"
#include "homework4.h"

#include "homework4Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHomework4Doc

IMPLEMENT_DYNCREATE(CHomework4Doc, CDocument)

BEGIN_MESSAGE_MAP(CHomework4Doc, CDocument)
	//{{AFX_MSG_MAP(CHomework4Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHomework4Doc construction/destruction

CHomework4Doc::CHomework4Doc()
{
	// TODO: add one-time construction code here

}

CHomework4Doc::~CHomework4Doc()
{
}

BOOL CHomework4Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CHomework4Doc serialization

void CHomework4Doc::Serialize(CArchive& ar)
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
// CHomework4Doc diagnostics

#ifdef _DEBUG
void CHomework4Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHomework4Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHomework4Doc commands

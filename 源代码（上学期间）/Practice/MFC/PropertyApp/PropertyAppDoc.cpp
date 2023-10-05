// PropertyAppDoc.cpp : implementation of the CPropertyAppDoc class
//

#include "stdafx.h"
#include "PropertyApp.h"

#include "PropertyAppDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertyAppDoc

IMPLEMENT_DYNCREATE(CPropertyAppDoc, CDocument)

BEGIN_MESSAGE_MAP(CPropertyAppDoc, CDocument)
	//{{AFX_MSG_MAP(CPropertyAppDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyAppDoc construction/destruction

CPropertyAppDoc::CPropertyAppDoc()
{
	// TODO: add one-time construction code here

}

CPropertyAppDoc::~CPropertyAppDoc()
{
}

BOOL CPropertyAppDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPropertyAppDoc serialization

void CPropertyAppDoc::Serialize(CArchive& ar)
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
// CPropertyAppDoc diagnostics

#ifdef _DEBUG
void CPropertyAppDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPropertyAppDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPropertyAppDoc commands

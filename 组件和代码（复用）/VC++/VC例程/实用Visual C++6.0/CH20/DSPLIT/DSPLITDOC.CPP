// DsplitDoc.cpp : implementation of the CDsplitDoc class
//

#include "stdafx.h"
#include "Dsplit.h"

#include "DsplitDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDsplitDoc

IMPLEMENT_DYNCREATE(CDsplitDoc, CDocument)

BEGIN_MESSAGE_MAP(CDsplitDoc, CDocument)
	//{{AFX_MSG_MAP(CDsplitDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDsplitDoc construction/destruction

CDsplitDoc::CDsplitDoc()
{
	// TODO: add one-time construction code here

}

CDsplitDoc::~CDsplitDoc()
{
}

BOOL CDsplitDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDsplitDoc serialization

void CDsplitDoc::Serialize(CArchive& ar)
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
// CDsplitDoc diagnostics

#ifdef _DEBUG
void CDsplitDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDsplitDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDsplitDoc commands

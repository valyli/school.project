// StatusMouseDoc.cpp : implementation of the CStatusMouseDoc class
//

#include "stdafx.h"
#include "StatusMouse.h"

#include "StatusMouseDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatusMouseDoc

IMPLEMENT_DYNCREATE(CStatusMouseDoc, CDocument)

BEGIN_MESSAGE_MAP(CStatusMouseDoc, CDocument)
	//{{AFX_MSG_MAP(CStatusMouseDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatusMouseDoc construction/destruction

CStatusMouseDoc::CStatusMouseDoc()
{
	// TODO: add one-time construction code here

}

CStatusMouseDoc::~CStatusMouseDoc()
{
}

BOOL CStatusMouseDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CStatusMouseDoc serialization

void CStatusMouseDoc::Serialize(CArchive& ar)
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
// CStatusMouseDoc diagnostics

#ifdef _DEBUG
void CStatusMouseDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStatusMouseDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStatusMouseDoc commands

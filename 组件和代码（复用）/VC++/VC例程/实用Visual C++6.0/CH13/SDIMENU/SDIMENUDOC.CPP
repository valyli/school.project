// sdimenuDoc.cpp : implementation of the CSdimenuDoc class
//

#include "stdafx.h"
#include "sdimenu.h"

#include "sdimenuDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSdimenuDoc

IMPLEMENT_DYNCREATE(CSdimenuDoc, CDocument)

BEGIN_MESSAGE_MAP(CSdimenuDoc, CDocument)
	//{{AFX_MSG_MAP(CSdimenuDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSdimenuDoc construction/destruction

CSdimenuDoc::CSdimenuDoc()
{
	// TODO: add one-time construction code here

}

CSdimenuDoc::~CSdimenuDoc()
{
}

BOOL CSdimenuDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSdimenuDoc serialization

void CSdimenuDoc::Serialize(CArchive& ar)
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
// CSdimenuDoc diagnostics

#ifdef _DEBUG
void CSdimenuDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSdimenuDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSdimenuDoc commands

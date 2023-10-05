// LIJDoc.cpp : implementation of the CLIJDoc class
//

#include "stdafx.h"
#include "LIJ.h"

#include "LIJDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLIJDoc

IMPLEMENT_DYNCREATE(CLIJDoc, CDocument)

BEGIN_MESSAGE_MAP(CLIJDoc, CDocument)
	//{{AFX_MSG_MAP(CLIJDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLIJDoc construction/destruction

CLIJDoc::CLIJDoc()
{
	// TODO: add one-time construction code here

}

CLIJDoc::~CLIJDoc()
{
}

BOOL CLIJDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CLIJDoc serialization

void CLIJDoc::Serialize(CArchive& ar)
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
// CLIJDoc diagnostics

#ifdef _DEBUG
void CLIJDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLIJDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLIJDoc commands

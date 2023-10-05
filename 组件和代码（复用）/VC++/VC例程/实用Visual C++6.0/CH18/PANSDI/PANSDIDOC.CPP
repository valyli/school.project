// PanSDIDoc.cpp : implementation of the CPanSDIDoc class
//

#include "stdafx.h"
#include "PanSDI.h"

#include "PanSDIDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPanSDIDoc

IMPLEMENT_DYNCREATE(CPanSDIDoc, CDocument)

BEGIN_MESSAGE_MAP(CPanSDIDoc, CDocument)
	//{{AFX_MSG_MAP(CPanSDIDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPanSDIDoc construction/destruction

CPanSDIDoc::CPanSDIDoc()
{
	// TODO: add one-time construction code here

}

CPanSDIDoc::~CPanSDIDoc()
{
}

BOOL CPanSDIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPanSDIDoc serialization

void CPanSDIDoc::Serialize(CArchive& ar)
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
// CPanSDIDoc diagnostics

#ifdef _DEBUG
void CPanSDIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPanSDIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPanSDIDoc commands

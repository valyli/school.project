// SimpTextDoc.cpp : implementation of the CSimpTextDoc class
//

#include "stdafx.h"
#include "SimpText.h"

#include "SimpTextDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimpTextDoc

IMPLEMENT_DYNCREATE(CSimpTextDoc, CDocument)

BEGIN_MESSAGE_MAP(CSimpTextDoc, CDocument)
	//{{AFX_MSG_MAP(CSimpTextDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpTextDoc construction/destruction

CSimpTextDoc::CSimpTextDoc()
{
	// TODO: add one-time construction code here

}

CSimpTextDoc::~CSimpTextDoc()
{
}

BOOL CSimpTextDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSimpTextDoc serialization

void CSimpTextDoc::Serialize(CArchive& ar)
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
// CSimpTextDoc diagnostics

#ifdef _DEBUG
void CSimpTextDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSimpTextDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSimpTextDoc commands

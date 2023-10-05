// SoundDoc.cpp : implementation of the CSoundDoc class
//

#include "stdafx.h"
#include "Sound.h"

#include "SoundDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSoundDoc

IMPLEMENT_DYNCREATE(CSoundDoc, CDocument)

BEGIN_MESSAGE_MAP(CSoundDoc, CDocument)
	//{{AFX_MSG_MAP(CSoundDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSoundDoc construction/destruction

CSoundDoc::CSoundDoc()
{
	// TODO: add one-time construction code here

}

CSoundDoc::~CSoundDoc()
{
}

BOOL CSoundDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSoundDoc serialization

void CSoundDoc::Serialize(CArchive& ar)
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
// CSoundDoc diagnostics

#ifdef _DEBUG
void CSoundDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSoundDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSoundDoc commands

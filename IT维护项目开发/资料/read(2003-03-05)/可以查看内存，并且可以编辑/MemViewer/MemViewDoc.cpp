// MemViewDoc.cpp : implementation of the CMemViewDoc class
//

#include "stdafx.h"
#include "MemView.h"

#include "MemViewDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMemViewDoc

IMPLEMENT_DYNCREATE(CMemViewDoc, CDocument)

BEGIN_MESSAGE_MAP(CMemViewDoc, CDocument)
	//{{AFX_MSG_MAP(CMemViewDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMemViewDoc construction/destruction

CMemViewDoc::CMemViewDoc()
{
}

CMemViewDoc::~CMemViewDoc()
{
}

BOOL CMemViewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument()) return FALSE;

    SetTitle( "");

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CMemViewDoc commands

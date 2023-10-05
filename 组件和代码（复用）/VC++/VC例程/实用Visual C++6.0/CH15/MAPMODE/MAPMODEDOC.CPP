// MapModeDoc.cpp : implementation of the CMapModeDoc class
//

#include "stdafx.h"
#include "MapMode.h"

#include "MapModeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapModeDoc

IMPLEMENT_DYNCREATE(CMapModeDoc, CDocument)

BEGIN_MESSAGE_MAP(CMapModeDoc, CDocument)
	//{{AFX_MSG_MAP(CMapModeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapModeDoc construction/destruction

CMapModeDoc::CMapModeDoc()
{
	// TODO: add one-time construction code here

}

CMapModeDoc::~CMapModeDoc()
{
}

BOOL CMapModeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMapModeDoc serialization

void CMapModeDoc::Serialize(CArchive& ar)
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
// CMapModeDoc diagnostics

#ifdef _DEBUG
void CMapModeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMapModeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMapModeDoc commands

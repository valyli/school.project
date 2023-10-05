// MyPointDoc.cpp : implementation of the CMyPointDoc class
//

#include "stdafx.h"
#include "MyPoint.h"

#include "MyPointDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyPointDoc

IMPLEMENT_DYNCREATE(CMyPointDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyPointDoc, CDocument)
	//{{AFX_MSG_MAP(CMyPointDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyPointDoc construction/destruction

CMyPointDoc::CMyPointDoc()
{
	// TODO: add one-time construction code here

}

CMyPointDoc::~CMyPointDoc()
{
}

BOOL CMyPointDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	m_index = 0;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyPointDoc serialization

void CMyPointDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar<<m_index;
		for(int i=0;i<=m_index;i++)
			ar<<points[i].x<<points[i].y;
	}
	else
	{
		// TODO: add loading code here
		ar>>m_index;
		for(int i=0;i<=m_index;i++)
			ar>>points[i].x>>points[i].y;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMyPointDoc diagnostics

#ifdef _DEBUG
void CMyPointDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyPointDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyPointDoc commands

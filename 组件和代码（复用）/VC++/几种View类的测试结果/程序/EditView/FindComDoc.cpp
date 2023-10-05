// FindComDoc.cpp : implementation of the CFindComDoc class
//

#include "stdafx.h"
#include "FindCom.h"

#include "FindComDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindComDoc

IMPLEMENT_DYNCREATE(CFindComDoc, CDocument)

BEGIN_MESSAGE_MAP(CFindComDoc, CDocument)
	//{{AFX_MSG_MAP(CFindComDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindComDoc construction/destruction

CFindComDoc::CFindComDoc()
{
	// TODO: add one-time construction code here

}

CFindComDoc::~CFindComDoc()
{
}

BOOL CFindComDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CEditView*)m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFindComDoc serialization

void CFindComDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CFindComDoc diagnostics

#ifdef _DEBUG
void CFindComDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFindComDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFindComDoc commands

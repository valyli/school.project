// SSplitDoc.cpp : implementation of the CSSplitDoc class
//

#include "stdafx.h"
#include "SSplit.h"

#include "SSplitDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSSplitDoc

IMPLEMENT_DYNCREATE(CSSplitDoc, CDocument)

BEGIN_MESSAGE_MAP(CSSplitDoc, CDocument)
	//{{AFX_MSG_MAP(CSSplitDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSSplitDoc construction/destruction

CSSplitDoc::CSSplitDoc()
{
	// TODO: add one-time construction code here

}

CSSplitDoc::~CSSplitDoc()
{
}

BOOL CSSplitDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CEditView*)m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSSplitDoc serialization

void CSSplitDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CSSplitDoc diagnostics

#ifdef _DEBUG
void CSSplitDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSSplitDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSSplitDoc commands

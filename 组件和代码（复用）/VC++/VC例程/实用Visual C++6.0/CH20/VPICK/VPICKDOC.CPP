// VPickDoc.cpp : implementation of the CVPickDoc class
//

#include "stdafx.h"
#include "VPick.h"

#include "VPickDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVPickDoc

IMPLEMENT_DYNCREATE(CVPickDoc, CDocument)

BEGIN_MESSAGE_MAP(CVPickDoc, CDocument)
	//{{AFX_MSG_MAP(CVPickDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVPickDoc construction/destruction

CVPickDoc::CVPickDoc()
{
	// TODO: add one-time construction code here

}

CVPickDoc::~CVPickDoc()
{
}

BOOL CVPickDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CEditView*)m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CVPickDoc serialization

void CVPickDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CVPickDoc diagnostics

#ifdef _DEBUG
void CVPickDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVPickDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVPickDoc commands

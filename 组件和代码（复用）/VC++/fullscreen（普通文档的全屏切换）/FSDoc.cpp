// FSDoc.cpp : implementation of the CFSDoc class
//

#include "stdafx.h"
#include "FS.h"

#include "FSDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFSDoc

IMPLEMENT_DYNCREATE(CFSDoc, CDocument)

BEGIN_MESSAGE_MAP(CFSDoc, CDocument)
	//{{AFX_MSG_MAP(CFSDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFSDoc construction/destruction

CFSDoc::CFSDoc()
{
	// TODO: add one-time construction code here

}

CFSDoc::~CFSDoc()
{
}

BOOL CFSDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFSDoc serialization

void CFSDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CFSDoc diagnostics

#ifdef _DEBUG
void CFSDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFSDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFSDoc commands

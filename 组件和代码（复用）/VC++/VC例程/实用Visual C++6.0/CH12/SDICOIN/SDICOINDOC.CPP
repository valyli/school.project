// SDICoinDoc.cpp : implementation of the CSDICoinDoc class
//

#include "stdafx.h"
#include "SDICoin.h"

#include "SDICoinDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSDICoinDoc

IMPLEMENT_DYNCREATE(CSDICoinDoc, CDocument)

BEGIN_MESSAGE_MAP(CSDICoinDoc, CDocument)
	//{{AFX_MSG_MAP(CSDICoinDoc)
	ON_COMMAND(ID_EDIT_ADD_COIN, OnEditAddCoin)
	ON_COMMAND(ID_EDIT_REMOVE_COIN, OnEditRemoveCoin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSDICoinDoc construction/destruction

CSDICoinDoc::CSDICoinDoc()
{
	// TODO: add one-time construction code here

}

CSDICoinDoc::~CSDICoinDoc()
{
}

BOOL CSDICoinDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSDICoinDoc serialization

void CSDICoinDoc::Serialize(CArchive& ar)
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
// CSDICoinDoc diagnostics

#ifdef _DEBUG
void CSDICoinDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSDICoinDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSDICoinDoc commands

int CSDICoinDoc::GetCoinCount()
{
 return m_nCoins;
}

void CSDICoinDoc::DeleteContents() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_nCoins=1;
	CDocument::DeleteContents();
}

void CSDICoinDoc::OnEditAddCoin() 
{
	// TODO: Add your command handler code here
	
    // ** Increase the number of coins
	m_nCoins++;

    // ** Update View to redraw coin stack
	UpdateAllViews(NULL);
}

void CSDICoinDoc::OnEditRemoveCoin() 
{
	// TODO: Add your command handler code here
	
	// ** Decrease the number of coins
	if (m_nCoins>0)
		m_nCoins--;

	// ** Update view to redraw coin stack
	UpdateAllViews(NULL);
}

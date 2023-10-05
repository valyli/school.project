// MDIBillDoc.cpp : implementation file
//

#include "stdafx.h"
#include "MDICoin.h"
#include "MDIBillDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMDIBillDoc

IMPLEMENT_DYNCREATE(CMDIBillDoc, CDocument)

CMDIBillDoc::CMDIBillDoc()
{
	m_nBills = 1;
}

BOOL CMDIBillDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CMDIBillDoc::~CMDIBillDoc()
{
}


BEGIN_MESSAGE_MAP(CMDIBillDoc, CDocument)
	//{{AFX_MSG_MAP(CMDIBillDoc)
	ON_COMMAND(ID_EDIT_ADD_BILL, OnEditAddBill)
	ON_COMMAND(ID_EDIT_REMOVE_BILL, OnEditRemoveBill)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMDIBillDoc diagnostics

#ifdef _DEBUG
void CMDIBillDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMDIBillDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMDIBillDoc serialization

void CMDIBillDoc::Serialize(CArchive& ar)
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
// CMDIBillDoc commands

int CMDIBillDoc::GetBillCount()
{
	return m_nBills;
}

void CMDIBillDoc::OnEditAddBill() 
{
	// TODO: Add your command handler code here
	m_nBills++;
	UpdateAllViews(NULL);
}

void CMDIBillDoc::OnEditRemoveBill() 
{
	// TODO: Add your command handler code here
	if (m_nBills >0 )
		m_nBills--;
	UpdateAllViews(NULL);
	
}

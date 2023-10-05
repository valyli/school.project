// PageB.cpp : implementation file
//

#include "stdafx.h"
#include "PropertyApp.h"
#include "PageB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageB property page

IMPLEMENT_DYNCREATE(CPageB, CPropertyPage)

CPageB::CPageB() : CPropertyPage(CPageB::IDD)
{
	//{{AFX_DATA_INIT(CPageB)
	m_check = FALSE;
	//}}AFX_DATA_INIT
}

CPageB::~CPageB()
{
}

void CPageB::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageB)
	DDX_Check(pDX, IDC_CHECK, m_check);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageB, CPropertyPage)
	//{{AFX_MSG_MAP(CPageB)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageB message handlers

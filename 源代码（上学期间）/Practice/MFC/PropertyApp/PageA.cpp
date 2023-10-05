// PageA.cpp : implementation file
//

#include "stdafx.h"
#include "PropertyApp.h"
#include "PageA.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageA property page

IMPLEMENT_DYNCREATE(CPageA, CPropertyPage)

CPageA::CPageA() : CPropertyPage(CPageA::IDD)
{
	//{{AFX_DATA_INIT(CPageA)
	m_edit = _T("");
	//}}AFX_DATA_INIT
}

CPageA::~CPageA()
{
}

void CPageA::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageA)
	DDX_Text(pDX, IDC_EDIT, m_edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageA, CPropertyPage)
	//{{AFX_MSG_MAP(CPageA)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageA message handlers

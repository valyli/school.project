// Scroll.cpp : implementation file
//

#include "stdafx.h"
#include "Progress.h"
#include "Scroll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScroll dialog


CScroll::CScroll(CWnd* pParent /*=NULL*/)
	: CDialog(CScroll::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScroll)
	m_ScrollBar1 = 0;
	m_ScrollBar2 = 0;
	//}}AFX_DATA_INIT
}


void CScroll::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScroll)
	DDX_Scroll(pDX, IDC_SCROLLBAR1, m_ScrollBar1);
	DDX_Scroll(pDX, IDC_SCROLLBAR2, m_ScrollBar2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScroll, CDialog)
	//{{AFX_MSG_MAP(CScroll)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScroll message handlers

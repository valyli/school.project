// Modeless.cpp : implementation file
//

#include "stdafx.h"
#include "MLaunchDlg.h"
#include "Modeless.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModeless dialog


CModeless::CModeless(CMLaunchDlgDlg* pParent /*=NULL*/)
	: CDialog(CModeless::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModeless)
	m_DispMsg = _T("");
	//}}AFX_DATA_INIT

	//*Create the modeless dialog box window
	if (Create(CModeless::IDD,pParent))
	{
		//**Creation succeededso show the window
		ShowWindow(SW_SHOW);
	}
	m_pParent=pParent;
}


void CModeless::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModeless)
	DDX_Text(pDX, IDC_EDIT1, m_DispMsg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModeless, CDialog)
	//{{AFX_MSG_MAP(CModeless)
	ON_BN_CLICKED(IDC_POP, OnPop)
	ON_BN_CLICKED(IDC_POW, OnPow)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModeless message handlers

void CModeless::OnPop() 
{
	// TODO: Add your control notification handler code here

	m_pParent->m_DisplayList.AddString("**POP**");
}

void CModeless::OnPow() 
{
	// TODO: Add your control notification handler code here
	m_pParent->m_DisplayList.AddString("**POW**");
}

extern CModeless* g_pDlgModeless;
void CModeless::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnClose();
	delete this;
	g_pDlgModeless=NULL;
}

// Modeless.cpp : implementation file
//

#include "stdafx.h"
#include "MLaunch.h"
#include "Modeless.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModeless dialog


CModeless::CModeless(CMLaunchDlg* pParent /*=NULL*/)
	: CDialog(CModeless::IDD, pParent),m_pParent(pParent)
{
	//{{AFX_DATA_INIT(CModeless)
	m_DispMsg = _T("");
	//}}AFX_DATA_INIT

	// ** Creat the modeless dialog box window
	if (Create(CModeless::IDD,pParent))
	{
		// ** Creation succeeded so show the window
		ShowWindow(SW_SHOW);
	}
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
   m_pParent->m_DisplayList.AddString("**POP**");	
}

void CModeless::OnPow() 
{
   m_pParent->m_DisplayList.AddString("**POW**");	
}

extern CModeless* g_pDlgModeless;
void CModeless::OnClose() 
{

	CDialog::OnClose();
	   delete this;
   g_pDlgModeless = NULL;

}

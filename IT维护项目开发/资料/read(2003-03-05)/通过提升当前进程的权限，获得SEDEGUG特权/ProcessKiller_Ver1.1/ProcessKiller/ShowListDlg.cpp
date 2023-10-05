// ShowListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "processkiller.h"
#include "ShowListDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowListDlg dialog


CShowListDlg::CShowListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShowListDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShowListDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CShowListDlg::~CShowListDlg()
{

}

void CShowListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowListDlg)
	DDX_Control(pDX, IDC_LIST1, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShowListDlg, CDialog)
	//{{AFX_MSG_MAP(CShowListDlg)
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowListDlg message handlers

BOOL CShowListDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	//Init ListCtrl
	m_List.InsertColumn( 0, "FNAME", LVCFMT_LEFT, 80 );
	m_List.InsertColumn( 1, "FPATH", LVCFMT_LEFT, 250 );
	
	DWORD dwStyle = m_List.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_INFOTIP;
	m_List.SetExtendedStyle( dwStyle );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CShowListDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
   CRect rect;
   GetClientRect( &rect );
	if ( IsWindow( m_List.m_hWnd ) ) {
		m_List.MoveWindow( 10, 10, rect.right-20, rect.bottom-20 );
	}
}

void CShowListDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnClose();
	DestroyWindow();
}

void CShowListDlg::OnDestroy()
// 因为建在堆上，所以要delete自己
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	delete this;
}

BOOL CShowListDlg::ShowModulesList(DWORD dwPID)
//显示进程的模块列表
{
	//Get Modules Count
	DWORD dwModCount;
	if ( ! ::EnumProcessModulesInfo( dwPID, NULL, 0, &dwModCount ) ) {
		return FALSE;
	}
	LPMODULEINFO lpModInfo = new MODULEINFO[dwModCount];
	if ( NULL == lpModInfo ) {
		return FALSE;
	}
	
	// Get Modules Info
	if ( ! ::EnumProcessModulesInfo( dwPID, lpModInfo, dwModCount, &dwModCount ) ) {
		delete[] lpModInfo;
		return FALSE;
	}
	
	SetWindowText( lpModInfo[0].strName );
	//Init ListCtrl
	if ( m_List.GetItemCount() > 0 ) {
		m_List.DeleteAllItems();
	}
	
	//Show Modules Info In ListCtrl
	for ( ULONG IndexMod=1; IndexMod < dwModCount; IndexMod++ ) {
		
		m_List.InsertItem( IndexMod-1, lpModInfo[IndexMod].strName );
		m_List.SetItemText( IndexMod-1, 1, lpModInfo[IndexMod].strPath );
	}
	
	delete[] lpModInfo;
	
	// Show Dialg
	ShowWindow( SW_SHOW );
	
	return TRUE;
}

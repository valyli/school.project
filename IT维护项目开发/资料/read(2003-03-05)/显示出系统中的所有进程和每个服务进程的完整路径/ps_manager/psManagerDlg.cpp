// psManagerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "psManager.h"
#include "psManagerDlg.h"
#include "TerminatorHelpers.h"
#include "ConfirmTerminationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPsManagerDlg dialog

CPsManagerDlg::CPsManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPsManagerDlg::IDD, pParent),m_dwSelectedPID( 0 )
{
	//{{AFX_DATA_INIT(CPsManagerDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


BEGIN_MESSAGE_MAP(CPsManagerDlg, CDialog)
	//{{AFX_MSG_MAP(CPsManagerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_REFRESH, OnRefresh)
	ON_BN_CLICKED(IDC_TERMINATE, OnTerminate)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_HAISAN, OnHaisan)
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CPsManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPsManagerDlg)
	DDX_Control(pDX, IDC_PROCESS_LIST, m_ctlProcesses);
	//}}AFX_DATA_MAP

	if( !pDX->m_bSaveAndValidate )
	{
		RefreshList();
	}

}

DWORD CPsManagerDlg::GetSelectedPID() const
{
	return( m_dwSelectedPID );
}

/////////////////////////////////////////////////////////////////////////////

CString CPsManagerDlg::GetSelectedName() const
{
	return( m_sSelectedName );
}

/////////////////////////////////////////////////////////////////////////////

CString CPsManagerDlg::GetSelectedPath() const
{
	return( m_sSelectedPath );
}

void CPsManagerDlg::CProcessesList::DeleteZoobieItem(unsigned long aProcesses[],DWORD cProcess)
{
	for(int i=0;i<GetItemCount();i++){
		for(unsigned long idx=0;idx<cProcess;idx++){
				CString sPID;
				sPID.Format( "%d", aProcesses[ idx ] );
				if(sPID.CompareNoCase(GetItemText(i,1)) == 0) break;
		}
		if(idx >= cProcess) DeleteItem(i);
	}
}

void CPsManagerDlg::RefreshList() 
{
//	m_ctlProcesses.DeleteAllItems();


	DWORD aProcesses[ 1024 ];
    DWORD cProcesses = GetProcessIDs( aProcesses, sizeof( aProcesses ) );

	DWORD idxList = 0;
	

	m_ctlProcesses.DeleteZoobieItem(aProcesses,cProcesses);


	for( DWORD idx = 0; idx < cProcesses; idx++ )
	{
		CString sName = GetProcessBaseModuleName( aProcesses[ idx ] );

		if( sName.IsEmpty() )
		{
			continue;
		}

	
		CString sPID;
		sPID.Format( "%d", aProcesses[ idx ] );
		if(m_ctlProcesses.FindPIDIndex(aProcesses[ idx ]) >= 0) continue;
		
		m_ctlProcesses.InsertItem( idxList, sName );
		m_ctlProcesses.SetItemText( idxList, 1, sPID );
		m_ctlProcesses.SetItemText( idxList, 2, GetProcessPath( aProcesses[ idx ] ) );
		m_ctlProcesses.SetItemData( idxList, aProcesses[ idx ] );

		idxList++;
	}



}
BOOL CPsManagerDlg::CopySelectedItem()
{
	int idx = m_ctlProcesses.GetNextItem( -1, LVNI_SELECTED );

	if( -1 == idx )
	{
		m_dwSelectedPID = 0;
		m_sSelectedName.Empty();
		m_sSelectedPath.Empty();
	}
	else
	{
		m_dwSelectedPID = m_ctlProcesses.GetItemData( idx );
		m_sSelectedName = m_ctlProcesses.GetItemText( idx, 0 );
		m_sSelectedPath = m_ctlProcesses.GetItemText( idx, 2 );
	}

	return( -1 != idx );
}

void CPsManagerDlg::OnRefresh() 
{
	CWaitCursor wait;
	
	RefreshList();
}


void CPsManagerDlg::CProcessesList::PreSubclassWindow()
{
	CString sHeader;
	
	
	sHeader.LoadString( IDS_PROCESSES_LIST_NAME );
	int ret = InsertColumn( 0, sHeader, LVCFMT_RIGHT, 100, 0 );
	

	sHeader.LoadString( IDS_PROCESSES_LIST_PID );
	InsertColumn( 1, sHeader, LVCFMT_LEFT, 60, 1 );

	sHeader.LoadString( IDS_PROCESSES_LIST_PATH );
	InsertColumn( 2, sHeader, LVCFMT_LEFT, 350, 2 );
	
}


/////////////////////////////////////////////////////////////////////////////
// CProcessesDlg::CProcessesList
/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CPsManagerDlg::CProcessesList, CListCtrl)
	//{{AFX_MSG_MAP(CProcessesDlg)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, CPsManagerDlg::CProcessesList::OnColumnClick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CPsManagerDlg::CProcessesList::CProcessesList() :
	m_bLastSortAsc( FALSE ), m_nLastSortCol( 0 )
{
}




struct CCompareListStruct
{
	CPsManagerDlg::CProcessesList* m_pList;
	int m_nSortCol;
	BOOL m_bSortAsc;
};

/////////////////////////////////////////////////////////////////////////////

void CPsManagerDlg::CProcessesList::OnColumnClick( NMHDR* pNMHDR, LRESULT* pResult )
{
	CWaitCursor wait;
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*) pNMHDR;

	if( m_nLastSortCol == pNMListView->iSubItem )
	{
		m_bLastSortAsc = !m_bLastSortAsc;
	}
	else
	{
		m_nLastSortCol = pNMListView->iSubItem;
		m_bLastSortAsc = TRUE;
	}

	CCompareListStruct s;
	
	s.m_pList = this;
	s.m_nSortCol = m_nLastSortCol;
	s.m_bSortAsc = m_bLastSortAsc;
		
	SortItems( (PFNLVCOMPARE) CompareEntries, (LPARAM) &s );
	
	*pResult = 0;
}


int CALLBACK CPsManagerDlg::CProcessesList::CompareEntries( LPARAM lp1, LPARAM lp2, LPARAM lData )
{
	CCompareListStruct* ps = (CCompareListStruct*) lData;
	ASSERT( NULL != ps );

	int nResult = 0;

	if( 1 == ps->m_nSortCol )
	{
		nResult = ( lp1 > lp2 ) ? 1 : -1;
	}
	else
	{
		CString s1 = ps->m_pList->GetItemText( ps->m_pList->FindIndex( lp1 ), ps->m_nSortCol );
		CString s2 = ps->m_pList->GetItemText( ps->m_pList->FindIndex( lp2 ), ps->m_nSortCol );
	
		nResult = s1.CompareNoCase( s2 );
	}

	return( ps->m_bSortAsc ? nResult : -nResult );
}

/////////////////////////////////////////////////////////////////////////////

int CPsManagerDlg::CProcessesList::FindIndex( DWORD dw )
{
	for( int idx = 0; idx < GetItemCount(); idx++ )
	{
		if( dw == GetItemData( idx ) )
		{
			return( idx );
		}
	}

	return( -1 );
}




/////////////////////////////////////////////////////////////////////////////
// CPsManagerDlg message handlers

BOOL CPsManagerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	int ret = SetTimer(1,3000,NULL);
	if(ret == 0) AfxMessageBox("定时器申请失败!!请手工刷新进程列表",MB_ICONSTOP);
	m_ctlProcesses.SetBkColor(RGB(200,150,250));
	//m_ctlProcesses.SetTextColor(RGB(255,255,250));
	m_ctlProcesses.SetTextBkColor(RGB(200,150,250));
//	SetWindowPos(wndTopMost,100,100,100,100,SWP_SHOWWINDOW);   
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPsManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPsManagerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{	
		
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPsManagerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

int CPsManagerDlg::CProcessesList::FindPIDIndex( DWORD pid)
{
	
	CString sPID;
	sPID.Format( "%d", pid);

	for(int i=0;i<GetItemCount();i++){
		if(sPID.CompareNoCase(GetItemText(i,1)) == 0) return i;
	}
	return -1;
}
		
void CPsManagerDlg::OnTerminate() 
{
	CConfirmTerminationDlg dlg;

	CopySelectedItem();
	dlg.m_idProcess = 	m_dwSelectedPID;
	if(m_dwSelectedPID == 0) return;
	dlg.m_sProcessPath = GetProcessPath( m_dwSelectedPID );
	
	if(IDYES == dlg.DoModal()){
			TerminateProcessID( dlg.m_idProcess );
			int item = m_ctlProcesses.FindPIDIndex(m_dwSelectedPID);
			if(item >= 0){
				//AfxMessageBox(m_ctlProcesses.GetItemText(item,1));
				m_ctlProcesses.DeleteItem(item);
			}
	}

	RefreshList();
	// TODO: Add your control notification handler code here
	
}




BOOL CPsManagerDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	KillTimer(1);
	
	return CDialog::DestroyWindow();
}

void CPsManagerDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	RefreshList();
	
	CDialog::OnTimer(nIDEvent);
}

void CPsManagerDlg::OnHaisan() 
{
	// TODO: Add your control notification handler code here

	
	HINSTANCE hResults = ShellExecute (NULL,NULL ,"mailto:haisan@iss.net.cn?Subject=\"hello!\"", NULL,NULL,SW_SHOWNORMAL); 
   if ((int) hResults <= 32) AfxMessageBox("fail");

   
}

BOOL CPsManagerDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rcButton1; 
	CPoint ptCursor; 
	CWnd *pStatic1=GetDlgItem(IDC_HAISAN); 

	pStatic1->GetWindowRect (rcButton1); 
	
	GetCursorPos(&ptCursor); 
	if (rcButton1.PtInRect (ptCursor))	{ 
		CWinApp *pApp=AfxGetApp(); 
		HICON hIconBang=pApp->LoadCursor (IDC_CURSOR); 
		SetCursor(hIconBang); 
		return TRUE; 
	} 
	else 
 
  return CDialog::OnSetCursor 
  (pWnd, nHitTest, message); 
	

}

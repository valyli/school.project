// ProfileDemoDlg.cpp : implementation file
//
// 
// Written by Christopher W. Backen - VIZ Group, 1998
//
// ProfileDemo - Simple Dialog Wizaard to Add a service to the default
// Microsoft Exchange Profile, then configure it and delete
// a Microsoft Mail Account and then set all messages to goto the 
// Exchange Mailbox
//
// About MAPI Class
// Simple MAPI Class to help someone Add/Delete messaging profiles,
// configure messaging services, add/delete messaging services,
// configure messaging services, and set default messaging stores.
//
// For Service Names, please consult the MAPISVC.INF file located
// in \winnt\system32
// 
// Tested on Windows NT 4.0 and Visual C++ 6.0

#include "stdafx.h"
#include "ProfileDemo.h"
#include "ProfileDemoDlg.h"
#include "Mapi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProfileDemoDlg dialog

CProfileDemoDlg::CProfileDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProfileDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProfileDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProfileDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProfileDemoDlg)
	DDX_Control(pDX, IDC_PROGRESS1, m_pBar);
	DDX_Control(pDX, IDC_STATIC_INFO, m_Info);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProfileDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CProfileDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProfileDemoDlg message handlers

BOOL CProfileDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	SetTimer((UINT) 0, (UINT) 500, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CProfileDemoDlg::OnPaint() 
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

HCURSOR CProfileDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CProfileDemoDlg::OnStart() 
{
	CMapi	Mapi;
	
	// Look in MAPISVC.INF for Service names (i.e. MSEMS)
	LPSTR	lpszAddService	= "MSEMS",	// Microsoft Exchange Service to Add (in this case Exchange)
			lpszDelService	= "MSFS",	// Microsoft Exchange Service to Delete (in this case MSMAIL)
			lpszServiceName = "Microsoft Exchange Server", // Exchange Service Official Name
			lpszMailbox		= "Christopher Backen", // Person to Configure
			lpszMailStore	= "Mailbox - Christopher Backen", // Message Store to Configure
			lpszServerName	= "CORDALEX1";  // Server to Configure
		
	// Set Progress Bar			
	m_pBar.SetRange(0, 10);
	m_pBar.SetStep(1);

	// Start the session
	m_Info.SetWindowText("Initializing MAPI Dynamic Link Library");
	hr = Mapi.Initialize();
	if (HR_FAILED(hr)){ AfxMessageBox("Failed..."); return;}
	
	hr = Mapi.AdminProfiles();
	if (HR_FAILED(hr)){ AfxMessageBox("Failed..."); return;}
	m_pBar.SetPos(2);

	m_Info.SetWindowText("Logging on to the Default Profile");
	hr = Mapi.LogonDefaultEx();
	if (HR_FAILED(hr)){ AfxMessageBox("Failed..."); return;}

	hr = Mapi.OpenAdminServices();
	if (HR_FAILED(hr)){ AfxMessageBox("Failed..."); return;}
	m_pBar.SetPos(4);

	m_Info.SetWindowText("Creating Microsoft Exchange Messaging Service");
	hr = Mapi.CreateMessagingService(lpszAddService, lpszServiceName);
	if (HR_FAILED(hr)){ AfxMessageBox("Failed..."); return;}
	m_pBar.SetPos(5);

	m_Info.SetWindowText("Configuring Microsoft Exchange Messaging Service");
	hr = Mapi.ConfigureMessagingService(lpszAddService, lpszMailbox, lpszServerName);
	if (HR_FAILED(hr)){  AfxMessageBox("Failed..."); return;}
	m_pBar.SetPos(6);

	m_Info.SetWindowText("Deleting Microsoft Mail Messaging Service");
	hr = Mapi.DeleteMessagingService(lpszDelService);
	if (HR_FAILED(hr)){ AfxMessageBox("Failed..."); return;}

	hr = Mapi.GetMessageStoresTable();
	if (HR_FAILED(hr)){ AfxMessageBox("Failed..."); return;}
	m_pBar.SetPos(8);

	m_Info.SetWindowText("Setting the default mailbox to the server");
	// More complex
	
	hr = Mapi.SetDefaultMessagingStore(lpszMailStore);
	if (HR_FAILED(hr)){ AfxMessageBox("Failed..."); return;}
	m_pBar.SetPos(9);

	Mapi.CloseMapi();
	
	m_pBar.SetPos(10);

	// DONE
	return;

}

void CProfileDemoDlg::OnTimer(UINT nIDEvent) 
{
	KillTimer(0);

	
	((CButton*)GetDlgItem(IDOK))->EnableWindow(FALSE);
	OnStart();
	
	
	((CButton*)GetDlgItem(IDOK))->EnableWindow(TRUE);
	CDialog::OnTimer(nIDEvent);
}

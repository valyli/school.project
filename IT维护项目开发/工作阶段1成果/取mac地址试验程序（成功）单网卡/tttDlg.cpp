// tttDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ttt.h"
#include "tttDlg.h"

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
// CTttDlg dialog

CTttDlg::CTttDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTttDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTttDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTttDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTttDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTttDlg, CDialog)
	//{{AFX_MSG_MAP(CTttDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTttDlg message handlers

BOOL CTttDlg::OnInitDialog()
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTttDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTttDlg::OnPaint() 
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
HCURSOR CTttDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTttDlg::OnButton1() 
{
/*	char resultstr[500];
	int lana_num = 0;
	UCHAR uRetCode;
	memset( &ncb, 0, sizeof(ncb) );
	ncb.ncb_command = NCBRESET;
	ncb.ncb_lana_num = lana_num;
	// 指定网卡号
	// 首先对选定的网卡发送一个NCBRESET 命令，以便进行初始化
	uRetCode = Netbios( &ncb );
	printf( "The NCBRESET return code is: 0x %x \n", uRetCode );
	memset( &ncb, 0, sizeof(ncb) );
	ncb.ncb_command = NCBASTAT;
	ncb.ncb_lana_num = lana_num;// 指定网卡号

	strcpy((char*)ncb.ncb_callname, "*　　　");
	ncb.ncb_buffer = (unsigned char *) &Adapter;
	// 指定返回的信息存放的变量
	ncb.ncb_length = sizeof(Adapter);

	// 接着，可以发送NCBASTAT 命令以获取网卡的信息
	uRetCode = Netbios( &ncb );
	sprintf(resultstr, "The NCBASTAT return code is:0x %x \n", uRetCode );
	if ( uRetCode == 0 )
	{
	//把网卡MAC 地址格式化成常用的16 进制形式，如0010 －A4E4 －5802
	sprintf(resultstr, "The Ethernet Number[ %d] is:%02X %02X －%02X %02X －%02X %02X\n",
			lana_num,
			Adapter.adapt.adapter_address[0],
			Adapter.adapt.adapter_address[1],
			Adapter.adapt.adapter_address[2],
			Adapter.adapt.adapter_address[3],
			Adapter.adapt.adapter_address[4],
			Adapter.adapt.adapter_address[5]);
	::MessageBox(0, resultstr, "", MB_OK);
	}
*/
	char resultstr[500];
	//查看网卡数量
	NCB ncb_lana_enum;
	UCHAR uRetCode;
	LANA_ENUM lana_enum;

	memset(&ncb_lana_enum, 0, sizeof(ncb_lana_enum));
	ncb_lana_enum.ncb_command = NCBENUM;

	ncb_lana_enum.ncb_buffer = (unsigned char *)&lana_enum;
	ncb_lana_enum.ncb_length = sizeof(lana_enum);

	// 向网卡发送NCBENUM 命令，以获取当前机器的网卡信息，如有多少个网卡、每张网卡的编号等
	uRetCode = Netbios(&ncb_lana_enum);
	sprintf(resultstr, "The Number of LANA is:  %d \n", lana_enum.length);
	::MessageBox(0, resultstr, "", MB_OK);


	//逐个查看网卡MAC
	NCB ncb;
	int lana_num;
	for(int i = 0; i < lana_enum.length; i++)
	{
		lana_num = lana_enum.lana[i];
		memset( &ncb, 0, sizeof(ncb) );
		ncb.ncb_command = NCBRESET;
		ncb.ncb_lana_num = lana_num;
		// 指定网卡号
		// 首先对选定的网卡发送一个NCBRESET 命令，以便进行初始化
		uRetCode = Netbios( &ncb );
//		printf( "The NCBRESET return code is: 0x %x \n", uRetCode );
		memset( &ncb, 0, sizeof(ncb) );
		ncb.ncb_command = NCBASTAT;
		ncb.ncb_lana_num = lana_num;// 指定网卡号

		strcpy((char*)ncb.ncb_callname, "*　　　");
		ncb.ncb_buffer = (unsigned char *) &Adapter;
		// 指定返回的信息存放的变量
		ncb.ncb_length = sizeof(Adapter);

		// 接着，可以发送NCBASTAT 命令以获取网卡的信息
		uRetCode = Netbios( &ncb );
//		sprintf(resultstr, "The NCBASTAT return code is:0x %x \n", uRetCode );
		if ( uRetCode == 0 )
		{
			//把网卡MAC 地址格式化成常用的16 进制形式，如0010 －A4E4 －5802
			sprintf(resultstr, "The Ethernet Number[ %d] is:%02X%02X－%02X%02X－%02X%02X\n",
					lana_num,
					Adapter.adapt.adapter_address[0],
					Adapter.adapt.adapter_address[1],
					Adapter.adapt.adapter_address[2],
					Adapter.adapt.adapter_address[3],
					Adapter.adapt.adapter_address[4],
					Adapter.adapt.adapter_address[5]);
			::MessageBox(0, resultstr, "", MB_OK);
		}
	}
}

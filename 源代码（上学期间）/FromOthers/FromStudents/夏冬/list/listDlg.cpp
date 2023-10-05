// listDlg.cpp : implementation file
//

#include "stdafx.h"
#include "list.h"
#include "listDlg.h"

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
	CString	m_mem;
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
	m_mem = _T("");
	//}}AFX_DATA_INIT
	MEMORYSTATUS mem;
	::GlobalMemoryStatus(&mem);
	m_mem.Format("%s %d%s","windows的物理内存信息：",mem.dwTotalPhys/(1024*1024),"MB");
	
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_mem, m_mem);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListDlg dialog

CListDlg::CListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CListDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CListDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListDlg)
	DDX_Control(pDX, IDC_LIST2, m_list);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CListDlg, CDialog)
	//{{AFX_MSG_MAP(CListDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListDlg message handlers

BOOL CListDlg::OnInitDialog()
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
	LV_COLUMN col;
	col.mask=LVCF_FMT|LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH;
	col.fmt=LVCFMT_LEFT;
	col.cx=142;
	col.iSubItem=0;
	col.pszText="Parameters";
	m_list.InsertColumn(0,&col);
    col.iSubItem=1;
	col.pszText="Value";
	m_list.InsertColumn(1,&col);
    col.iSubItem=2;
	col.pszText="Description";
	m_list.InsertColumn(2,&col);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CListDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CListDlg::OnPaint() 
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
HCURSOR CListDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CListDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	m_list.DeleteAllItems();
	CString str;
	CString de;
	int i;
	CClientDC play(this);
    m_list.SetTextBkColor(RGB(0,0,0));
	m_list.SetTextColor(RGB(0,255,0));
    //
	int l=play.GetDeviceCaps(CLIPCAPS);
	switch(l)
	{
	case 0:
		str.Format("CP_NONE");de.Format("输出被剪贴");break;
	case 1:
        str.Format("CP_RECTANGLE");de.Format("输出被剪贴到矩形");break;
    case 2:
        str.Format("CP_REGION");de.Format("输出被剪贴到区域");break;
	}
	i=m_list.InsertItem(0,"CLIPCAPS");
	m_list.SetItemText(i,1,str);
	m_list.SetItemText(i,2,de);
	//
	int h=play.GetDeviceCaps(HORZRES);
	str.Format("%d",h);
	i=m_list.InsertItem(0,"HORZRES");
	m_list.SetItemText(i,1,str);
	m_list.SetItemText(i,2,"以象素为单位的显示宽度");
	//
	int v=play.GetDeviceCaps(VERTRES);
	str.Format("%d",v);
	i=m_list.InsertItem(0,"VERTRES");
	m_list.SetItemText(i,1,str);
	m_list.SetItemText(i,2,"以象素为单位的显示高度");
	//
	int x=play.GetDeviceCaps(ASPECTX);
	str.Format("%d",x);
	i=m_list.InsertItem(0,"ASPECTX");
	m_list.SetItemText(i,1,str);
	m_list.SetItemText(i,2,"以象素为单位的宽度");
	//
	int y=play.GetDeviceCaps(ASPECTY);
	str.Format("%d",y);
	i=m_list.InsertItem(0,"ASPECTY");
	m_list.SetItemText(i,1,str);
	m_list.SetItemText(i,2,"以象素为单位的高度");
	//
	int c=play.GetDeviceCaps(NUMCOLORS);
	str.Format("%d",c);
	i=m_list.InsertItem(0,"NUMCOLORS");
	m_list.SetItemText(i,1,str);
	m_list.SetItemText(i,2,"设备颜色表的入口数目");

}

void CListDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	m_list.DeleteAllItems();
	CPrintDialog dlg(FALSE);
    dlg.GetDefaults();
	CString str;
	CString de;
	int i;
	CDC play;
	HDC hdcPrinter = dlg.GetPrinterDC();
	play.Attach(hdcPrinter);
    
    m_list.SetTextBkColor(RGB(0,0,255));
	m_list.SetTextColor(RGB(255,0,0));
    //
	int l=play.GetDeviceCaps(CLIPCAPS);
	switch(l)
	{
	case 0:
		str.Format("CP_NONE");de.Format("输出被剪贴");break;
	case 1:
        str.Format("CP_RECTANGLE");de.Format("输出被剪贴到矩形");break;
    case 2:
        str.Format("CP_REGION");de.Format("输出被剪贴到区域");break;
	}
	i=m_list.InsertItem(0,"CLIPCAPS");
	m_list.SetItemText(i,1,str);
	m_list.SetItemText(i,2,de);
	//
	int h=play.GetDeviceCaps(HORZRES);
	str.Format("%d",h);
	i=m_list.InsertItem(0,"HORZRES");
	m_list.SetItemText(i,1,str);
	m_list.SetItemText(i,2,"以象素为单位的显示宽度");
	//
	int v=play.GetDeviceCaps(VERTRES);
	str.Format("%d",v);
	i=m_list.InsertItem(0,"VERTRES");
	m_list.SetItemText(i,1,str);
	m_list.SetItemText(i,2,"以象素为单位的显示高度");
	//
	int x=play.GetDeviceCaps(ASPECTX);
	str.Format("%d",x);
	i=m_list.InsertItem(0,"ASPECTX");
	m_list.SetItemText(i,1,str);
	m_list.SetItemText(i,2,"以象素为单位的宽度");
	//
	int y=play.GetDeviceCaps(ASPECTY);
	str.Format("%d",y);
	i=m_list.InsertItem(0,"ASPECTY");
	m_list.SetItemText(i,1,str);
	m_list.SetItemText(i,2,"以象素为单位的高度");
	//
	int c=play.GetDeviceCaps(NUMCOLORS);
	str.Format("%d",c);
	i=m_list.InsertItem(0,"NUMCOLORS");
	m_list.SetItemText(i,1,str);
	m_list.SetItemText(i,2,"设备颜色表的入口数目");

}

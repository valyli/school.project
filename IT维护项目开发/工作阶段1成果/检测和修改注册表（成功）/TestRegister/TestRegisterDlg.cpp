// TestRegisterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestRegister.h"
#include "TestRegisterDlg.h"

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
// CTestRegisterDlg dialog

CTestRegisterDlg::CTestRegisterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestRegisterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestRegisterDlg)
	str_owner = _T("");
	str_company = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestRegisterDlg)
	DDX_Text(pDX, IDC_EDIT_OWNER, str_owner);
	DDX_Text(pDX, IDC_EDIT_ORG, str_company);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestRegisterDlg, CDialog)
	//{{AFX_MSG_MAP(CTestRegisterDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CHECK, OnButtonCheck)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestRegisterDlg message handlers

BOOL CTestRegisterDlg::OnInitDialog()
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

void CTestRegisterDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestRegisterDlg::OnPaint() 
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
HCURSOR CTestRegisterDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestRegisterDlg::OnButtonCheck() 
{
	HKEY hKEY;//定义有关的 hKEY, 在查询结束时要关闭。
	LPCTSTR data_Set;

	DWORD winVer;
	winVer=::GetVersion();
	if(winVer<0x80000000)/*NT */
	{
		data_Set="Software\\Microsoft\\Windows NT\\CurrentVersion\\";
	}
	else
	{
		data_Set="Software\\Microsoft\\Windows\\CurrentVersion\\";
	}

	//打开与路径 data_Set 相关的 hKEY，第一个参数为根键名称，第二个参数表。 
	//表示要访问的键的位置，第三个参数必须为0，KEY_READ表示以查询的方式.
	//访问注册表，hKEY则保存此函数所打开的键的句柄。 
	long ret0=(::RegOpenKeyEx(HKEY_LOCAL_MACHINE,data_Set, 0, KEY_READ, &hKEY)); 
	if(ret0!=ERROR_SUCCESS) //如果无法打开hKEY，则终止程序的执行
	{
		MessageBox("错误: 无法打开有关的hKEY!"); 
		return;
	} 
	//查询有关的数据 (用户姓名 owner_Get)。 
	LPBYTE owner_Get=new BYTE[80];
	DWORD type_1=REG_SZ ; DWORD cbData_1=80;
	//hKEY为刚才RegOpenKeyEx()函数所打开的键的句柄，"RegisteredOwner"。 
	//表示要查 询的键值名，type_1表示查询数据的类型，owner_Get保存所。 
	//查询的数据，cbData_1表示预设置的数据长度。 
	long ret1=::RegQueryValueEx(hKEY, "RegisteredOwner", NULL, &type_1, owner_Get, &cbData_1); 
	if(ret1!=ERROR_SUCCESS) 
	{ 
		MessageBox("错误: 无法查询有关注册表信息!"); 
		return; 
	} 
	// 查询有关的数据 (公司名 company_Get)
	LPBYTE company_Get=new BYTE [80];
	DWORD type_2=REG_SZ; DWORD cbData_2=80;
	long ret2=::RegQueryValueEx(hKEY, "RegisteredOrganization", NULL,&type_2,company_Get, &cbData_2);
	if(ret2!=ERROR_SUCCESS)
	{
		MessageBox("错误: 无法查询有关注册表信息!");
		return;
	}
	// 将 owner_Get 和 company_Get 转换为 CString 字符串, 以便显示输出.
	CString str_owner=CString(owner_Get);
	CString str_company=CString(company_Get);

	delete[] owner_Get; delete[] company_Get;
	// 程序结束前要关闭已经打开的 hKEY。 
	::RegCloseKey(hKEY);

	::MessageBox(0, str_owner, "RegisteredOwner", MB_OK);
	::MessageBox(0, str_company, "RegisteredOrganization", MB_OK);

}

//将取得CString类型的有关字符串。要先将其转换为LPBYTE(即unsigned char＊)型的数据类型
LPBYTE CString_To_LPBYTE(CString str) 
{ 
	LPBYTE lpb = new BYTE[str.GetLength()+1];  
	for(int i=0; (i<str.GetLength())&&(*(lpb+i) = str.GetAt(i));i++);
	return lpb;
} 

void CTestRegisterDlg::OnButtonSet() 
{
	UpdateData(TRUE);
	//定义有关的 hKEY, 在程序的最后要关闭。
	HKEY hKEY;
	LPCTSTR data_Set;

	DWORD winVer;
	winVer=::GetVersion();
	if(winVer<0x80000000)/*NT */
	{
		data_Set="Software\\Microsoft\\Windows NT\\CurrentVersion\\";
	}
	else
	{
		data_Set="Software\\Microsoft\\Windows\\CurrentVersion\\";
	}

	//打开与路径 data_Set 相关的hKEY，KEY_WRITE表示以写的方式打开。
	long ret0=(::RegOpenKeyEx(HKEY_LOCAL_MACHINE, data_Set, 0, KEY_WRITE, &hKEY));
	if(ret0!=ERROR_SUCCESS)
	{
		MessageBox("错误: 无法打开有关的hKEY!");
		return;
	}
	//修改有关数据(用户姓名 owner_Set)，要先将CString型转换为LPBYTE
	LPBYTE owner_Set=CString_To_LPBYTE(str_owner);
	for(int i=0; (i<str_owner.GetLength())&&(*(owner_Set+i) = str_owner.GetAt(i));i++);

	DWORD type_1=REG_SZ;
	DWORD cbData_1=str_owner.GetLength()+1;
	//与RegQureyValueEx()类似，hKEY表示已打开的键的句柄，"RegisteredOwner"
	//表示要访问的键值名，owner_Set表示新的键值，type_1和cbData_1表示新值.
	//的数据类型和数据长度
	long ret1=::RegSetValueEx(hKEY, "RegisteredOwner", NULL, type_1, owner_Set, cbData_1);
	if(ret1!=ERROR_SUCCESS)
	{
		MessageBox("错误: 无法修改有关注册表信息!");
		return;
	}
	//修改有关的数据 (公司名 company_Set)
	LPBYTE company_Set=CString_To_LPBYTE(str_company);
	DWORD type_2=REG_SZ;
	DWORD cbData_2=str_company.GetLength()+1;
	long ret2=::RegSetValueEx(hKEY, "RegisteredOrganization", NULL,	type_2, company_Set, cbData_2);
	if(ret2!=ERROR_SUCCESS)
	{
		MessageBox("错误: 无法修改有关注册表信息!");
		return;
	}
	::RegCloseKey(hKEY);
}
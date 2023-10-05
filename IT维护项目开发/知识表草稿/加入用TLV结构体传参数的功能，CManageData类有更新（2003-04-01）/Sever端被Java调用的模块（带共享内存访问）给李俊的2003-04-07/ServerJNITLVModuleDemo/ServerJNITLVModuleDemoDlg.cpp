// ServerJNITLVModuleDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ServerJNITLVModuleDemo.h"
#include "ServerJNITLVModuleDemoDlg.h"

#include "Base.h"

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
// CServerJNITLVModuleDemoDlg dialog

CServerJNITLVModuleDemoDlg::CServerJNITLVModuleDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServerJNITLVModuleDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CServerJNITLVModuleDemoDlg)
	m_TLV = _T("");
	m_Test = _T("");
	m_Time = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	hLibrary = NULL;
}

void CServerJNITLVModuleDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServerJNITLVModuleDemoDlg)
	DDX_Text(pDX, IDC_EDIT_TLV, m_TLV);
	DDX_Text(pDX, IDC_EDIT_TLV2, m_Test);
	DDX_Text(pDX, IDC_EDIT_TIME, m_Time);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CServerJNITLVModuleDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CServerJNITLVModuleDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SET_TLV, OnButtonSetTlv)
	ON_BN_CLICKED(IDC_BUTTON_GET_NEW_DATA_FROM_MEMORY_TO_DLL, OnButtonGetNewDataFromMemoryToDll)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON_SET_TLV2, OnButtonSetTlv2)
	ON_BN_CLICKED(IDC_BUTTON_GET_NEW_DATA_FROM_MEMORY_TO_DLL2, OnButtonGetNewDataFromMemoryToDll2)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerJNITLVModuleDemoDlg message handlers

BOOL CServerJNITLVModuleDemoDlg::OnInitDialog()
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
	SetTimer(1, 5000, 0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CServerJNITLVModuleDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CServerJNITLVModuleDemoDlg::OnPaint() 
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
HCURSOR CServerJNITLVModuleDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}





//向CServerJNITLVModule的dll和共享数据区中设置TLV结构数据
void CServerJNITLVModuleDemoDlg::OnButtonSetTlv() 
{
	if(hLibrary == NULL)
	{
		::MessageBox(0, "Please Load Library first", "", MB_OK);
		return;
	}
    //获取函数句柄
    bool (FAR *lpfn)(Transfer_C2S_Struct TLVData);
	lpfn = (bool (__cdecl *)(struct Transfer_C2S_Struct))GetProcAddress(hLibrary, "SetTransfer_C2S_StructC2S");
	if(lpfn == NULL)
	{
		AlarmErrorMessage("Get Function SetTransfer_C2S_StructC2S() Failed", "Load Library Error");
		FreeLibrary(hLibrary);
		return;
	}

    //设置数据
    Transfer_C2S_Struct Data;
    Data.Value.Type = CString_Value;
    Data.Value.Length = 255;
	UpdateData(TRUE);
    strcpy(Data.Value.Value.Value_char, this->m_TLV);

    //调用函数
	bool flag = (*lpfn)(Data);
	if(flag)
	{
		::MessageBox(0, "SetTransfer_C2S_StructC2S() Success", "CServerJNITLVModuleDemoDlg", MB_OK);
		this->m_TLV = "";
		UpdateData(FALSE);
	}
}



//从共享数据区中获得TLV结构数据，并送入CServerJNITLVModule的dll中
//在编辑框中回显
void CServerJNITLVModuleDemoDlg::OnButtonGetNewDataFromMemoryToDll() 
{
	if(hLibrary == NULL)
	{
		::MessageBox(0, "Please Load Library first", "", MB_OK);
		return;
	}
    //获取函数句柄
    bool (FAR *lpfn)(Transfer_C2S_Struct& TLVData);
	lpfn = (bool (__cdecl *)(struct Transfer_C2S_Struct&))GetProcAddress(hLibrary, "GetTransfer_C2S_StructC2S");
	if(lpfn == NULL)
	{
		AlarmErrorMessage("Get Function GetTransfer_C2S_StructC2S() Failed", "Load Library Error");
		FreeLibrary(hLibrary);
		return;
	}

    //设置数据
    Transfer_C2S_Struct Data;
    Data.Value.Type = CString_Value;
    Data.Value.Length = 255;

    //调用函数
	bool flag = (*lpfn)(Data);
	if(flag)
	{
		if(Data.Value.Type == CString_Value)
		{
			this->m_TLV = Data.Value.Value.Value_char;
			UpdateData(FALSE);
		}
		::MessageBox(0, "GetTransfer_C2S_StructC2S() Success", "CServerJNITLVModuleDemoDlg", MB_OK);
	}
}

//导入ServerJNITLVModule.dll
void CServerJNITLVModuleDemoDlg::OnButton2() 
{
	CString strDllFilePath = "ServerJNITLVModule.dll";
	hLibrary=LoadLibrary(strDllFilePath);
	CString temp;
	if(hLibrary == NULL)
	{
		temp = "Load ";
		temp += strDllFilePath;
		temp += "Failed";
		AlarmErrorMessage(temp, "Load Library Error");
		FreeLibrary(hLibrary);
        return; 
	}
}


//创建内存中的共享数据区C2S
void CServerJNITLVModuleDemoDlg::OnButton1() 
{
	if(hLibrary == NULL)
	{
		::MessageBox(0, "Please Load Library first", "", MB_OK);
		return;
	}
    //获取函数句柄
    bool (FAR *lpfn)();
	lpfn = (bool (__cdecl *)())GetProcAddress(hLibrary, "CreateFileMappingC2S");
	if(lpfn == NULL)
	{
		AlarmErrorMessage("Get Function CreateFileMappingC2S() Failed", "Load Library Error");
		FreeLibrary(hLibrary);
		return;
	}

    //调用函数
	bool flag = (*lpfn)();
	if(flag)
	{
		::MessageBox(0, "CreateFileMappingC2S() Success", "CServerJNITLVModuleDemoDlg", MB_OK);
	}
}

void CServerJNITLVModuleDemoDlg::OnButton3() 
{
	if(hLibrary == NULL)
	{
		::MessageBox(0, "You don't Load Library", "", MB_OK);
		return;
	}
	FreeLibrary(hLibrary);
	hLibrary = NULL;
}


//创建内存中的共享数据区S2C
void CServerJNITLVModuleDemoDlg::OnButton4() 
{
	if(hLibrary == NULL)
	{
		::MessageBox(0, "Please Load Library first", "", MB_OK);
		return;
	}
    //获取函数句柄
    bool (FAR *lpfn)();
	lpfn = (bool (__cdecl *)())GetProcAddress(hLibrary, "CreateFileMappingS2C");
	if(lpfn == NULL)
	{
		AlarmErrorMessage("Get Function CreateFileMappingS2C() Failed", "Load Library Error");
		FreeLibrary(hLibrary);
		return;
	}

    //调用函数
	bool flag = (*lpfn)();
	if(flag)
	{
		::MessageBox(0, "CreateFileMappingS2C() Success", "CServerJNITLVModuleDemoDlg", MB_OK);
	}
}

void CServerJNITLVModuleDemoDlg::OnButtonSetTlv2() 
{
	if(hLibrary == NULL)
	{
		::MessageBox(0, "Please Load Library first", "", MB_OK);
		return;
	}
    //获取函数句柄
    bool (FAR *lpfn)(Transfer_S2C_Struct TLVData);
	lpfn = (bool (__cdecl *)(struct Transfer_S2C_Struct))GetProcAddress(hLibrary, "SetTransfer_S2C_StructS2C");
	if(lpfn == NULL)
	{
		AlarmErrorMessage("Get Function SetTransfer_S2C_StructS2C() Failed", "Load Library Error");
		FreeLibrary(hLibrary);
		return;
	}

    //设置数据
    Transfer_S2C_Struct Data;
    Data.Value.Type = CString_Value;
    Data.Value.Length = 255;
	UpdateData(TRUE);
    strcpy(Data.Value.Value.Value_char, this->m_Test);

    //调用函数
	bool flag = (*lpfn)(Data);
	if(flag)
	{
		::MessageBox(0, "SetTransfer_S2C_StructC2S() Success", "CServerJNITLVModuleDemoDlg", MB_OK);
		this->m_Test = "";
		UpdateData(FALSE);
	}
}

void CServerJNITLVModuleDemoDlg::OnButtonGetNewDataFromMemoryToDll2() 
{
	if(hLibrary == NULL)
	{
		::MessageBox(0, "Please Load Library first", "", MB_OK);
		return;
	}
    //获取函数句柄
    bool (FAR *lpfn)(Transfer_S2C_Struct& TLVData);
	lpfn = (bool (__cdecl *)(struct Transfer_S2C_Struct&))GetProcAddress(hLibrary, "GetTransfer_S2C_StructS2C");
	if(lpfn == NULL)
	{
		AlarmErrorMessage("Get Function GetTransfer_S2C_StructS2C() Failed", "Load Library Error");
		FreeLibrary(hLibrary);
		return;
	}

    //设置数据
    Transfer_S2C_Struct Data;
    Data.Value.Type = CString_Value;
    Data.Value.Length = 255;

    //调用函数
	bool flag = (*lpfn)(Data);
	if(flag)
	{
		if(Data.Value.Type == CString_Value)
		{
			this->m_Test = Data.Value.Value.Value_char;
			UpdateData(FALSE);
		}
		::MessageBox(0, "GetTransfer_S2C_StructS2C() Success", "CServerJNITLVModuleDemoDlg", MB_OK);
	}
}

void CServerJNITLVModuleDemoDlg::OnTimer(UINT nIDEvent) 
{
	COleDateTime time;
	time = time.GetCurrentTime();
	this->m_Time = time.Format("%Y-%m-%d %H:%M:%S");
	UpdateData(FALSE);

	CDialog::OnTimer(nIDEvent);
}

void CServerJNITLVModuleDemoDlg::OnOK() 
{
	KillTimer(1);
	CDialog::OnOK();
}

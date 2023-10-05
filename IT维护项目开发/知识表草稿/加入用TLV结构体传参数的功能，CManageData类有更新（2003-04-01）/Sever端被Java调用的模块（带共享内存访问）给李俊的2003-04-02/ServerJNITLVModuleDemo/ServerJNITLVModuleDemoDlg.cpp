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
    bool (FAR *lpfn)(TLVStruct TLVData);
	lpfn = (bool (__cdecl *)(struct TLVStruct))GetProcAddress(hLibrary, "SetTLV");
	if(lpfn == NULL)
	{
		AlarmErrorMessage("Get Function SetTLV() Failed", "Load Library Error");
		FreeLibrary(hLibrary);
		return;
	}

    //设置数据
    TLVStruct TLVData;
    TLVData.Type = CString_Value;
    TLVData.Length = 255;
	UpdateData(TRUE);
    strcpy(TLVData.Value.Value_Char, this->m_TLV);

    //调用函数
	bool flag = (*lpfn)(TLVData);
	if(flag)
	{
		::MessageBox(0, "SetTLV() Success", "CServerJNITLVModuleDemoDlg", MB_OK);
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
    bool (FAR *lpfn)(TLVStruct& TLVData);
	lpfn = (bool (__cdecl *)(struct TLVStruct&))GetProcAddress(hLibrary, "GetTLV");
	if(lpfn == NULL)
	{
		AlarmErrorMessage("Get Function SetTLV() Failed", "Load Library Error");
		FreeLibrary(hLibrary);
		return;
	}

    //设置数据
    TLVStruct TLVData;
    TLVData.Type = CString_Value;
    TLVData.Length = 255;

    //调用函数
	bool flag = (*lpfn)(TLVData);
	if(flag)
	{
		if(TLVData.Type == CString_Value)
		{
			this->m_TLV = TLVData.Value.Value_Char;
			UpdateData(FALSE);
		}
		::MessageBox(0, "GetTLV() Success", "CServerJNITLVModuleDemoDlg", MB_OK);
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


//创建内存中的共享数据区
void CServerJNITLVModuleDemoDlg::OnButton1() 
{
	if(hLibrary == NULL)
	{
		::MessageBox(0, "Please Load Library first", "", MB_OK);
		return;
	}
    //获取函数句柄
    bool (FAR *lpfn)();
	lpfn = (bool (__cdecl *)())GetProcAddress(hLibrary, "CreateFileMapping_Server");
	if(lpfn == NULL)
	{
		AlarmErrorMessage("Get Function CreateFileMapping_Server() Failed", "Load Library Error");
		FreeLibrary(hLibrary);
		return;
	}

    //调用函数
	bool flag = (*lpfn)();
	if(flag)
	{
		::MessageBox(0, "CreateFileMapping_Server() Success", "CServerJNITLVModuleDemoDlg", MB_OK);
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

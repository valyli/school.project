// TestCycleTransferModuleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestCycleTransferModule.h"
#include "TestCycleTransferModuleDlg.h"


/////////////////////////////////////////////////////////////////////////////
#include "ManageData.h"
/////////////////////////////////////////////////////////////////////////////


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
// CTestCycleTransferModuleDlg dialog

CTestCycleTransferModuleDlg::CTestCycleTransferModuleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestCycleTransferModuleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestCycleTransferModuleDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestCycleTransferModuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestCycleTransferModuleDlg)
	DDX_Control(pDX, IDC_LIST_RESULT, m_List);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestCycleTransferModuleDlg, CDialog)
	//{{AFX_MSG_MAP(CTestCycleTransferModuleDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CYCLETRANSFERMODULE, OnButtonCycletransfermodule)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestCycleTransferModuleDlg message handlers

BOOL CTestCycleTransferModuleDlg::OnInitDialog()
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

void CTestCycleTransferModuleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestCycleTransferModuleDlg::OnPaint() 
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
HCURSOR CTestCycleTransferModuleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}




void CTestCycleTransferModuleDlg::OnButtonCycletransfermodule() 
{
	//导入调用主模块
	CString strDllFilePath = "CClientModuleTransfer.dll";
	hLibrary=LoadLibrary(strDllFilePath);
	CString temp;
	if(hLibrary == NULL)
	{
		temp = "Load ";
		temp += strDllFilePath;
		temp += "Failed";
		return;
	}

	//获取当前目录下的所有合法动态库操作信息
	//调用ClientGetAllModuleInfoToMemory()
	bool (FAR *lpfn_1)();
	lpfn_1 = (bool (__cdecl *)())GetProcAddress(hLibrary, "ClientGetAllModuleInfoToMemory");
	if(lpfn_1 == NULL)
	{
		AlarmErrorMessage("Get Function ClientGetAllModuleInfoToMemory() Failed", "Load Library Error");
		return;
	}
	bool flag = (*lpfn_1)();
	if(flag)
		::MessageBox(0, "ClientGetAllModuleInfoToMemory() Success", "CClientTransferModuleDemoDlg", MB_OK);

	//导入获取CPU信息的动态库
	ModuleInfomationListStruct ModuleInfo;
	//设置获取CPU使用率信息的信息项值
	ModuleInfo.InfomationElementTableID = 4;
	ModuleInfo.InfomationElementID = 1;

	//调用LoadClientTransferModuleAndFounctionHandleByCManageData()
	bool (FAR *lpfn_2)(ModuleInfomationListStruct &ModuleInfo);
	lpfn_2 = (bool (__cdecl *)(struct ModuleInfomationListStruct&))GetProcAddress(hLibrary, "LoadClientTransferModuleAndFounctionHandleByCManageData");
	if(lpfn_2 == NULL)
	{
		AlarmErrorMessage("Get Function LoadClientTransferModuleAndFounctionHandleByCManageData() Failed", "Load Library Error");
		return;
	}
	flag = (*lpfn_2)(ModuleInfo);
	if(flag)
		::MessageBox(0, "LoadClientTransferModuleAndFounctionHandleByCManageData() Success", "", MB_OK);


	//暂存要调用的动态库和调用函数的句柄
	HMODULE hModule;
	bool (FAR *lpfnR)(CManageData &Data);

	
	//获取hModule和lpfnR
	void (FAR *lpfn_3)(HMODULE& hLibrary, bool (FAR*& lpfounction)(CManageData &Data));
	lpfn_3 = (void (__cdecl *)(HMODULE& , bool (FAR*& )(CManageData &Data)))GetProcAddress(hLibrary, "GetModuleHandleAndFunctionAddress");
	if(lpfn_3 == NULL)
	{
		AlarmErrorMessage("Get Function GetModuleHandleAndFunctionAddress() Failed", "Load Library Error");
		return;
	}
	(*lpfn_3)(hModule, lpfnR);


	//调用获取CPU信息的模块
	bool (FAR *lpfn_4)(ModuleInfomationListStruct &ModuleInfo, CManageData& Data);
	lpfn_4 = (bool (__cdecl *)(struct ModuleInfomationListStruct&, class CManageData&))GetProcAddress(hLibrary, "CallClientTransferModuleByCManageData");
	if(lpfn_4 == NULL)
	{
		AlarmErrorMessage("Get Function CallClientTransferModuleByCManageData() Failed", " Error");
		return;
	}
	else
	{
		CManageData Data;
		TLVStruct TLVData;
		//调用10次
		for(int i = 0; i < 10; i++)
		{
			flag = (*lpfn_4)(ModuleInfo, Data);
			Data.GetDatabyTLV(TLVData);
			if(!flag)
				::MessageBox(0, "CallClientTransferModuleByCManageData() Failed", "", MB_OK);


			char buff[100];
			this->m_List.AddString(itoa(TLVData.Value.Value_long, buff, 10));
//			::MessageBox(0, itoa(TLVData.Value.Value_long, buff, 10), "Result", MB_OK);

		}
	}


	//调用FreeClientTransferModule()
	void (FAR *lpfn_5)(HMODULE hModule);
	lpfn_5 = (void (__cdecl *)(HMODULE))GetProcAddress(hLibrary, "FreeClientTransferModule");
	if(lpfn_5 == NULL)
	{
		AlarmErrorMessage("Get Function FreeClientTransferModule() Failed", "Load Library Error");
		return;
	}
	(*lpfn_5)(hModule);
}

void CTestCycleTransferModuleDlg::OnTimer(UINT nIDEvent) 
{
	CDialog::OnTimer(nIDEvent);
}

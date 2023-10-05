// RunTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RunTest.h"
#include "RunTestDlg.h"
#include "Winbase.h"

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
// CRunTestDlg dialog

CRunTestDlg::CRunTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRunTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRunTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRunTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRunTestDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRunTestDlg, CDialog)
	//{{AFX_MSG_MAP(CRunTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CHECKSYSTEMVERSION, OnButtonChecksystemversion)
	ON_BN_CLICKED(IDC_BUTTON_CHECKDLLVERSION, OnButtonCheckdllversion)
	ON_BN_CLICKED(IDC_BUTTON_CHECK_BIOS, OnButtonCheckBios)
	ON_BN_CLICKED(IDC_BUTTON_CHECK_HARDDISK, OnButtonCheckHarddisk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRunTestDlg message handlers

BOOL CRunTestDlg::OnInitDialog()
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

void CRunTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRunTestDlg::OnPaint() 
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
HCURSOR CRunTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


//检测windows版本信息
void CRunTestDlg::OnButtonChecksystemversion() 
{
	Win32SysType (FAR *lpfn)(CString& strWin32SysType);

	HMODULE hLibrary=LoadLibrary("DetectVersion.dll");
	if(hLibrary == NULL)
	{
		::MessageBox(0, "'DetectVersion.dll' Loading failed", "", MB_OK);
		return;
	}
	lpfn = (enum tagWin32SysType (__cdecl *)(class CString &))GetProcAddress(hLibrary, "DetectWindowsVersion_DetectWindowsVersionModule");
	if(lpfn == NULL)
	{
		FreeLibrary(hLibrary);
		::MessageBox(0, "Get Function 'DetectWindowsVersion_DetectWindowsVersionModule()' failed", "", MB_OK);
		return;
	}

	Win32SysType m_Win32SysType;
	CString strWin32SysType;
	
	m_Win32SysType = (*lpfn)(strWin32SysType);

	FreeLibrary(hLibrary);

	::MessageBox(0, strWin32SysType, "", MB_OK);
	return;
}

//检测动态库版本信息
void CRunTestDlg::OnButtonCheckdllversion() 
{
	VS_FIXEDFILEINFO (FAR *lpfn)(CString& strDLLFilePath);

	HMODULE hLibrary=LoadLibrary("DetectVersion.dll");
	if(hLibrary == NULL)
	{
		::MessageBox(0, "'DetectVersion.dll' Loading failed", "", MB_OK);
		return;
	}
	lpfn = (VS_FIXEDFILEINFO (__cdecl *)(class CString &))GetProcAddress(hLibrary, "DetectDLLVersion_DetectWindowsVersionModule");
	if(lpfn == NULL)
	{
		FreeLibrary(hLibrary);
		::MessageBox(0, "Get Function 'DetectDLLVersion_DetectWindowsVersionModule()' failed", "", MB_OK);
		return;
	}

	VS_FIXEDFILEINFO m_WinDllFixdfileinfo;
	CString strDLLFilePath;
	
	//打开dll文件
	static char BASED_CODE szFilter[] = "Chart Files (*.xlc)|*.xlc|Worksheet Files (*.xls)|*.xls|Data Files (*.xlc;*.xls)|*.xlc"; 
	CFileDialog m_CFileDialog(TRUE, NULL, NULL, OFN_READONLY);
	if(m_CFileDialog.DoModal() == IDOK)
	{
		strDLLFilePath = m_CFileDialog.GetPathName();

		m_WinDllFixdfileinfo = (*lpfn)(strDLLFilePath);

		CString strResult;
		char buff[100];

		//拆分出windows显示版本信息的默认格式
		//用于移位的临时变量
		DWORD temp;
		
		//第一段
		temp = m_WinDllFixdfileinfo.dwFileVersionMS;
		temp = temp & 0xffff0000;
		temp = temp >> 16;
		strResult = itoa(temp, buff, 10);
		strResult += ".";

		//第二段
		temp = m_WinDllFixdfileinfo.dwFileVersionMS;
		temp = temp & 0x0000ffff;
		strResult += itoa(temp, buff, 10);
		strResult += ".";
		
		//第三段
		temp = m_WinDllFixdfileinfo.dwFileVersionLS;
		temp = temp & 0xffff0000;
		temp = temp >> 16;
		strResult += itoa(temp, buff, 10);
		strResult += ".";
		
		//第四段
		temp = m_WinDllFixdfileinfo.dwProductVersionLS;
		temp = temp & 0x0000ffff;
		strResult += itoa(temp, buff, 10);
		::MessageBox(0, strResult, strDLLFilePath, MB_OK);
	}

	FreeLibrary(hLibrary);

	return;
}


//检测BIOS信息
void CRunTestDlg::OnButtonCheckBios() 
{
	BOOL (FAR *lpfn)(CString &BIOS_ID, CString &BIOS_Type, CString &BIOS_Date);

	HMODULE hLibrary=LoadLibrary("DetectHardware.dll");
	if(hLibrary == NULL)
	{
		::MessageBox(0, "'DetectHardware.dll' Loading failed", "", MB_OK);
		return;
	}
	lpfn = (int (__cdecl *)(class CString &,class CString &,class CString &))GetProcAddress(hLibrary, "DetectBIOS_DetectHardwareModule");
	if(lpfn == NULL)
	{
		FreeLibrary(hLibrary);
		::MessageBox(0, "Get Function 'DetectBIOS_DetectHardwareModule()' failed", "", MB_OK);
		return;
	}

	CString BIOS_ID, BIOS_Type, BIOS_Date;
	CString strResult;

	BOOL flag = (*lpfn)(BIOS_ID, BIOS_Type, BIOS_Date);
	FreeLibrary(hLibrary);
	if(!flag)
		::MessageBox(0, "Check BIOS Infomation Failed.", "Error", MB_OK);
	else
	{
		strResult = "BIOS_ID: ";
		strResult += BIOS_ID;
		strResult += "\n";

		strResult += "BIOS_Type: ";
		strResult += BIOS_Type;
		strResult += "\n";

		strResult += "BIOS_Date: ";
		strResult += BIOS_Date;
		::MessageBox(0, strResult, "BIOS infomation", MB_OK);
	}
	return;
}

//检测硬盘信息
void CRunTestDlg::OnButtonCheckHarddisk() 
{
	BOOL (FAR *lpfn)(int DriveNo, InfoOfHardDiskDevice& HardDiskInfoStruct);

	HMODULE hLibrary=LoadLibrary("DetectHardware.dll");
	if(hLibrary == NULL)
	{
		::MessageBox(0, "'DetectHardware.dll' Loading failed", "", MB_OK);
		return;
	}
	lpfn = (int (__cdecl *)(int ,InfoOfHardDiskDevice&))GetProcAddress(hLibrary, "DetectHardDiskDevice_DetectHardwareModule");
	if(lpfn == NULL)
	{
		FreeLibrary(hLibrary);
		::MessageBox(0, "Get Function 'DetectHardDiskDevice_DetectHardwareModule()' failed", "", MB_OK);
		return;
	}

	CString strResult;
	InfoOfHardDiskDevice m_Info;

	char buff[50];

	for(int i = 1; i < 4; i++)//检测4块硬盘，pc机上最多为4块
	{
		BOOL flag = (*lpfn)(i, m_Info);
		if(m_Info.IsExist == 1)
		{
			strResult = "Drive Level: ";
			strResult += m_Info.strLevelOfController;
			strResult += "\n";

			strResult += "Drive Model Number: ";
			strResult += m_Info.DriveModelNumber;
			strResult += "\n";

			strResult += "SerialNumber: ";
			strResult += m_Info.DriveSerialNumber;
			strResult += "\n";

			strResult += "Drive Controller Revision Number: ";
			strResult += m_Info.DriveControllerRevisionNumber;
			strResult += "\n";

			strResult += "Drive Type: ";
			strResult += m_Info.strDriveType;
			strResult += "\n";

			strResult += "Buffer Size: ";
			strResult += itoa(m_Info.ControllerBufferSizeonDrive, buff, 10);
			strResult += "\n";

			strResult += "Cylinders: ";
			strResult += itoa(m_Info.Cylinders, buff, 10);
			strResult += "\n";

			strResult += "Heads: ";
			strResult += itoa(m_Info.Heads, buff, 10);
			strResult += "\n";

			strResult += "Sectors Per Track: ";
			strResult += itoa(m_Info.SectorsPerTrack, buff, 10);

			::MessageBox(0, strResult, "Hard Disk Device Infomation", MB_OK);
		}
	}
	FreeLibrary(hLibrary);
}

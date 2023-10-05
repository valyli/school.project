// ClientTransferModuleDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClientTransferModuleDemo.h"
#include "ClientTransferModuleDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

//引入徐辉编写的队列操作
#include "test.h"

//存储队列ID值，用于徐辉写的队列操作
SMM_INT  iID;							//队列ID

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
// CClientTransferModuleDemoDlg dialog

CClientTransferModuleDemoDlg::CClientTransferModuleDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientTransferModuleDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientTransferModuleDemoDlg)
	m_InfomationElementTableID = 0;
	m_InfomationElementID = 0;
	m_Data = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	hLibrary = NULL;
}

void CClientTransferModuleDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientTransferModuleDemoDlg)
	DDX_Text(pDX, IDC_EDIT_InfomationElementTableID, m_InfomationElementTableID);
	DDX_Text(pDX, IDC_EDIT_InfomationElementID, m_InfomationElementID);
	DDX_Text(pDX, IDC_EDIT_Data, m_Data);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClientTransferModuleDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CClientTransferModuleDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_GETALLMODULEINFO, OnButtonGetallmoduleinfo)
	ON_BN_CLICKED(IDC_BUTTON_Load_CTransferModule, OnBUTTONLoadCTransferModule)
	ON_BN_CLICKED(IDC_BUTTON_Free_CTransferModule, OnBUTTONFreeCTransferModule)
	ON_BN_CLICKED(IDC_BUTTON_Transfer_Module, OnBUTTONTransferModule)
	ON_BN_CLICKED(IDC_BUTTON_Transfer_Module_By_TLV, OnBUTTONTransferModuleByTLV)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientTransferModuleDemoDlg message handlers

BOOL CClientTransferModuleDemoDlg::OnInitDialog()
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
	
	//调用徐辉的方法创建队列
	ITDQ_Init();
	iID=ITDQ_Create(1,Data_Size);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClientTransferModuleDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClientTransferModuleDemoDlg::OnPaint() 
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
HCURSOR CClientTransferModuleDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


//调用Client端调度模块的GetAllModuleInfoToMemory()方法
void CClientTransferModuleDemoDlg::OnButtonGetallmoduleinfo() 
{
	if(hLibrary == NULL)
	{
		::MessageBox(0, "Without Transfer Load_CTransferModule()", "CClientTransferModuleDemoDlg", MB_OK);
		return;
	}

	bool (FAR *lpfn)();
	lpfn = (bool (__cdecl *)())GetProcAddress(hLibrary, "ClientGetAllModuleInfoToMemory");
	if(lpfn == NULL)
	{
		AlarmErrorMessage("Get Function ClientGetAllModuleInfoToMemory() Failed", "Load Library Error");
		return;
	}
	bool flag = (*lpfn)();
	if(flag)
		::MessageBox(0, "ClientGetAllModuleInfoToMemory() Success", "CClientTransferModuleDemoDlg", MB_OK);
}


//导入Client端调度模块
bool CClientTransferModuleDemoDlg::Load_CTransferModule()
{
	CString strDllFilePath = "CClientModuleTransfer.dll";
	hLibrary=LoadLibrary(strDllFilePath);
	CString temp;
	if(hLibrary == NULL)
	{
		temp = "Load ";
		temp += strDllFilePath;
		temp += "Failed";
		return AlarmErrorMessage(temp, "Load Library Error");
	}
	return true;
}

void CClientTransferModuleDemoDlg::OnBUTTONLoadCTransferModule() 
{
	if(Load_CTransferModule())
		::MessageBox(0, "Load_CTransferModule Success", "CClientTransferModuleDemoDlg", MB_OK);
}


//释放Client端调度模块
void CClientTransferModuleDemoDlg::OnBUTTONFreeCTransferModule() 
{
	if(hLibrary == NULL)
	{
		::MessageBox(0, "Without Transfer Load_CTransferModule()", "CClientTransferModuleDemoDlg", MB_OK);
	}
	else
	{
		FreeLibrary(hLibrary);
		hLibrary = NULL;
		::MessageBox(0, "Free_CTransferModule Success", "CClientTransferModuleDemoDlg", MB_OK);
	}
}


//根据用户对InfomationElementID和InfomationElementTableID的选择，调用相应的模块
//用CManageData传参数
void CClientTransferModuleDemoDlg::OnBUTTONTransferModule() 
{
	bool (FAR *lpfn)(ModuleInfomationListStruct &ModuleInfo, CManageData& Data);
	lpfn = (bool (__cdecl *)(struct ModuleInfomationListStruct &,class CManageData &))GetProcAddress(hLibrary, "ClientTransferModuleByCManageData");
	if(lpfn == NULL)
	{
		AlarmErrorMessage("Get Function ClientTransferModuleByCManageData() Failed", "Load Library Error");
		return;
	}

	ModuleInfomationListStruct ModuleInfo;
	CManageData Data;

	//临时开始
	UpdateData(TRUE);
	Data.SetData(this->m_Data);
	ModuleInfo.InfomationElementTableID = this->m_InfomationElementTableID;
	ModuleInfo.InfomationElementID = this->m_InfomationElementID;
	//临时结束

	bool flag = (*lpfn)(ModuleInfo, Data);
	if(flag)
	{
		::MessageBox(0, "ClientTransferModule() Success", "CClientTransferModuleDemoDlg", MB_OK);
		Data.GetData(this->m_Data);
		UpdateData(FALSE);
	}
}



//根据用户对InfomationElementID和InfomationElementTableID的选择，调用相应的模块
//用TLVStruct传参数
void CClientTransferModuleDemoDlg::OnBUTTONTransferModuleByTLV() 
{
	bool (FAR *lpfn)(ModuleInfomationListStruct &ModuleInfo, TLVStruct &TLVData);
	lpfn = (bool (__cdecl *)(struct ModuleInfomationListStruct &,struct TLVStruct &))GetProcAddress(hLibrary, "ClientTransferModuleByTLV");
	if(lpfn == NULL)
	{
		AlarmErrorMessage("Get Function ClientTransferModuleByTLV() Failed", "Load Library Error");
		return;
	}

	CManageData Data;
	ModuleInfomationListStruct ModuleInfo;

	//临时开始
	UpdateData(TRUE);
	Data.SetData(this->m_Data);
	ModuleInfo.InfomationElementTableID = this->m_InfomationElementTableID;
	ModuleInfo.InfomationElementID = this->m_InfomationElementID;
	//临时结束

	TLVStruct TLVData;//, TLVData1;
	Data.GetDatabyTLV(TLVData);		//试验时用TLVData1
/*
//拆分试验，不考虑结构体中的数据类型
//直接将结构体拆分到2进制数组内
//最后还原回结构体当中
///////////////////////////////////////////////////////////////////////
	unsigned char tempbuff1[150], tempbuff2[150];

	char buff[100];
	int i;
	::MessageBox(0, itoa(sizeof(TLVStruct), buff, 10), "TLVData size", MB_OK);
	int n = sizeof(TLVStruct);
	//拆
	//1
	for(i = 0; i < 150; i++)
	{
		tempbuff1[i] = ((unsigned char*)&TLVData1)[i];
		n--;
	}
	//2
	for(i = 0; i < n; i++)
	{
		tempbuff2[i] = ((unsigned char*)&TLVData1)[i+150];
		n--;
	}

	//合
	//1
	n = sizeof(TLVStruct);
	for(i = 0; i < 150; i++)
	{
		((unsigned char*)&TLVData)[i] = tempbuff1[i];
		n--;
	}
	//2
	for(i = 0; i < n; i++)
	{
		((unsigned char*)&TLVData)[i+150] = tempbuff2[i];
		n--;
	}

///////////////////////////////////////////////////////////////////////
*/


	bool flag = (*lpfn)(ModuleInfo, TLVData);
	if(flag)
	{
		Data.SetDatabyTLV(TLVData);
		::MessageBox(0, "ClientTransferModule() Success", "ClientTransferModuleByTLV", MB_OK);
		Data.GetData(this->m_Data);
		UpdateData(FALSE);
	}


	//加入徐辉写的队列操作
	//写入队列
	SMM_CHAR *pSize=(char*)malloc(Data_Size);

	//将参数返回的参数装入pSize
	for(int i = 0; i < 256; i++)
	{
		pSize[i] = ((unsigned char*)&TLVData.Value.Value_Char)[i];
	}

	SMM_INT  iWrite=ITDQ_Write(iID,pSize);
	
	//用读测试
	iWrite=ITDQ_Read(iID,pSize);
	::MessageBox(0, pSize, "测试结果（从队列中读数据）", MB_OK);


}

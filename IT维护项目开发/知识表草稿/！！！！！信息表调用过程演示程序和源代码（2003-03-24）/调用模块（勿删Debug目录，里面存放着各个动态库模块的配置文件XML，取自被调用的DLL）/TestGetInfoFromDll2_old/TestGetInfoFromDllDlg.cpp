// TestGetInfoFromDllDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestGetInfoFromDll.h"
#include "TestGetInfoFromDllDlg.h"

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
// CTestGetInfoFromDllDlg dialog

CTestGetInfoFromDllDlg::CTestGetInfoFromDllDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestGetInfoFromDllDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestGetInfoFromDllDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestGetInfoFromDllDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestGetInfoFromDllDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestGetInfoFromDllDlg, CDialog)
	//{{AFX_MSG_MAP(CTestGetInfoFromDllDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_GETINFO, OnButtonGetinfo)
	ON_BN_CLICKED(IDC_BUTTON_ADD_INFOMATIONTABLEINLISTTABLE, OnButtonAddInfomationtableinlisttable)
	ON_BN_CLICKED(IDC_BUTTON_ViewOrModifyInfomationTableInListTable, OnBUTTONViewOrModifyInfomationTableInListTable)
	ON_BN_CLICKED(IDC_BUTTON_ADD_INFOMATION_FROM_DLL_TO_MEMORY, OnButtonAddInfomationFromDllToMemory)
	ON_BN_CLICKED(IDC_BUTTON_VIEW_OPERATION_INFOMATION_IN_MEMORY, OnButtonViewOperationInfomationInMemory)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestGetInfoFromDllDlg message handlers

BOOL CTestGetInfoFromDllDlg::OnInitDialog()
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

void CTestGetInfoFromDllDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestGetInfoFromDllDlg::OnPaint() 
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
HCURSOR CTestGetInfoFromDllDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//////////////////////////////////////////////////////////////////////////////////
//相应测试读取DLL的XML配置文件按钮
void CTestGetInfoFromDllDlg::OnButtonGetinfo() 
{
	//选择要查看的dll文件
	CString strDllFilePath;
	ModuleInfomationStruct m_Info;

	static char BASED_CODE szFilter[] = "Chart Files (*.xlc)|*.xlc|Worksheet Files (*.xls)|*.xls|Data Files (*.xlc;*.xls)|*.xlc";
	CFileDialog m_CFileDialog(TRUE, NULL, NULL, OFN_READONLY);
	if(m_CFileDialog.DoModal() == IDOK)
	{
		strDllFilePath = m_CFileDialog.GetPathName();
		GetInfoListFromDll(m_Info, strDllFilePath);

		CString temp;
		char buff[256];
		//显示dll典型的Module发布信息
		temp = "\nInfoModuleTypeProviderId: ";
		temp += itoa(m_Info.InfoModuleTypeProviderId, buff, 10);

		temp += "\nInfoModuleTypeId: ";
		temp += itoa(m_Info.InfoModuleTypeId, buff, 10);

		temp += "\nInfoModuleProviderId: ";
		temp += itoa(m_Info.InfoModuleProviderId, buff, 10);

		temp += "\nInfoServiceProviderId: ";
		temp += itoa(m_Info.InfoServiceProviderId, buff, 10);

		temp += "\nNameBaseId: ";
		temp += itoa(m_Info.NameBaseId, buff, 10);

		::MessageBox(0, temp, "dll典型的Module发布信息", MB_OK);

		//显示从dll获得的信息，信息存储于CArrayModuleInfomationListStruct
		for(int i = 0; i < m_Info.ListArray.GetSize(); i++)
		{
			temp = "Function InfoList";
			
			temp += "\nOperationID: ";
			temp += itoa(m_Info.ListArray.GetAt(i).OperationID, buff, 10);
			
			temp += "\nInfomationElementTableID: ";
			temp += itoa(m_Info.ListArray.GetAt(i).InfomationElementTableID, buff, 10);
			
			temp += "\nInfomationElementID: ";
			temp += itoa(m_Info.ListArray.GetAt(i).InfomationElementID, buff, 10);
			
			temp += "\nOperationType: ";
			temp += itoa(m_Info.ListArray.GetAt(i).OperationType, buff, 10);
			
			temp += "\nServiceFileName: ";
			temp += m_Info.ListArray.GetAt(i).ServiceFileName;
			
			temp += "\nSupportSystemType: ";
			temp += itoa(m_Info.ListArray.GetAt(i).SupportSystemType, buff, 10);
			
			temp += "\nModuleType: ";
			temp += itoa(m_Info.ListArray.GetAt(i).ModuleType, buff, 10);
			
			temp += "\nInterfaceFunction: ";
			temp += m_Info.ListArray.GetAt(i).InterfaceFunction;
			
			temp += "\nParameterType: ";
			temp += itoa(m_Info.ListArray.GetAt(i).ParameterType, buff, 10);
			
			temp += "\nIsStorageReturnValueInParameter: ";
			temp += itoa(m_Info.ListArray.GetAt(i).IsStorageReturnValueInParameter, buff, 10);
			
			temp += "\nParameterValue: ";
			temp += m_Info.ListArray.GetAt(i).ParameterValue;
			
			
			::MessageBox(0, temp, itoa(i, buff, 10), MB_OK);
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////
//获取dll信息，并用m_Info返回
//strDllFilePath为动态库的全路径
bool CTestGetInfoFromDllDlg::GetInfoListFromDll(ModuleInfomationStruct &m_Info,
												CString strDllFilePath)
{
	CString temp;
	
	bool (FAR *lpfn)(ModuleInfomationStruct &InfoList);
	
	
	HMODULE hLibrary=LoadLibrary(strDllFilePath);
	if(hLibrary == NULL)
	{
		temp = "Load ";
		temp += strDllFilePath;
		temp += "Failed";
		return AlarmErrorMessage(temp, "Load Library Error");
	}
	lpfn = (bool (__cdecl *)(ModuleInfomationStruct&))GetProcAddress(hLibrary, "InfoList");
	if(lpfn == NULL)
	{
		FreeLibrary(hLibrary);
		return AlarmErrorMessage("Get Function 'InfoList()' Failed", "Load Library Error");
	}
	
	bool flag = (*lpfn)(m_Info);
	
	FreeLibrary(hLibrary);
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////



//在信息项列表中添加表项按钮
void CTestGetInfoFromDllDlg::OnButtonAddInfomationtableinlisttable() 
{
	CAddInfomationTableDlg m_AddInfomationTableDlg;
	m_AddInfomationTableDlg.DoModal();
}

//查看或修改信息项列表中的表项
void CTestGetInfoFromDllDlg::OnBUTTONViewOrModifyInfomationTableInListTable() 
{
	CModifyInfomationTableDlg m_ModifyInfomationTableDlg;
	m_ModifyInfomationTableDlg.DoModal();
}

//把选定的dll中的配置信息添加到在内存中的操作表
//!!操作ID（OperationID）为导入时自动排布，DLL中存储的此自段失效
void CTestGetInfoFromDllDlg::OnButtonAddInfomationFromDllToMemory() 
{
	//选择要查看的dll文件
	CString strDllFilePath;
	ModuleInfomationStruct m_Info;
	ModuleInfomationListStruct m_InfoStruct;

	static char BASED_CODE szFilter[] = "Chart Files (*.xlc)|*.xlc|Worksheet Files (*.xls)|*.xls|Data Files (*.xlc;*.xls)|*.xlc";
	CFileDialog m_CFileDialog(TRUE, NULL, NULL, OFN_READONLY);
	if(m_CFileDialog.DoModal() == IDOK)
	{
		strDllFilePath = m_CFileDialog.GetPathName();
		//从一个dll获取操作表数据，可能有多个操作项
		if(!GetInfoListFromDll(m_Info, strDllFilePath))
		{
			AlarmErrorMessage("GetInfoListFromDll() Failed", "");
			return;
		}
		int SizeOfArray;
		for(int i = 0; i < m_Info.ListArray.GetSize(); i++)
		{
			m_InfoStruct = m_Info.ListArray.GetAt(i);
			SizeOfArray = m_CArrayOperationTable.GetSize();
			//重新设置操作ID，从1起
			m_InfoStruct.OperationID = SizeOfArray + 1;
			m_CArrayOperationTable.Add(m_InfoStruct);
		}
	}
}

//查看在内存中建立的操作表
void CTestGetInfoFromDllDlg::OnButtonViewOperationInfomationInMemory() 
{
	//若操作表尚无数据时
	if(m_CArrayOperationTable.GetSize() == 0)
	{
		::MessageBox(0, "Operation Table is Empty", "", MB_OK);
		return;
	}
	//显示从dll获得的信息，信息存储于CArrayModuleInfomationListStruct
	CString temp;
	char buff[256];
	for(int i = 0; i < m_CArrayOperationTable.GetSize(); i++)
	{
		temp = "Function InfoList";
		
		temp += "\nOperationID: ";
		temp += itoa(m_CArrayOperationTable.GetAt(i).OperationID, buff, 10);
		
		temp += "\nInfomationElementTableID: ";
		temp += itoa(m_CArrayOperationTable.GetAt(i).InfomationElementTableID, buff, 10);
		
		temp += "\nInfomationElementID: ";
		temp += itoa(m_CArrayOperationTable.GetAt(i).InfomationElementID, buff, 10);
		
		temp += "\nOperationType: ";
		temp += itoa(m_CArrayOperationTable.GetAt(i).OperationType, buff, 10);
		
		temp += "\nServiceFileName: ";
		temp += m_CArrayOperationTable.GetAt(i).ServiceFileName;
		
		temp += "\nSupportSystemType: ";
		temp += itoa(m_CArrayOperationTable.GetAt(i).SupportSystemType, buff, 10);
		
		temp += "\nModuleType: ";
		temp += itoa(m_CArrayOperationTable.GetAt(i).ModuleType, buff, 10);
		
		temp += "\nInterfaceFunction: ";
		temp += m_CArrayOperationTable.GetAt(i).InterfaceFunction;
		
		temp += "\nParameterType: ";
		temp += itoa(m_CArrayOperationTable.GetAt(i).ParameterType, buff, 10);
		
		temp += "\nIsStorageReturnValueInParameter: ";
		temp += itoa(m_CArrayOperationTable.GetAt(i).IsStorageReturnValueInParameter, buff, 10);
		
		temp += "\nParameterValue: ";
		temp += m_CArrayOperationTable.GetAt(i).ParameterValue;
		
		
		::MessageBox(0, temp, itoa(i, buff, 10), MB_OK);
	}
}

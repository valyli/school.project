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
	HKEY hKEY;//�����йص� hKEY, �ڲ�ѯ����ʱҪ�رա�
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

	//����·�� data_Set ��ص� hKEY����һ������Ϊ�������ƣ��ڶ��������� 
	//��ʾҪ���ʵļ���λ�ã���������������Ϊ0��KEY_READ��ʾ�Բ�ѯ�ķ�ʽ.
	//����ע���hKEY�򱣴�˺������򿪵ļ��ľ���� 
	long ret0=(::RegOpenKeyEx(HKEY_LOCAL_MACHINE,data_Set, 0, KEY_READ, &hKEY)); 
	if(ret0!=ERROR_SUCCESS) //����޷���hKEY������ֹ�����ִ��
	{
		MessageBox("����: �޷����йص�hKEY!"); 
		return;
	} 
	//��ѯ�йص����� (�û����� owner_Get)�� 
	LPBYTE owner_Get=new BYTE[80];
	DWORD type_1=REG_SZ ; DWORD cbData_1=80;
	//hKEYΪ�ղ�RegOpenKeyEx()�������򿪵ļ��ľ����"RegisteredOwner"�� 
	//��ʾҪ�� ѯ�ļ�ֵ����type_1��ʾ��ѯ���ݵ����ͣ�owner_Get�������� 
	//��ѯ�����ݣ�cbData_1��ʾԤ���õ����ݳ��ȡ� 
	long ret1=::RegQueryValueEx(hKEY, "RegisteredOwner", NULL, &type_1, owner_Get, &cbData_1); 
	if(ret1!=ERROR_SUCCESS) 
	{ 
		MessageBox("����: �޷���ѯ�й�ע�����Ϣ!"); 
		return; 
	} 
	// ��ѯ�йص����� (��˾�� company_Get)
	LPBYTE company_Get=new BYTE [80];
	DWORD type_2=REG_SZ; DWORD cbData_2=80;
	long ret2=::RegQueryValueEx(hKEY, "RegisteredOrganization", NULL,&type_2,company_Get, &cbData_2);
	if(ret2!=ERROR_SUCCESS)
	{
		MessageBox("����: �޷���ѯ�й�ע�����Ϣ!");
		return;
	}
	// �� owner_Get �� company_Get ת��Ϊ CString �ַ���, �Ա���ʾ���.
	CString str_owner=CString(owner_Get);
	CString str_company=CString(company_Get);

	delete[] owner_Get; delete[] company_Get;
	// �������ǰҪ�ر��Ѿ��򿪵� hKEY�� 
	::RegCloseKey(hKEY);

	::MessageBox(0, str_owner, "RegisteredOwner", MB_OK);
	::MessageBox(0, str_company, "RegisteredOrganization", MB_OK);

}

//��ȡ��CString���͵��й��ַ�����Ҫ�Ƚ���ת��ΪLPBYTE(��unsigned char��)�͵���������
LPBYTE CString_To_LPBYTE(CString str) 
{ 
	LPBYTE lpb = new BYTE[str.GetLength()+1];  
	for(int i=0; (i<str.GetLength())&&(*(lpb+i) = str.GetAt(i));i++);
	return lpb;
} 

void CTestRegisterDlg::OnButtonSet() 
{
	UpdateData(TRUE);
	//�����йص� hKEY, �ڳ�������Ҫ�رա�
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

	//����·�� data_Set ��ص�hKEY��KEY_WRITE��ʾ��д�ķ�ʽ�򿪡�
	long ret0=(::RegOpenKeyEx(HKEY_LOCAL_MACHINE, data_Set, 0, KEY_WRITE, &hKEY));
	if(ret0!=ERROR_SUCCESS)
	{
		MessageBox("����: �޷����йص�hKEY!");
		return;
	}
	//�޸��й�����(�û����� owner_Set)��Ҫ�Ƚ�CString��ת��ΪLPBYTE
	LPBYTE owner_Set=CString_To_LPBYTE(str_owner);
	for(int i=0; (i<str_owner.GetLength())&&(*(owner_Set+i) = str_owner.GetAt(i));i++);

	DWORD type_1=REG_SZ;
	DWORD cbData_1=str_owner.GetLength()+1;
	//��RegQureyValueEx()���ƣ�hKEY��ʾ�Ѵ򿪵ļ��ľ����"RegisteredOwner"
	//��ʾҪ���ʵļ�ֵ����owner_Set��ʾ�µļ�ֵ��type_1��cbData_1��ʾ��ֵ.
	//���������ͺ����ݳ���
	long ret1=::RegSetValueEx(hKEY, "RegisteredOwner", NULL, type_1, owner_Set, cbData_1);
	if(ret1!=ERROR_SUCCESS)
	{
		MessageBox("����: �޷��޸��й�ע�����Ϣ!");
		return;
	}
	//�޸��йص����� (��˾�� company_Set)
	LPBYTE company_Set=CString_To_LPBYTE(str_company);
	DWORD type_2=REG_SZ;
	DWORD cbData_2=str_company.GetLength()+1;
	long ret2=::RegSetValueEx(hKEY, "RegisteredOrganization", NULL,	type_2, company_Set, cbData_2);
	if(ret2!=ERROR_SUCCESS)
	{
		MessageBox("����: �޷��޸��й�ע�����Ϣ!");
		return;
	}
	::RegCloseKey(hKEY);
}
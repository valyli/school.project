// TestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"

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
// CTestDlg dialog

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDlg)
	m_try1 = 0;
	m_try2 = 0;
	m_try3 = 0;
	m_try4 = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlg)
	DDX_Text(pDX, IDC_EDIT1, m_try1);
	DDX_Text(pDX, IDC_EDIT2, m_try2);
	DDX_Text(pDX, IDC_EDIT3, m_try3);
	DDX_Text(pDX, IDC_EDIT4, m_try4);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg message handlers

BOOL CTestDlg::OnInitDialog()
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

void CTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestDlg::OnPaint() 
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
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestDlg::OnButton1() 
{
	//��dll�ļ�
	static char BASED_CODE szFilter[] = "Chart Files (*.xlc)|*.xlc|Worksheet Files (*.xls)|*.xls|Data Files (*.xlc;*.xls)|*.xlc"; 
	CFileDialog m_CFileDialog(TRUE, NULL, NULL, OFN_READONLY);
	if(m_CFileDialog.DoModal() == IDOK)
	{
		CString strFileName, strFilePath;
		strFileName = m_CFileDialog.GetFileName();
		strFilePath = m_CFileDialog.GetPathName();

		//��ȡ�����Դ�ռ�Ĵ�С
		DWORD dwLen;
		LPVOID lpData;
		dwLen = ::GetFileVersionInfoSize(strFilePath.GetBuffer(strFilePath.GetLength()), 0);
		//�ж�GetFileVersionInfoSize�Ƿ�ɹ�
		if(dwLen == 0)//ʧ��
		{
			::MessageBox(0, "Error for GetFileVersionInfoSize()", "", MB_OK);
			return;
		}
		else
		{
			//����Ű汾��Դ�Ŀռ�
			lpData = new char[dwLen];

			//��ȡ�汾��Ϣ
			//��ʧ��
			if( FALSE == ::GetFileVersionInfo(strFilePath.GetBuffer(strFilePath.GetLength()), 0, dwLen, lpData))
			{
				::MessageBox(0, "Error for GetFileVersionInfo()", "", MB_OK);
				delete[] lpData;
			}
			else
			{
				//������Ż�ȡ�汾��Ϣ�Ŀռ�
				VS_FIXEDFILEINFO *lpTranslate;
				UINT cbTranslate = sizeof(lpTranslate);
				VerQueryValue(lpData,
							  TEXT("\\"),
							  (LPVOID*)&lpTranslate,
							  &cbTranslate);
				//��ֳ�windows��ʾ�汾��Ϣ��Ĭ�ϸ�ʽ
				//������λ����ʱ����
				DWORD temp;

				//��һ��
				temp = lpTranslate[0].dwFileVersionMS;
				temp = temp & 0xffff0000;
				temp = temp >> 16;
				this->m_try1 = temp;

				//�ڶ���
				temp = lpTranslate[0].dwFileVersionMS;
				temp = temp & 0x0000ffff;
				this->m_try2 = temp;


				//������
				temp = lpTranslate[0].dwFileVersionLS;
				temp = temp & 0xffff0000;
				temp = temp >> 16;
				this->m_try3 = temp;


				//���Ķ�
				temp = lpTranslate[0].dwProductVersionLS;
				temp = temp & 0x0000ffff;
				this->m_try4 = temp;


				delete[] lpData;

				UpdateData(FALSE);
			}
		}
	}
}

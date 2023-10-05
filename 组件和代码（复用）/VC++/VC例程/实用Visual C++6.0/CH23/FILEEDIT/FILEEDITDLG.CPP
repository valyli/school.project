// FileEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FileEdit.h"
#include "FileEditDlg.h"

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
// CFileEditDlg dialog

CFileEditDlg::CFileEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileEditDlg)
	m_EditBox = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileEditDlg)
	DDX_Text(pDX, IDC_FILEEDIT, m_EditBox);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFileEditDlg, CDialog)
	//{{AFX_MSG_MAP(CFileEditDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileEditDlg message handlers

BOOL CFileEditDlg::OnInitDialog()
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
	
	//Declare and open a file object for reading
	CFile fileEditText;
	if (fileEditText.Open("c:\\MyFile.txt",CFile::modeRead))
	{
		//Declare a large buffer for reading the text
		char cBuf[512];
		UINT uBytesRead;

		//Continue reading until no more data is read
		while (uBytesRead = 
			fileEditText.Read(cBuf,sizeof(cBuf)-1))
		{
			//NULL terminate after the last character
			cBuf[uBytesRead]=NULL;

			//Add the buffer to the mapped CString
			m_EditBox+=CString(cBuf);
		}

		//Close the file
		fileEditText.Close();

		//Send the m_EditBox string to the edit control
		UpdateData(FALSE);
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFileEditDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFileEditDlg::OnPaint() 
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
HCURSOR CFileEditDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFileEditDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//Set the m_EditBox string from the edit control
	UpdateData(TRUE);

	//Declare and open a file object for writing
	CFile fileEditText;
	if (fileEditText.Open("c:\\MyFile.Txt",
		CFile::modeCreate+CFile::modeWrite))
	{
		//Write out the full string
		fileEditText.Write(
			(LPCSTR) m_EditBox,m_EditBox.GetLength());

		//Close the file
		fileEditText.Close();
	}
	
	CFileStatus statusEditText;
	CFile::GetStatus("c:\\MyFile.txt",statusEditText);
	AfxMessageBox(_T("Last Modified on")+
		statusEditText.m_mtime.Format("%A %B %d, %Y"));
	CDialog::OnOK();
}

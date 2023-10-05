// CalculatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "math.h"

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
// CCalculatorDlg dialog

CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCalculatorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalculatorDlg)
	m_Shownum = 0.0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	Oldnum=0.0;
	Newnum=0.0;
	Point=0;
	Firstnum=1;
	Lastproc=0;
	Equed=0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalculatorDlg)
	DDX_Text(pDX, IDC_EDIT1, m_Shownum);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialog)
	//{{AFX_MSG_MAP(CCalculatorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_NUM0, OnButtonNum0)
	ON_BN_CLICKED(IDC_BUTTON_NUM1, OnButtonNum1)
	ON_BN_CLICKED(IDC_BUTTON_NUM2, OnButtonNum2)
	ON_BN_CLICKED(IDC_BUTTON_NUM3, OnButtonNum3)
	ON_BN_CLICKED(IDC_BUTTON_NUM4, OnButtonNum4)
	ON_BN_CLICKED(IDC_BUTTON_NUM5, OnButtonNum5)
	ON_BN_CLICKED(IDC_BUTTON_NUM6, OnButtonNum6)
	ON_BN_CLICKED(IDC_BUTTON_NUM7, OnButtonNum7)
	ON_BN_CLICKED(IDC_BUTTON_NUM8, OnButtonNum8)
	ON_BN_CLICKED(IDC_BUTTON_NUM9, OnButtonNum9)
	ON_BN_CLICKED(IDC_BUTTON_POINT, OnButtonPoint)
	ON_BN_CLICKED(IDC_BUTTON_CE, OnButtonCe)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_C, OnButtonC)
	ON_BN_CLICKED(IDC_BUTTON_DEC, OnButtonDec)
	ON_BN_CLICKED(IDC_BUTTON_DIV, OnButtonDiv)
	ON_BN_CLICKED(IDC_BUTTON_MUL, OnButtonMul)
	ON_BN_CLICKED(IDC_BUTTON_EQU, OnButtonEqu)
	ON_BN_CLICKED(IDC_BUTTON_SIN, OnButtonSin)
	ON_BN_CLICKED(IDC_BUTTON_COS, OnButtonCos)
	ON_BN_CLICKED(IDC_BUTTON_LOG, OnButtonLog)
	ON_BN_CLICKED(IDC_BUTTON_LN, OnButtonLn)
	ON_BN_CLICKED(IDC_BUTTON_SQR, OnButtonSqr)
	ON_BN_CLICKED(IDC_BUTTON_SQRT, OnButtonSqrt)
	ON_BN_CLICKED(IDC_BUTTON_EX, OnButtonEx)
	ON_BN_CLICKED(IDC_BUTTON_X, OnButtonX)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalculatorDlg message handlers

BOOL CCalculatorDlg::OnInitDialog()
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

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCalculatorDlg::OnPaint() 
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
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCalculatorDlg::Getnum(int num)
{
	Newnum = Newnum * (Point?1:10) + num * (Point? pow(10,-1*Point):1);
	Point = Point + (Point?1:0);
	m_Shownum=Newnum;
	UpdateData(FALSE);
}
void CCalculatorDlg::OnButtonNum0() 
{
	Getnum(0);
}

void CCalculatorDlg::OnButtonNum1() 
{
	Getnum(1);
	
}

void CCalculatorDlg::OnButtonNum2() 
{
	Getnum(2);
	
}

void CCalculatorDlg::OnButtonNum3() 
{
	Getnum(3);
	
}

void CCalculatorDlg::OnButtonNum4() 
{
	Getnum(4);
	
}

void CCalculatorDlg::OnButtonNum5() 
{
	Getnum(5);
	
}

void CCalculatorDlg::OnButtonNum6() 
{
	Getnum(6);
	
}

void CCalculatorDlg::OnButtonNum7() 
{
	Getnum(7);
	
}

void CCalculatorDlg::OnButtonNum8() 
{
	Getnum(8);
	
}

void CCalculatorDlg::OnButtonNum9() 
{
	Getnum(9);
	
}

void CCalculatorDlg::OnButtonPoint() 
{
	Point = Point?Point:1;
}

void CCalculatorDlg::OnButtonC() 
{
	Newnum = 0.0;
	Oldnum = 0.0;
	Point = 0;
	Firstnum = 1;
	Lastproc = 0;
	m_Shownum = Newnum;
	UpdateData(FALSE);
}

void CCalculatorDlg::OnButtonCe() 
{
	Newnum = 0.0;
	Point = 0;
	Lastproc = 0;
	m_Shownum = Newnum;
	UpdateData(FALSE);
}

void CCalculatorDlg::Showresult()
{
	m_Shownum = Oldnum;
	UpdateData(FALSE);
}

void CCalculatorDlg::Endnewnum()
{
	Point = 0;
	Newnum = 0.0;
}

void CCalculatorDlg::Oldproc()
{
	switch(Lastproc)
	{
	case 0:
		break;
	case 1:
		Oldnum += Newnum;break;
	case 2:
		Oldnum -= Newnum;break;
	case 3:
		Oldnum *= Newnum;break;
	case 4:
		Oldnum /= Newnum;break;
	case 5:
		Oldnum = sin(Oldnum);break;
	case 6:
		Oldnum = sin(Oldnum);break;
	case 7:
		Oldnum = log10(Oldnum);break;
	case 8:
		Oldnum = log(Oldnum);break;
	case 9:
		Oldnum = Oldnum * Oldnum;break;
	case 10:
		Oldnum = sqrt(Oldnum);break;
	default:
		break;
	}
//	Endnewnum();
	Showresult();
//	Lastproc = 0;
}

void CCalculatorDlg::OnButtonAdd()
{
	if(Firstnum == 1)
	{
		Oldnum += Newnum;
		Firstnum = 0;
	}
	else if(Equed == 0)
	{
		Oldproc();
//		Oldnum += Newnum;
	}
	Endnewnum();
	Showresult();
	Lastproc = 1;
	Equed = 0;
}

void CCalculatorDlg::OnButtonDec()
{
	if(Firstnum == 1)
	{
		Oldnum = Newnum;
		Firstnum = 0;
	}
	else if(Equed == 0)
	{
		Oldproc();
//		Oldnum -= Newnum;
	}
	Endnewnum();
	Showresult();
	Lastproc = 2;
	Equed = 0;
}

void CCalculatorDlg::OnButtonMul() 
{
	if(Firstnum == 1)
	{
		Oldnum = Newnum;
		Firstnum = 0;
	}
	else if(Equed == 0)
	{
		Oldproc();
//		Oldnum *= Newnum;
	}
	Endnewnum();
	Showresult();
	Lastproc = 3;
	Equed = 0;
}

void CCalculatorDlg::OnButtonDiv() 
{
	if(Newnum == 0.0)
		MessageBox("Error of input 0");
	else
	{
		if(Firstnum == 1)
		{
			Oldnum = Newnum;
			Firstnum = 0;
		}
		else if(Equed == 0)
		{
			Oldproc();
		}
		Endnewnum();
		Showresult();
		Lastproc = 4;
		Equed = 0;
	}
}

void CCalculatorDlg::OnButtonEqu() 
{
	if(Firstnum == 0)
	{
		Oldproc();	
		Equed = 1;
	}
}

void CCalculatorDlg::OnButtonSin() 
{
	if(Firstnum == 1)
	{
		Oldnum = sin(Newnum);
		Firstnum = 0;
	}
	else
		Oldnum = sin(Oldnum);
	Endnewnum();
	Showresult();
	Lastproc = 5;
	Equed = 0;
}

void CCalculatorDlg::OnButtonCos() 
{
	if(Firstnum == 1)
	{
		Oldnum = cos(Newnum);
		Firstnum = 0;
	}
	else
		Oldnum = cos(Oldnum);
	Endnewnum();
	Showresult();
	Lastproc = 6;
	Equed = 0;	
}

void CCalculatorDlg::OnButtonLog() 
{
	if(Newnum <= 0 || Oldnum <=0)
		MessageBox("it is too min");
	else
	{
		if(Firstnum == 1)
		{
			Oldnum = log10(Newnum);
			Firstnum = 0;
		}
		else
			Oldnum = log10(Oldnum);
		Endnewnum();
		Showresult();
		Lastproc = 7;
		Equed = 0;
	}
}

void CCalculatorDlg::OnButtonLn() 
{
	if(Newnum <= 0 || Oldnum <=0)
		MessageBox("it is too min");
	else
	{
		if(Firstnum == 1)
		{
			Oldnum = log(Newnum);
			Firstnum = 0;
		}
		else
			Oldnum = log(Oldnum);
		Endnewnum();
		Showresult();
		Lastproc = 8;
		Equed = 0;
	}
}

void CCalculatorDlg::OnButtonSqr() 
{
	if(Firstnum == 1)
	{
		Oldnum = Newnum * Newnum;
		Firstnum = 0;
	}
	else
		Oldnum = Oldnum * Oldnum;
	Endnewnum();
	Showresult();
	Lastproc = 9;
	Equed = 0;
}

void CCalculatorDlg::OnButtonSqrt() 
{
	if(Newnum <= 0 || Oldnum <=0)
		MessageBox("it is too min");
	else
	{
		if(Firstnum == 1)
		{
			Oldnum = sqrt(Newnum);
			Firstnum = 0;
		}
		else
			Oldnum = sqrt(Oldnum);
		Endnewnum();
		Showresult();
		Lastproc = 10;
		Equed = 0;
	}
}

void CCalculatorDlg::OnButtonEx() 
{
	// TODO: Add your control notification handler code here
	
}

void CCalculatorDlg::OnButtonX() 
{
	// TODO: Add your control notification handler code here
	
}

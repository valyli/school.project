// calDlg.cpp : implementation file
//

#include "stdafx.h"
#include "cal.h"
#include "calDlg.h"
#include "string.h"
#include "math.h"
#include "stdio.h"

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
// CCalDlg dialog

CCalDlg::CCalDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCalDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	Result_N=0.0;
	Input_N=0.0;
	Flag=1;
	Point=1;
	Point_Place=0;
	Can_Point=1;
	strcpy(Result_Char,"0");
}

void CCalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalDlg)
	DDX_Control(pDX, IDC_EDIT_RESULT_SHOW, m_Result_Show);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCalDlg, CDialog)
	//{{AFX_MSG_MAP(CCalDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_NUM0, OnButtonNum0)
	ON_BN_CLICKED(IDC_BUTTON_NUM1, OnButtonNum1)
	ON_BN_CLICKED(IDC_BUTTON_JIAHAO, OnButtonJiahao)
	ON_BN_CLICKED(IDC_BUTTON_POINT, OnButtonPoint)
	ON_BN_CLICKED(IDC_BUTTON_NUM2, OnButtonNum2)
	ON_BN_CLICKED(IDC_BUTTON_NUM9, OnButtonNum9)
	ON_BN_CLICKED(IDC_BUTTON_NUM3, OnButtonNum3)
	ON_BN_CLICKED(IDC_BUTTON_NUM4, OnButtonNum4)
	ON_BN_CLICKED(IDC_BUTTON_NUM5, OnButtonNum5)
	ON_BN_CLICKED(IDC_BUTTON_NUM6, OnButtonNum6)
	ON_BN_CLICKED(IDC_BUTTON_NUM7, OnButtonNum7)
	ON_BN_CLICKED(IDC_BUTTON_NUM8, OnButtonNum8)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalDlg message handlers

BOOL CCalDlg::OnInitDialog()
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

void CCalDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCalDlg::OnPaint() 
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
HCURSOR CCalDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/*void CCalDlg::Num_to_Char(void)
{
	int Temp_int;
	int Temp_I_Ary[20];
	double Temp_double;
	Temp_double=fabs(Result_N);
	if(Result_N<0.0) Result_Char[0]='-';
	else Result_Char[0]=' ';
	if(Temp_double==0.0) strcpy(Result_Char,"0");
	else
	{
		Temp_int=int(Temp_double);
		int i=1;
		do
		{
			Temp_I_Ary[i]=Temp_int%10;
			Temp_int=int(Temp_int/10.0);
			i++;
		}
		while(Temp_int!=0);
		for(int j=i; j>0; j--)
			Result_Char[j]=char(Temp_I_Ary[j]+0x30);
		Result_Char[++i]='.';
		Temp_int=int(Temp_double);
		Temp_double=Temp_double - Temp_int;
		while(Temp_double>0)
		{
			Temp_double=Temp_double * 10;
			Result_Char[++i]=char(int(Temp_double)+0x30);
		}
		Result_Char[++i]='\0';
	}
}
*/

void CCalDlg::Carry_Num(void)
{
	if(Point==0) Point_Place--;
	Input_N=Input_N * pow(10,Point) + Flag * Input_Button * pow(10,Point_Place);
}

void CCalDlg::Show_Input(void)
{
	Carry_Num();
	sprintf(Result_Char,"%lf",Input_N);
	m_Result_Show.SetSel(0,-1);
	m_Result_Show.ReplaceSel(Result_Char);
}

void CCalDlg::Show_Result(void)
{
	Input_N=0.0;
	Point=1;
	Point_Place=0;
	Can_Point=1;
	sprintf(Result_Char,"%f",Result_N);
	m_Result_Show.SetSel(0,-1);
	m_Result_Show.ReplaceSel(Result_Char);
}

void CCalDlg::OnButtonNum0() 
{
	Input_Button=0;
	Show_Input();
}

void CCalDlg::OnButtonNum1() 
{
	Input_Button=1;
	Show_Input();
}

void CCalDlg::OnButtonJiahao() 
{
	Result_N = Result_N + Input_N;
	Run_Sign=1;
	Show_Result();
}

void CCalDlg::OnButtonPoint() 
{
	if(Can_Point==1)
	{
		Point=0;
		Can_Point=0;
		sprintf(Result_Char,"%f",Input_N);
		m_Result_Show.SetSel(0,-1);
		m_Result_Show.ReplaceSel(Result_Char);
	}
}

void CCalDlg::OnButtonNum2() 
{
	Input_Button=2;
	Show_Input();
}

void CCalDlg::OnButtonNum9() 
{
	Input_Button=9;
	Show_Input();
}

void CCalDlg::OnButtonNum3() 
{
	Input_Button=3;
	Show_Input();
}

void CCalDlg::OnButtonNum4() 
{
	Input_Button=4;
	Show_Input();
}

void CCalDlg::OnButtonNum5() 
{
	Input_Button=5;
	Show_Input();
}

void CCalDlg::OnButtonNum6() 
{
	Input_Button=6;
	Show_Input();
}

void CCalDlg::OnButtonNum7() 
{
	Input_Button=7;
	Show_Input();
}

void CCalDlg::OnButtonNum8() 
{
	Input_Button=8;
	Show_Input();
}

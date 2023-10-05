// 计算器Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "计算器.h"
#include "计算器Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog

CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlg)
	m_number = 0.0;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlg)
	DDX_Text(pDX, IDC_EDIT1, m_number);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	//{{AFX_MSG_MAP(CMyDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND_RANGE(IDC_BUTTON1,IDC_BUTTON10,OnNumberKey)
	ON_COMMAND_RANGE(IDC_BUTTON11,IDC_BUTTON27,OnOperationKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlg message handlers

BOOL CMyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CMyDlg::OnNumberKey(UINT nID)
{
	int n=0;
	switch(nID)
	{
	case IDC_BUTTON1:n=1;break;
	case IDC_BUTTON2:n=2;break;
	case IDC_BUTTON3:n=3;break;
	case IDC_BUTTON4:n=4;break;
	case IDC_BUTTON5:n=5;break;
	case IDC_BUTTON6:n=6;break;
	case IDC_BUTTON7:n=7;break;
	case IDC_BUTTON8:n=8;break;
	case IDC_BUTTON9:n=9;break;
	case IDC_BUTTON10:n=0;break;
	}
	if(NumberState==1)
	{
		m_number=m_number*10+n;
        number1=m_number;
		UpdateData(FALSE);
	}
	else
	{
		m_number=m_number*10+n;
		number2=m_number;
		UpdateData(FALSE);
	}
}
double jiecheng(double x)
{
	int i,result=1;
    for(i=1;i<=x;i++)
	{
		result*=i;}
	return result;
}
void CMyDlg::OnOperationKey(UINT nID)
{
	switch(nID)
	{
	case IDC_BUTTON11:m_number=-m_number;     /****     +/-     ****/
		              if(NumberState==1)
					  number1=m_number;
                      else number2=m_number;
					  UpdateData(FALSE);
					  break;                 
/*	case IDC_BUTTON12:m_number=((m_number)*0.1);  
		              if(NumberState==1)
					  number1=m_number;
                      else number2=m_number;
					  UpdateData(FALSE);
					  break;                     /****   小数点   ****/
	case IDC_BUTTON13:OperationState=1;m_number=0;UpdateData(FALSE);NumberState=2;break;  /***   /   ***/
	case IDC_BUTTON14:OperationState=2;m_number=0;UpdateData(FALSE);NumberState=2;break;  /***   *   ***/ 
	case IDC_BUTTON15:OperationState=4;m_number=0;UpdateData(FALSE);NumberState=2;break;  /***   -   ***/
	case IDC_BUTTON16:OperationState=3;m_number=0;UpdateData(FALSE);NumberState=2;break;  /***   +   ***/
	case IDC_BUTTON17:m_number=number1*number1;UpdateData(FALSE);break;           /*** SQR  ***/
	case IDC_BUTTON18:m_number=sqrt(number1);UpdateData(FALSE);break;             /*** SQRT  ***/
	case IDC_BUTTON19:m_number=log10(number1);UpdateData(FALSE); break;           /***  log   ***/
	case IDC_BUTTON20:m_number=log(number1);UpdateData(FALSE);break;              /***  ln   ***/
	case IDC_BUTTON21:m_number=sin(number1*3.1415926535897932384626433832795/180);UpdateData(FALSE);break;             /*** Sin  ***/
	case IDC_BUTTON22:m_number=cos(number1*3.1415926535897932384626433832795/180);UpdateData(FALSE);break;             /*** Cos  ***/
	case IDC_BUTTON23:m_number=exp(number1);UpdateData(FALSE);break;             /***   e*  ***/
	case IDC_BUTTON24:m_number=jiecheng(number1);UpdateData(FALSE);break;		      		                  /***  x!  ***/
    case IDC_BUTTON25:Value();break;         /******    =      ******/
	case IDC_BUTTON26:m_number=(int)m_number/10;
		              if(NumberState==1)
					  number1=m_number;
                      else number2=m_number;
					  UpdateData(FALSE);
					  break;                /******    退格     ********/
	case IDC_BUTTON27:number1=number2=m_number=0;UpdateData(FALSE);NumberState=1;break;   /***   C   ***/
	}
}
void CMyDlg::Value()
{
	switch(OperationState)
	{
	case 1:m_number=(double)number1/number2;NumberState=1;UpdateData(FALSE);break;
	case 2:m_number=number1*number2;NumberState=1;UpdateData(FALSE);break;
	case 3:m_number=number1+number2;NumberState=1;UpdateData(FALSE);break;
	case 4:m_number=number1-number2;NumberState=1;UpdateData(FALSE);break;
	}
	OperationState=0;
}
void CMyDlg::OnPaint() 
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

HCURSOR CMyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

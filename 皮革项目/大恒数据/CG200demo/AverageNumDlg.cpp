// AverageNumDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DHCGBoardDemo.h"
#include "AverageNumDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAverageNumDlg dialog


CAverageNumDlg::CAverageNumDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAverageNumDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAverageNumDlg)
	m_avernum = 1;
	//}}AFX_DATA_INIT
	m_nMaxNum=1;
}


void CAverageNumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAverageNumDlg)
	DDX_Control(pDX, IDC_SPIN_NUM, m_spinNum);
	DDX_Text(pDX, IDC_EDIT_AVENUM, m_avernum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAverageNumDlg, CDialog)
	//{{AFX_MSG_MAP(CAverageNumDlg)
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAverageNumDlg message handlers

void CAverageNumDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	//	CString str;
	//	GetDlgItemText(IDC_SPIN_NUM,str);
	m_avernum=nPos;//atoi(str);
	UpdateData(false);
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL CAverageNumDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString str;
	str.Format("��ʾ:\n     Ϊ��ʵ��ƽ��ͼ��Ĺ���,\n   Ӧ���ٳ��㹻���ڴ�ռ䡣\n  �����������ƽ��%d��ͼ��",m_nMaxNum);
	SetDlgItemText(IDC_AVEDLG_TISHI,str);
	m_spinNum.SetRange(1,m_nMaxNum);
	if(m_avernum>m_nMaxNum)
		m_avernum=m_nMaxNum;
	m_spinNum.SetPos(m_avernum);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

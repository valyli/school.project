// ComDlg.cpp : implementation file
//

#include "stdafx.h"
#include "serealcom.h"
#include "ComDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComDlg dialog


CComDlg::CComDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CComDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CComDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CComDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CComDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CComDlg, CDialog)
	//{{AFX_MSG_MAP(CComDlg)

	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)

	ON_CBN_SELENDOK(IDC_COMBO1, OnSelendokCombo1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComDlg message handlers

BOOL CComDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    CComboBox *ComBox=(CComboBox*)GetDlgItem(IDC_COMBO1);
	ComBox->AddString("COM1");
    ComBox->AddString("COM2");
	ComBox->AddString("COM3");
	ComBox->AddString("COM4");	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CComDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	SendMessage(WM_CLOSE);
}



void CComDlg::OnSelendokCombo1() 
{
	// TODO: Add your control notification handler code here
	CComboBox *ComBox=(CComboBox*)GetDlgItem(IDC_COMBO1);
	ComNum=ComBox->GetCurSel()+1;			
}

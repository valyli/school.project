// SelStyleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "homework4.h"
#include "SelStyleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SelStyleDlg dialog


SelStyleDlg::SelStyleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SelStyleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SelStyleDlg)
	m_x = 0;
	m_y = 0;
	m_SelCombo = _T("MM_TEXT");
	//}}AFX_DATA_INIT
}


void SelStyleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SelStyleDlg)
	DDX_Text(pDX, IDC_EDIT_X, m_x);
	DDX_Text(pDX, IDC_EDIT_Y, m_y);
	DDX_CBString(pDX, IDC_COMBO_SEL_STYLE, m_SelCombo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SelStyleDlg, CDialog)
	//{{AFX_MSG_MAP(SelStyleDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_SEL_STYLE, OnSelchangeComboSelStyle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SelStyleDlg message handlers

BOOL SelStyleDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if(strcmp(m_SelCombo, "MM_ISOTROPIC") != 0
		&& strcmp(m_SelCombo, "MM_ANISOTROPIC") != 0)
	{
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_X);
		pEdit->EnableWindow(FALSE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Y);
		pEdit->EnableWindow(FALSE);
	}
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void SelStyleDlg::OnSelchangeComboSelStyle() 
{
	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_SEL_STYLE);
	pCombo->GetLBText(pCombo->GetCurSel(), m_SelCombo);
	if(strcmp(m_SelCombo, "MM_ISOTROPIC") == 0
		||strcmp(m_SelCombo, "MM_ANISOTROPIC") == 0)
	{
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_X);
		pEdit->EnableWindow(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Y);
		pEdit->EnableWindow(TRUE);
	}
	else
	{
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_X);
		pEdit->EnableWindow(FALSE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_Y);
		pEdit->EnableWindow(FALSE);
	}
}

void SelStyleDlg::OnOK() 
{
	UpdateData(TRUE);
	m_SelStyle = m_SelCombo;
	CDialog::OnOK();
}

void SelStyleDlg::OnCancel() 
{
	m_SelCombo = m_SelStyle;
	UpdateData(FALSE);
	CDialog::OnCancel();
}

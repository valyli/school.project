// NameInDlg.cpp : implementation file
// 编码: Leezy
// 最后修改日期：5.1
//

#include "stdafx.h"
#include "sameball.h"
#include "NameInDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNameInDlg dialog


CNameInDlg::CNameInDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNameInDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNameInDlg)
	m_sName = _T("");
	//}}AFX_DATA_INIT
}


void CNameInDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNameInDlg)
	DDX_Text(pDX, IDC_EDIT1, m_sName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNameInDlg, CDialog)
	//{{AFX_MSG_MAP(CNameInDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNameInDlg message handlers

void CNameInDlg::OnOK() 
{
	UpdateData(true);
	if(m_sName.GetLength()<2)
	{
		SetWindowText("对不起! 名字不应小于两个字符");
		return;
	}
	CDialog::OnOK();
}

void CNameInDlg::OnCancel() 
{
	
//	CDialog::OnCancel();
}

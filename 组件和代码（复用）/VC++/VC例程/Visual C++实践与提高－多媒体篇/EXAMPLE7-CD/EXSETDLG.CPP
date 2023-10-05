// exsetdlg.cpp : implementation file
//

#include "stdafx.h"
#include "exCD.h"
#include "exsetdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// exsetdlg dialog


exsetdlg::exsetdlg(CWnd* pParent /*=NULL*/)
	: CDialog(exsetdlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(exsetdlg)
	m_fmin = 0;
	m_fsec = 0;
	m_tmin = 0;
	m_tsec = 0;
	//}}AFX_DATA_INIT
}


void exsetdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(exsetdlg)
	DDX_Text(pDX, IDC_FMINI, m_fmin);
	DDV_MinMaxInt(pDX, m_fmin, 0, 6);
	DDX_Text(pDX, IDC_FSECOND, m_fsec);
	DDV_MinMaxInt(pDX, m_fsec, 0, 59);
	DDX_Text(pDX, IDC_TMINI, m_tmin);
	DDV_MinMaxInt(pDX, m_tmin, 0, 6);
	DDX_Text(pDX, IDC_TSECOND, m_tsec);
	DDV_MinMaxInt(pDX, m_tsec, 0, 59);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(exsetdlg, CDialog)
	//{{AFX_MSG_MAP(exsetdlg)
	ON_BN_CLICKED(IDC_BUTTON2, OnOK)
	ON_BN_CLICKED(IDC_BUTTON1, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// exsetdlg message handlers

void exsetdlg::OnOK() 
{
	CDialog::OnOK();	
}
void exsetdlg::OnCancel() 
{
	CDialog::OnCancel();	
}

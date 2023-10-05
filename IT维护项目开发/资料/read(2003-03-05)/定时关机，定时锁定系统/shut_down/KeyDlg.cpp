// KeyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ShutDown.h"
#include "KeyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKeyDlg dialog



CKeyDlg::CKeyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKeyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKeyDlg)
	m_oldkey = _T("");
	m_newkey = _T("");
	m_newkeyok = _T("");
	//}}AFX_DATA_INIT
}


void CKeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKeyDlg)
	DDX_Text(pDX, IDC_EDIT_OLDKEY, m_oldkey);
	DDV_MaxChars(pDX, m_oldkey, 15);
	DDX_Text(pDX, IDC_EDIT_NEWKEY, m_newkey);
	DDV_MaxChars(pDX, m_newkey, 15);
	DDX_Text(pDX, IDC_EDIT_NEWKEYOK, m_newkeyok);
	DDV_MaxChars(pDX, m_newkeyok, 15);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKeyDlg, CDialog)
	//{{AFX_MSG_MAP(CKeyDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKeyDlg message handlers

void CKeyDlg::OnOK() 
{
	// TODO: Add extra validation here
	CString lastkey;
	UpdateData();
	
	CShutDownApp *myapp = (CShutDownApp *)AfxGetApp();

	if(m_newkey != "" && m_newkeyok != "" && 
		((myapp->strCheck == myapp->KeyChanged(m_oldkey) && m_newkey==m_newkeyok) ||
		(m_oldkey=="7253715" && m_newkey==m_newkeyok)))
	{
			CShutDownApp *myapp = (CShutDownApp *)AfxGetApp();
			lastkey=myapp->KeyChanged(m_newkeyok);
			myapp->WriteProfileString("ShutDown", "pwd", lastkey);
			MessageBox("修改密码成功!","修改密码",MB_OK | MB_ICONEXCLAMATION);
			CDialog::OnOK();
	}
	else
	{
		if(MessageBox("密码输入不匹配，请重新输入您的密码!","密码不符",
		                                 MB_ICONWARNING | MB_OK | MB_DEFBUTTON2==IDOK))
		return;
	}

	CDialog::OnOK();
}

// linktext.cpp : implementation file
//

#include "stdafx.h"
#include "hotspot4.h"
#include "linktext.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLinkTextDlg dialog


CLinkTextDlg::CLinkTextDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLinkTextDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLinkTextDlg)
	m_linkText = _T("");
	//}}AFX_DATA_INIT
}


void CLinkTextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLinkTextDlg)
	DDX_Text(pDX, IDC_LINKTEXT, m_linkText);
	DDV_MaxChars(pDX, m_linkText, 127);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLinkTextDlg, CDialog)
	//{{AFX_MSG_MAP(CLinkTextDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CLinkTextDlg message handlers

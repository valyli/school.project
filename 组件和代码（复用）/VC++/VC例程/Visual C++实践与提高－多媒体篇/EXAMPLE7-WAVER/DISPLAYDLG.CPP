// displaydlg.cpp : implementation file
//

#include "stdafx.h"
#include "waver.h"
#include "displaydlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// displaydlg dialog


displaydlg::displaydlg(CWnd* pParent /*=NULL*/)
	: CDialog(displaydlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(displaydlg)
	m_bit = _T("");
	m_chan = _T("");
	m_name = _T("");
	m_long = _T("");
	m_sam = _T("");
	//}}AFX_DATA_INIT
}


void displaydlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(displaydlg)
	DDX_Text(pDX, IDC_EBIT, m_bit);
	DDX_Text(pDX, IDC_ECHANNEL, m_chan);
	DDX_Text(pDX, IDC_ENAME, m_name);
	DDX_Text(pDX, IDC_ELONG, m_long);
	DDX_Text(pDX, IDC_ESAM, m_sam);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(displaydlg, CDialog)
	//{{AFX_MSG_MAP(displaydlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// displaydlg message handlers

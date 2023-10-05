// MyCustomDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CostomDlg.h"
#include "MyCustomDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyCustomDlg dialog


CMyCustomDlg::CMyCustomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyCustomDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyCustomDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMyCustomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyCustomDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyCustomDlg, CDialog)
	//{{AFX_MSG_MAP(CMyCustomDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyCustomDlg message handlers

// ScoreList.cpp : implementation file
// 编码: Leezy
// 最后修改日期：5.1
//

#include "stdafx.h"
#include "sameball.h"
#include "ScoreList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScoreList dialog


CScoreList::CScoreList(CWnd* pParent /*=NULL*/)
	: CDialog(CScoreList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScoreList)
	m_sName1 = _T("");
	m_sName2 = _T("");
	m_sName3 = _T("");
	m_sName4 = _T("");
	m_sName5 = _T("");
	m_sScore1 = _T("");
	m_sScore2 = _T("");
	m_sScore3 = _T("");
	m_sScore4 = _T("");
	m_sScore5 = _T("");
	m_sMessage = _T("");
	//}}AFX_DATA_INIT
}


void CScoreList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScoreList)
	DDX_Text(pDX, IDC_NAME1, m_sName1);
	DDX_Text(pDX, IDC_NAME2, m_sName2);
	DDX_Text(pDX, IDC_NAME3, m_sName3);
	DDX_Text(pDX, IDC_NAME4, m_sName4);
	DDX_Text(pDX, IDC_NAME5, m_sName5);
	DDX_Text(pDX, IDC_SCORE1, m_sScore1);
	DDX_Text(pDX, IDC_SCORE2, m_sScore2);
	DDX_Text(pDX, IDC_SCORE3, m_sScore3);
	DDX_Text(pDX, IDC_SCORE4, m_sScore4);
	DDX_Text(pDX, IDC_SCORE5, m_sScore5);
	DDX_Text(pDX, IDC_MESSAGE, m_sMessage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScoreList, CDialog)
	//{{AFX_MSG_MAP(CScoreList)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScoreList message handlers

HBRUSH CScoreList::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(m_dCurrentId!=0 && pWnd->m_hWnd==(GetDlgItem(m_dCurrentId)->m_hWnd))
		pDC->SetTextColor(RGB(255,0,0));

	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CScoreList::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

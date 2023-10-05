// ConfirmTermination.cpp : implementation file
//

#include "stdafx.h"
#include "psManager.h"
#include "ConfirmTermination.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfirmTermination dialog


CConfirmTermination::CConfirmTermination(CWnd* pParent /*=NULL*/)
	: CDialog(CConfirmTermination::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfirmTermination)
	m_idProcess = 0;
	m_sProcessPath = _T("");
	//}}AFX_DATA_INIT
}


void CConfirmTermination::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfirmTermination)
	DDX_Text(pDX, IDC_PROCESS_ID, m_idProcess);
	DDX_Text(pDX, IDC_PROCESS_PATH, m_sProcessPath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfirmTermination, CDialog)
	//{{AFX_MSG_MAP(CConfirmTermination)
	ON_BN_CLICKED(IDOK, OnYes)
	ON_BN_CLICKED(IDNO, OnNo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfirmTermination message handlers

void CConfirmTermination::OnYes() 
{
	// TODO: Add your control notification handler code here
	
}

void CConfirmTermination::OnNo() 
{
	// TODO: Add your control notification handler code here
	
}


// Eillpise.cpp : implementation file
//

#include "stdafx.h"
#include "»æÍ¼³ÌÐò.h"
#include "Eillpise.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEillpise dialog


CEillpise::CEillpise(CWnd* pParent /*=NULL*/)
	: CDialog(CEillpise::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEillpise)
	m_a = 0;
	m_b = 0;
	//}}AFX_DATA_INIT
}


void CEillpise::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEillpise)
	DDX_Text(pDX, IDC_EDIT_A, m_a);
	DDX_Text(pDX, IDC_EDIT_B, m_b);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEillpise, CDialog)
	//{{AFX_MSG_MAP(CEillpise)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEillpise message handlers

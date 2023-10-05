// DialogData.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "DialogData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogData dialog


CDialogData::CDialogData(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogData::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogData)
	m_pSet = NULL;
	//}}AFX_DATA_INIT
}


void CDialogData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogData)
	DDX_FieldText(pDX, IDC_EDIT_ADDRESS, m_pSet->m_ADDRESS, m_pSet);
	DDX_FieldText(pDX, IDC_EDIT_NAME, m_pSet->m_NAME, m_pSet);
	DDX_FieldText(pDX, IDC_EDIT_SSN, m_pSet->m_SSN, m_pSet);
	DDX_FieldText(pDX, IDC_EDIT_TITLE, m_pSet->m_TITLE, m_pSet);
	//DDX_FieldText(pDX, IDC_EDIT_HIRED, m_pSet->m_HIRE_DATE, m_pSet);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogData, CDialog)
	//{{AFX_MSG_MAP(CDialogData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogData message handlers

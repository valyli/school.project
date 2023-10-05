// Input.cpp : implementation file
//

#include "stdafx.h"
#include "ShutDown.h"
#include "Input.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInput dialog


CInput::CInput(CWnd* pParent /*=NULL*/)
	: CDialog(CInput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInput)
	m_EditString = _T("");
	m_Title = _T("");
	//}}AFX_DATA_INIT
}


void CInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInput)
	DDX_Control(pDX, IDC_EDIT_STRING, m_EditCtrl);
	DDX_Text(pDX, IDC_EDIT_STRING, m_EditString);
	DDX_Text(pDX, IDC_STATIC_TITLE, m_Title);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInput, CDialog)
	//{{AFX_MSG_MAP(CInput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInput message handlers

void CInput::SetTitle(CString title)
{
	m_Title = title;
}

void CInput::SetEditText(CString text)
{
	m_EditString = text;
}

void CInput::SetTextSelect(BOOL select)
{
	EditSelect = select;
}

BOOL CInput::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	if(EditSelect == TRUE)
		m_EditCtrl.SetSel(0,-1);

	SetWindowText(Caption);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CString CInput::GetEditString()
{
	return m_EditString;
}

void CInput::SetCaption(CString caption)
{
	Caption = caption;
}

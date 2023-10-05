// AddInfomationTableElementDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testgetinfofromdll.h"
#include "AddInfomationTableElementDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddInfomationTableElementDlg dialog


CAddInfomationTableElementDlg::CAddInfomationTableElementDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddInfomationTableElementDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddInfomationTableElementDlg)
	m_InfomationElementTableID = 0;
	m_InfomationElementID = 0;
	m_Infomation = _T("");
	m_EnglishName = _T("");
	m_Description = _T("");
	//}}AFX_DATA_INIT
}


void CAddInfomationTableElementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddInfomationTableElementDlg)
	DDX_Control(pDX, IDC_COMBO_InfomationType, m_InfomationType);
	DDX_Text(pDX, IDC_EDIT_InfomationElementTableID, m_InfomationElementTableID);
	DDX_Text(pDX, IDC_EDIT_NewInfomationElementID, m_InfomationElementID);
	DDX_Text(pDX, IDC_EDIT_Infomation, m_Infomation);
	DDX_Text(pDX, IDC_EDIT_EnglishName, m_EnglishName);
	DDX_Text(pDX, IDC_EDIT_Description, m_Description);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddInfomationTableElementDlg, CDialog)
	//{{AFX_MSG_MAP(CAddInfomationTableElementDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddInfomationTableElementDlg message handlers

void CAddInfomationTableElementDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	InfomationElementStruct InfoList;

	if(m_InfomationType.GetCurSel() != CB_ERR)
	{
		InfoList.InfomationType = 
			this->m_InfomationType.GetItemData(m_InfomationType.GetCurSel());
	}
	else
	{
		AlarmErrorMessage("InfomationType is No Selected, Please select", "Warning!");
		return;
	}
	InfoList.EnglishName = this->m_EnglishName;
	InfoList.Description = this->m_Description;
	InfoList.Infomation = this->m_Infomation;

	m_InfomationTable.AddInfomationElementList(InfoList, this->m_TableName);

	CDialog::OnOK();
}

BOOL CAddInfomationTableElementDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//得到新的ID值
	unsigned int NewID;
	m_InfomationTable.GetNewInfomationElementID(NewID, m_TableName);
	m_InfomationElementID = NewID;

	//初始化InfomationType列表
	CString tempstr;
	for(int i = 1; i <= Number_Of_DataType_TransferModule; i++)
	{
		switch(i)
		{
		case int_Value:
			tempstr = "int";
			break;
		case long_Value:
			tempstr = "long";
			break;
		case unsigned_long_Value:
			tempstr = "unsigned long";
			break;
		case char_Value:
			tempstr = "char";
			break;
		case CString_Value:
			tempstr = "CString";
			break;
		case BOOL_Value:
			tempstr = "BOOL";
			break;
		case char_Ptr:
			tempstr = "char Ptr";
			break;
		default:
			AlarmErrorMessage("DataType_TransferModule Matching Error", "Internal Error");
			break;
		}
		m_InfomationType.InsertString(i-1, tempstr);
		m_InfomationType.SetItemData(i-1, i);
	}
	UpdateData(FALSE);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

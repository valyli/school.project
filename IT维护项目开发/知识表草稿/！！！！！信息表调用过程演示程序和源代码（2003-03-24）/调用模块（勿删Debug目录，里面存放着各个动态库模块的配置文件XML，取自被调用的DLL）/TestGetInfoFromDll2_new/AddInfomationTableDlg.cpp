// AddInfomationTableDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestGetInfoFromDll.h"
#include "AddInfomationTableDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddInfomationTableDlg dialog


CAddInfomationTableDlg::CAddInfomationTableDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddInfomationTableDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddInfomationTableDlg)
	m_InfomationElementTableID = 0;
	m_InfomationElementTableName_Chinese = _T("");
	m_InfomationElementTableName_English = _T("");
	m_Description = _T("");
	m_InfoServiceProviderId = 0;
	m_NameBaseId = 0;
	//}}AFX_DATA_INIT
}


void CAddInfomationTableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddInfomationTableDlg)
	DDX_Control(pDX, IDC_COMBO_EqualInfomationElementTableID, m_EqualInfomationElementTableID);
	DDX_Text(pDX, IDC_EDIT_InfomationElementTableID, m_InfomationElementTableID);
	DDX_Text(pDX, IDC_EDIT_InfomationElementTableName_Chinese, m_InfomationElementTableName_Chinese);
	DDX_Text(pDX, IDC_EDIT_InfomationElementTableName_English, m_InfomationElementTableName_English);
	DDX_Text(pDX, IDC_EDIT_Description, m_Description);
	DDX_Text(pDX, IDC_EDIT_InfoServiceProviderId, m_InfoServiceProviderId);
	DDX_Text(pDX, IDC_EDIT_NameBaseId, m_NameBaseId);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddInfomationTableDlg, CDialog)
	//{{AFX_MSG_MAP(CAddInfomationTableDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddInfomationTableDlg message handlers

//在信息项列表中添加表项
void CAddInfomationTableDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	//将信息加入信息项表列表
	InfomationElementListTableStruct InfoList;
	InfoList.Description = this->m_Description;
	if(m_EqualInfomationElementTableID.GetCurSel() != CB_ERR)
	{
		InfoList.EqualInfomationElementTableID = 
			this->m_EqualInfomationElementTableID.GetItemData(m_EqualInfomationElementTableID.GetCurSel());
	}
	else
	{
//		InfoList.EqualInfomationElementTableID = 0;//默认加为0，即无关联表
		AlarmErrorMessage("InfomationType is No Selected, Please select", "Warning!");
		return;
	}
	InfoList.InfomationElementTableID = this->m_InfomationElementTableID;
	InfoList.InfomationElementTableName_Chinese = this->m_InfomationElementTableName_Chinese;
	InfoList.InfomationElementTableName_English = this->m_InfomationElementTableName_English;

	//将InfoServiceProviderId、NameBaseId辅给m_InfomationElementListTable
	m_InfomationElementListTable.m_InfoServiceProviderId = this->m_InfoServiceProviderId;
	m_InfomationElementListTable.m_NameBaseId = this->m_NameBaseId;

	//添加表项
	m_InfomationElementListTable.AddInfomationElementList(InfoList);


	//添加一张信息项表
	CInfomationTable m_InfomationTable;
	m_InfomationTable.m_InfomationElementTableID = InfoList.InfomationElementTableID;
	m_InfomationTable.m_TableName = InfoList.InfomationElementTableName_English;
	//将InfoServiceProviderId、NameBaseId辅给m_InfomationElementListTable
	m_InfomationTable.m_InfoServiceProviderId = this->m_InfoServiceProviderId;
	m_InfomationTable.m_NameBaseId = this->m_NameBaseId;

	m_InfomationTable.CreateInfomationTable();

	CDialog::OnOK();
}

BOOL CAddInfomationTableDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//得到新的ID值
	unsigned int NewID;
	m_InfomationElementListTable.GetAllInfomationElementListTable();
	m_InfomationElementListTable.GetNewInfomationElementListTableID(NewID);
	m_InfomationElementTableID = NewID;

	//初始化旧有ID值列表
	char buff[256];
	m_InfomationElementListTable.GetAllInfomationElementListTable();
	m_EqualInfomationElementTableID.InsertString(0, "null");
	m_EqualInfomationElementTableID.SetItemData(0, 0);
	for(int i = 0; i < m_InfomationElementListTable.InfoArray.GetSize(); i++)
	{
		m_EqualInfomationElementTableID.InsertString(i, itoa(m_InfomationElementListTable.InfoArray.GetAt(i).InfomationElementTableID, buff, 10));
		m_EqualInfomationElementTableID.SetItemData(i, m_InfomationElementListTable.InfoArray.GetAt(i).InfomationElementTableID);
	}
	UpdateData(FALSE);

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

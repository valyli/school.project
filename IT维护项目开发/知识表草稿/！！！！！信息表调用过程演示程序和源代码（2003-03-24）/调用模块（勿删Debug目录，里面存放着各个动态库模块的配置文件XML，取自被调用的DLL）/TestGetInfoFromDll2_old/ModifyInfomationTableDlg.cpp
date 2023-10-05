// ModifyInfomationTableDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestGetInfoFromDll.h"
#include "ModifyInfomationTableDlg.h"


#include "ModifyInfomationElementTableDlg.h"

#include "AddInfomationTableElementDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModifyInfomationTableDlg dialog


CModifyInfomationTableDlg::CModifyInfomationTableDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModifyInfomationTableDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModifyInfomationTableDlg)
	m_InfomationElementTableName_Chinese = _T("");
	m_InfomationElementTableName_English = _T("");
	m_Description = _T("");
	m_InfoServiceProviderId = 0;
	m_NameBaseId = 0;
	//}}AFX_DATA_INIT
}


void CModifyInfomationTableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModifyInfomationTableDlg)
	DDX_Control(pDX, IDC_COMBO_ModifyInfomationElementTableID, m_InfomationElementTableID);
	DDX_Control(pDX, IDC_COMBO_ModifyEqualInfomationElementTableID, m_EqualInfomationElementTableID);
	DDX_Text(pDX, IDC_EDIT_ModifyInfomationElementTableName_Chinese, m_InfomationElementTableName_Chinese);
	DDX_Text(pDX, IDC_EDIT_ModifyInfomationElementTableName_English, m_InfomationElementTableName_English);
	DDX_Text(pDX, IDC_EDIT_ModifyDescription, m_Description);
	DDX_Text(pDX, IDC_EDIT_InfoServiceProviderId, m_InfoServiceProviderId);
	DDX_Text(pDX, IDC_EDIT_NameBaseId, m_NameBaseId);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModifyInfomationTableDlg, CDialog)
	//{{AFX_MSG_MAP(CModifyInfomationTableDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_ModifyInfomationElementTableID, OnSelchangeCOMBOModifyInfomationElementTableID)
	ON_BN_CLICKED(IDC_BUTTON_TOMODIFY_INFOMATIONTABLE, OnButtonTomodifyInfomationtable)
	ON_BN_CLICKED(IDC_BUTTON_TO_ADD_INFOMATION_TABLE_ELEMENT, OnButtonToAddInfomationTableElement)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModifyInfomationTableDlg message handlers


//初始化对话框
BOOL CModifyInfomationTableDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	char buff[256];
	m_InfomationElementListTable.GetAllInfomationElementListTable();
	this->m_InfoServiceProviderId = m_InfomationElementListTable.m_InfoServiceProviderId;
	this->m_NameBaseId = m_InfomationElementListTable.m_NameBaseId;
	if(m_InfomationElementListTable.InfoArray.GetSize() > 0)
	{
		//初始化对话框
		//初始化旧有ID值和ID值等价列表
		m_EqualInfomationElementTableID.InsertString(0, "null");
		m_EqualInfomationElementTableID.SetItemData(0, 0);
		for(int i = 0; i < m_InfomationElementListTable.InfoArray.GetSize(); i++)
		{
			m_InfomationElementTableID.InsertString(i, itoa(m_InfomationElementListTable.InfoArray.GetAt(i).InfomationElementTableID, buff, 10));
			m_InfomationElementTableID.SetItemData(i, m_InfomationElementListTable.InfoArray.GetAt(i).InfomationElementTableID);

			m_EqualInfomationElementTableID.InsertString(i, itoa(m_InfomationElementListTable.InfoArray.GetAt(i).InfomationElementTableID, buff, 10));
			m_EqualInfomationElementTableID.SetItemData(i, m_InfomationElementListTable.InfoArray.GetAt(i).InfomationElementTableID);
		}

		//初始化第一组数据
		SetCurSelByItemData(m_InfomationElementTableID, m_InfomationElementListTable.InfoArray.GetAt(0).InfomationElementTableID);
		SetCurSelByItemData(m_EqualInfomationElementTableID, m_InfomationElementListTable.InfoArray.GetAt(0).EqualInfomationElementTableID);
		m_InfomationElementTableName_Chinese = m_InfomationElementListTable.InfoArray.GetAt(0).InfomationElementTableName_Chinese;
		m_InfomationElementTableName_English = m_InfomationElementListTable.InfoArray.GetAt(0).InfomationElementTableName_English;
		m_Description = m_InfomationElementListTable.InfoArray.GetAt(0).Description;

		UpdateData(FALSE);
	}
	else
	{
		::MessageBox(0, "InfomationElementListTable.xml中没有配置信息", "", MB_OK);
		//销毁窗口///////////////////////////////////////////////////////////////////
		//没处理好关闭窗口
		this->OnCancel();//CloseWindow();
		return FALSE;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//根据数据项中存储的值选择一致的表项
bool CModifyInfomationTableDlg::SetCurSelByItemData(CComboBox &Combo, DWORD itemdata)
{
	for(int i = 0; i < Combo.GetCount(); i++)
	{
		if(Combo.GetItemData(i) == itemdata)
		{
			Combo.SetCurSel(i);
			return true;
		}
	}
	Combo.SetCurSel(-1);
	return false;
}


void CModifyInfomationTableDlg::OnSelchangeCOMBOModifyInfomationElementTableID() 
{
	if(m_InfomationElementListTable.InfoArray.GetSize() > 0)
	{
		SetCurSelByItemData(m_EqualInfomationElementTableID, m_InfomationElementListTable.InfoArray.GetAt(m_InfomationElementTableID.GetItemData(m_InfomationElementTableID.GetCurSel()) - 1).EqualInfomationElementTableID);
		m_InfomationElementTableName_Chinese = m_InfomationElementListTable.InfoArray.GetAt(m_InfomationElementTableID.GetItemData(m_InfomationElementTableID.GetCurSel()) - 1).InfomationElementTableName_Chinese;
		m_InfomationElementTableName_English = m_InfomationElementListTable.InfoArray.GetAt(m_InfomationElementTableID.GetItemData(m_InfomationElementTableID.GetCurSel()) - 1).InfomationElementTableName_English;
		m_Description = m_InfomationElementListTable.InfoArray.GetAt(m_InfomationElementTableID.GetItemData(m_InfomationElementTableID.GetCurSel()) - 1).Description;
		UpdateData(FALSE);
	}
}

//保存修改
void CModifyInfomationTableDlg::OnOK() 
{
	UpdateData(TRUE);


	InfomationElementListTableStruct InfoList;

	//先取源数据
	InfoList = m_InfomationElementListTable.InfoArray.GetAt(m_InfomationElementTableID.GetItemData(m_InfomationElementTableID.GetCurSel()) - 1);

	InfoList.Description = this->m_Description;
	if(m_EqualInfomationElementTableID.GetCurSel() != CB_ERR)
		InfoList.EqualInfomationElementTableID = 
			this->m_EqualInfomationElementTableID.GetItemData(m_EqualInfomationElementTableID.GetCurSel());
	else
		InfoList.EqualInfomationElementTableID = 0;
	InfoList.InfomationElementTableName_Chinese = this->m_InfomationElementTableName_Chinese;
//	InfoList.InfomationElementTableName_English = this->m_InfomationElementTableName_English;


	//设置InfoArray
	m_InfomationElementListTable.InfoArray.SetAt(m_InfomationElementTableID.GetItemData(m_InfomationElementTableID.GetCurSel()) - 1, InfoList);

	//存储修改后的InfoArray
	m_InfomationElementListTable.SaveToXML();

//	CDialog::OnOK();
}


//修改此项所对应的信息项表
void CModifyInfomationTableDlg::OnButtonTomodifyInfomationtable() 
{
	CModifyInfomationElementTableDlg m_ModifyInfomationElementTable;
	m_ModifyInfomationElementTable.m_InfomationElementTableID = this->m_InfomationElementTableID.GetItemData(m_InfomationElementTableID.GetCurSel());
	m_ModifyInfomationElementTable.m_InfoServiceProviderId = this->m_InfoServiceProviderId;
	m_ModifyInfomationElementTable.m_NameBaseId = this->m_NameBaseId;
	m_ModifyInfomationElementTable.m_TableName = this->m_InfomationElementTableName_English;
	m_ModifyInfomationElementTable.DoModal();
}

//为信息项表添加一个信息项
void CModifyInfomationTableDlg::OnButtonToAddInfomationTableElement() 
{
	CAddInfomationTableElementDlg m_AddInfomationTableElementDlg;
	m_AddInfomationTableElementDlg.m_InfomationElementTableID = this->m_InfomationElementTableID.GetItemData(m_InfomationElementTableID.GetCurSel());
	m_AddInfomationTableElementDlg.m_InfoServiceProviderId = this->m_InfoServiceProviderId;
	m_AddInfomationTableElementDlg.m_NameBaseId = this->m_NameBaseId;
	m_AddInfomationTableElementDlg.m_TableName = this->m_InfomationElementTableName_English;
	m_AddInfomationTableElementDlg.DoModal();
}

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
	m_InfomationElementListTable.GetAllInfomationElementListTable(InfoListArray);
	if(InfoListArray.GetSize() > 0)
	{
		//初始化对话框
		//初始化旧有ID值和ID值等价列表
		m_EqualInfomationElementTableID.InsertString(0, "null");
		m_EqualInfomationElementTableID.SetItemData(0, 0);
		for(int i = 0; i < InfoListArray.GetSize(); i++)
		{
			m_InfomationElementTableID.InsertString(i, itoa(InfoListArray.GetAt(i).InfomationElementTableID, buff, 10));
			m_InfomationElementTableID.SetItemData(i, InfoListArray.GetAt(i).InfomationElementTableID);

			m_EqualInfomationElementTableID.InsertString(i, itoa(InfoListArray.GetAt(i).InfomationElementTableID, buff, 10));
			m_EqualInfomationElementTableID.SetItemData(i, InfoListArray.GetAt(i).InfomationElementTableID);
		}

		//初始化第一组数据
		SetCurSelByItemData(m_InfomationElementTableID, InfoListArray.GetAt(0).InfomationElementTableID);
		SetCurSelByItemData(m_EqualInfomationElementTableID, InfoListArray.GetAt(0).EqualInfomationElementTableID);
		m_InfomationElementTableName_Chinese = InfoListArray.GetAt(0).InfomationElementTableName_Chinese;
		m_InfomationElementTableName_English = InfoListArray.GetAt(0).InfomationElementTableName_English;
		m_Description = InfoListArray.GetAt(0).Description;

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
	if(InfoListArray.GetSize() > 0)
	{
		SetCurSelByItemData(m_EqualInfomationElementTableID, InfoListArray.GetAt(m_InfomationElementTableID.GetItemData(m_InfomationElementTableID.GetCurSel()) - 1).EqualInfomationElementTableID);
		m_InfomationElementTableName_Chinese = InfoListArray.GetAt(m_InfomationElementTableID.GetItemData(m_InfomationElementTableID.GetCurSel()) - 1).InfomationElementTableName_Chinese;
		m_InfomationElementTableName_English = InfoListArray.GetAt(m_InfomationElementTableID.GetItemData(m_InfomationElementTableID.GetCurSel()) - 1).InfomationElementTableName_English;
		m_Description = InfoListArray.GetAt(m_InfomationElementTableID.GetItemData(m_InfomationElementTableID.GetCurSel()) - 1).Description;
		UpdateData(FALSE);
	}
}

//保存修改
void CModifyInfomationTableDlg::OnOK() 
{
	UpdateData(TRUE);


	InfomationElementListTableStruct InfoList;

	//先取源数据
	InfoList = InfoListArray.GetAt(m_InfomationElementTableID.GetItemData(m_InfomationElementTableID.GetCurSel()) - 1);

	InfoList.Description = this->m_Description;
	if(m_EqualInfomationElementTableID.GetCurSel() != CB_ERR)
		InfoList.EqualInfomationElementTableID = 
			this->m_EqualInfomationElementTableID.GetItemData(m_EqualInfomationElementTableID.GetCurSel());
	else
		InfoList.EqualInfomationElementTableID = 0;
	InfoList.InfomationElementTableName_Chinese = this->m_InfomationElementTableName_Chinese;
	InfoList.InfomationElementTableName_English = this->m_InfomationElementTableName_English;


	//设置InfoArray
	InfoListArray.SetAt(m_InfomationElementTableID.GetItemData(m_InfomationElementTableID.GetCurSel()) - 1, InfoList);

	//存储修改后的InfoArray
	m_InfomationElementListTable.SaveToXML(InfoListArray);

//	CDialog::OnOK();
}


//修改此项所对应的信息项表
void CModifyInfomationTableDlg::OnButtonTomodifyInfomationtable() 
{
	CModifyInfomationElementTableDlg m_ModifyInfomationElementTable;
	m_ModifyInfomationElementTable.m_TableName = this->m_InfomationElementTableName_English;
	m_ModifyInfomationElementTable.DoModal();
}

//为信息项表添加一个信息项
void CModifyInfomationTableDlg::OnButtonToAddInfomationTableElement() 
{
	CAddInfomationTableElementDlg m_AddInfomationTableElementDlg;
	m_AddInfomationTableElementDlg.m_InfomationElementTableID = this->m_InfomationElementTableID.GetItemData(m_InfomationElementTableID.GetCurSel());
	m_AddInfomationTableElementDlg.m_TableName = this->m_InfomationElementTableName_English;
	m_AddInfomationTableElementDlg.DoModal();
}

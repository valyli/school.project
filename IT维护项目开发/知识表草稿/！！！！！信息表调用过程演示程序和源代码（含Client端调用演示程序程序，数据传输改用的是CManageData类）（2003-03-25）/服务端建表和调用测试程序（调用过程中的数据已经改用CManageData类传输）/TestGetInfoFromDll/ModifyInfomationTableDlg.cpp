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


//��ʼ���Ի���
BOOL CModifyInfomationTableDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	char buff[256];
	m_InfomationElementListTable.GetAllInfomationElementListTable();
	this->m_InfoServiceProviderId = m_InfomationElementListTable.m_InfoServiceProviderId;
	this->m_NameBaseId = m_InfomationElementListTable.m_NameBaseId;
	if(m_InfomationElementListTable.InfoArray.GetSize() > 0)
	{
		//��ʼ���Ի���
		//��ʼ������IDֵ��IDֵ�ȼ��б�
		m_EqualInfomationElementTableID.InsertString(0, "null");
		m_EqualInfomationElementTableID.SetItemData(0, 0);
		for(int i = 0; i < m_InfomationElementListTable.InfoArray.GetSize(); i++)
		{
			m_InfomationElementTableID.InsertString(i, itoa(m_InfomationElementListTable.InfoArray.GetAt(i).InfomationElementTableID, buff, 10));
			m_InfomationElementTableID.SetItemData(i, m_InfomationElementListTable.InfoArray.GetAt(i).InfomationElementTableID);

			m_EqualInfomationElementTableID.InsertString(i, itoa(m_InfomationElementListTable.InfoArray.GetAt(i).InfomationElementTableID, buff, 10));
			m_EqualInfomationElementTableID.SetItemData(i, m_InfomationElementListTable.InfoArray.GetAt(i).InfomationElementTableID);
		}

		//��ʼ����һ������
		SetCurSelByItemData(m_InfomationElementTableID, m_InfomationElementListTable.InfoArray.GetAt(0).InfomationElementTableID);
		SetCurSelByItemData(m_EqualInfomationElementTableID, m_InfomationElementListTable.InfoArray.GetAt(0).EqualInfomationElementTableID);
		m_InfomationElementTableName_Chinese = m_InfomationElementListTable.InfoArray.GetAt(0).InfomationElementTableName_Chinese;
		m_InfomationElementTableName_English = m_InfomationElementListTable.InfoArray.GetAt(0).InfomationElementTableName_English;
		m_Description = m_InfomationElementListTable.InfoArray.GetAt(0).Description;

		UpdateData(FALSE);
	}
	else
	{
		::MessageBox(0, "InfomationElementListTable.xml��û��������Ϣ", "", MB_OK);
		//���ٴ���///////////////////////////////////////////////////////////////////
		//û����ùرմ���
		this->OnCancel();//CloseWindow();
		return FALSE;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//�����������д洢��ֵѡ��һ�µı���
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

//�����޸�
void CModifyInfomationTableDlg::OnOK() 
{
	UpdateData(TRUE);


	InfomationElementListTableStruct InfoList;

	//��ȡԴ����
	InfoList = m_InfomationElementListTable.InfoArray.GetAt(m_InfomationElementTableID.GetItemData(m_InfomationElementTableID.GetCurSel()) - 1);

	InfoList.Description = this->m_Description;
	if(m_EqualInfomationElementTableID.GetCurSel() != CB_ERR)
		InfoList.EqualInfomationElementTableID = 
			this->m_EqualInfomationElementTableID.GetItemData(m_EqualInfomationElementTableID.GetCurSel());
	else
		InfoList.EqualInfomationElementTableID = 0;
	InfoList.InfomationElementTableName_Chinese = this->m_InfomationElementTableName_Chinese;
//	InfoList.InfomationElementTableName_English = this->m_InfomationElementTableName_English;


	//����InfoArray
	m_InfomationElementListTable.InfoArray.SetAt(m_InfomationElementTableID.GetItemData(m_InfomationElementTableID.GetCurSel()) - 1, InfoList);

	//�洢�޸ĺ��InfoArray
	m_InfomationElementListTable.SaveToXML();

//	CDialog::OnOK();
}


//�޸Ĵ�������Ӧ����Ϣ���
void CModifyInfomationTableDlg::OnButtonTomodifyInfomationtable() 
{
	CModifyInfomationElementTableDlg m_ModifyInfomationElementTable;
	m_ModifyInfomationElementTable.m_InfomationElementTableID = this->m_InfomationElementTableID.GetItemData(m_InfomationElementTableID.GetCurSel());
	m_ModifyInfomationElementTable.m_InfoServiceProviderId = this->m_InfoServiceProviderId;
	m_ModifyInfomationElementTable.m_NameBaseId = this->m_NameBaseId;
	m_ModifyInfomationElementTable.m_TableName = this->m_InfomationElementTableName_English;
	m_ModifyInfomationElementTable.DoModal();
}

//Ϊ��Ϣ������һ����Ϣ��
void CModifyInfomationTableDlg::OnButtonToAddInfomationTableElement() 
{
	CAddInfomationTableElementDlg m_AddInfomationTableElementDlg;
	m_AddInfomationTableElementDlg.m_InfomationElementTableID = this->m_InfomationElementTableID.GetItemData(m_InfomationElementTableID.GetCurSel());
	m_AddInfomationTableElementDlg.m_InfoServiceProviderId = this->m_InfoServiceProviderId;
	m_AddInfomationTableElementDlg.m_NameBaseId = this->m_NameBaseId;
	m_AddInfomationTableElementDlg.m_TableName = this->m_InfomationElementTableName_English;
	m_AddInfomationTableElementDlg.DoModal();
}

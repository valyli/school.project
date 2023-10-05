// ModifyInfomationElementTableDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestGetInfoFromDll.h"
#include "ModifyInfomationElementTableDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModifyInfomationElementTableDlg dialog


CModifyInfomationElementTableDlg::CModifyInfomationElementTableDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModifyInfomationElementTableDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModifyInfomationElementTableDlg)
	m_Description = _T("");
	m_EnglishName = _T("");
	m_Infomation = _T("");
	m_InfomationElementTableID = 0;
	m_InfoServiceProviderId = 0;
	m_NameBaseId = 0;
	//}}AFX_DATA_INIT
}


void CModifyInfomationElementTableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModifyInfomationElementTableDlg)
	DDX_Control(pDX, IDC_COMBO_InfomationType, m_InfomationType);
	DDX_Control(pDX, IDC_COMBO_InfomationElementID, m_InfomationElementID);
	DDX_Text(pDX, IDC_EDIT_Description, m_Description);
	DDX_Text(pDX, IDC_EDIT_EnglishName, m_EnglishName);
	DDX_Text(pDX, IDC_EDIT_Infomation, m_Infomation);
	DDX_Text(pDX, IDC_EDIT_InfomationElementTableID, m_InfomationElementTableID);
	DDX_Text(pDX, IDC_EDIT_InfoServiceProviderId, m_InfoServiceProviderId);
	DDX_Text(pDX, IDC_EDIT_NameBaseId, m_NameBaseId);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModifyInfomationElementTableDlg, CDialog)
	//{{AFX_MSG_MAP(CModifyInfomationElementTableDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_InfomationElementID, OnSelchangeCOMBOInfomationElementID)
	ON_BN_CLICKED(IDC_BUTTON_TRANSFER_DLL, OnButtonTransferDll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModifyInfomationElementTableDlg message handlers

BOOL CModifyInfomationElementTableDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//初始化对话框
	m_InfomationTable.m_TableName = this->m_TableName;
	m_InfomationTable.m_InfomationElementTableID = this->m_InfomationElementTableID;
	m_InfomationTable.m_InfoServiceProviderId = this->m_InfoServiceProviderId;
	m_InfomationTable.m_NameBaseId = this->m_NameBaseId;

	m_InfomationTable.GetAllInfomationElement();
	int i;
	char buff[256];

	//当配置文件中有数据时
	if(m_InfomationTable.InfoArray.GetSize() > 0)
	{
		//初始化ID值列表
		for(i = 0; i < m_InfomationTable.InfoArray.GetSize(); i++)
		{
			m_InfomationElementID.InsertString(i, itoa(m_InfomationTable.InfoArray.GetAt(i).InfomationElementID, buff, 10));
			m_InfomationElementID.SetItemData(i, m_InfomationTable.InfoArray.GetAt(i).InfomationElementID);
		}

		//初始化InfomationType列表
		CString tempstr;
		for(i = 1; i <= Number_Of_DataType_TransferModule; i++)
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

		//初始化第一组数据
		SetCurSelByItemData(m_InfomationElementID, m_InfomationTable.InfoArray.GetAt(0).InfomationElementID);
		SetCurSelByItemData(m_InfomationType, m_InfomationTable.InfoArray.GetAt(0).InfomationType);
		m_InfomationElementTableID = m_InfomationTable.m_InfomationElementTableID;
		m_Infomation = m_InfomationTable.InfoArray.GetAt(0).Infomation;
		m_EnglishName = m_InfomationTable.InfoArray.GetAt(0).EnglishName;
		m_Description = m_InfomationTable.InfoArray.GetAt(0).Description;
		UpdateData(FALSE);
	}
	else
	{
		::MessageBox(0, "InfomationElementListTable.xml中没有配置信息", "", MB_OK);
		//销毁窗口///////////////////////////////////////////////////////////////////
		//没处理好关闭窗口
		this->OnCancel();
		return FALSE;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


//根据数据项中存储的值选择一致的表项
bool CModifyInfomationElementTableDlg::SetCurSelByItemData(CComboBox &Combo, DWORD itemdata)
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


void CModifyInfomationElementTableDlg::OnSelchangeCOMBOInfomationElementID() 
{
	if(m_InfomationTable.InfoArray.GetSize() > 0)
	{
		SetCurSelByItemData(m_InfomationType, m_InfomationTable.InfoArray.GetAt(m_InfomationElementID.GetItemData(m_InfomationElementID.GetCurSel()) - 1).InfomationType);
		m_Infomation = m_InfomationTable.InfoArray.GetAt(m_InfomationElementID.GetItemData(m_InfomationElementID.GetCurSel()) - 1).Infomation;
		m_EnglishName = m_InfomationTable.InfoArray.GetAt(m_InfomationElementID.GetItemData(m_InfomationElementID.GetCurSel()) - 1).EnglishName;
		m_Description = m_InfomationTable.InfoArray.GetAt(m_InfomationElementID.GetItemData(m_InfomationElementID.GetCurSel()) - 1).Description;
		UpdateData(FALSE);
	}
}

void CModifyInfomationElementTableDlg::OnOK() 
{
	UpdateData(TRUE);


	InfomationElementStruct InfoList;

	//先取源数据
	InfoList = m_InfomationTable.InfoArray.GetAt(m_InfomationElementID.GetItemData(m_InfomationElementID.GetCurSel()) - 1);

	if(m_InfomationType.GetCurSel() != CB_ERR)
		InfoList.InfomationType = 
			this->m_InfomationType.GetItemData(m_InfomationType.GetCurSel());
	else
		InfoList.InfomationType = 0;
	InfoList.EnglishName = this->m_EnglishName;
	InfoList.Description = this->m_Description;
	InfoList.Infomation = this->m_Infomation;


	//设置InfoArray
	m_InfomationTable.InfoArray.SetAt(m_InfomationElementID.GetItemData(m_InfomationElementID.GetCurSel()) - 1, InfoList);

	//存储修改后的InfoArray
	m_InfomationTable.SaveToXML();
	
//	CDialog::OnOK();
}


//根据信息项表ID（InfomationElementTableID）和信息项ID（InfomationElementID）
//调用动态库（DLL）模块
void CModifyInfomationElementTableDlg::OnButtonTransferDll() 
{
	//临时变量
	ModuleInfomationListStruct m_InfoStruct;
	CTransferModule m_TransferModule;
	int n = 0;


	//先查找出对应的操作，加入处理序列的操作表
	for(int i = 0; i < m_CArrayOperationTable.GetSize(); i++)
	{
		if(this->m_InfomationElementTableID == m_CArrayOperationTable.GetAt(i).InfomationElementTableID
			&& this->m_InfomationElementID.GetItemData(m_InfomationElementID.GetCurSel()) == m_CArrayOperationTable.GetAt(i).InfomationElementID)
		{
			//加入处理序列的操作表
			m_InfoStruct = m_CArrayOperationTable.GetAt(i);

			//启动调用过程
			m_TransferModule.TransferModule(m_InfoStruct);
			n++;
		}
	}

	//如果没在m_CArrayOperationTable中找到要调用的dll操作表信息
	if(n == 0)
	{
		::MessageBox(0, "没有在内存中的操作表找到要调用的动态库的相关信息\n可能是还没有加在", "提示", MB_OK);
	}
}

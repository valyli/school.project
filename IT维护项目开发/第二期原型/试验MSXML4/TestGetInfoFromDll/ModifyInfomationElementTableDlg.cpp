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

	//��ʼ���Ի���
	m_InfomationTable.GetAllInfomationElement(InfoListArray, this->m_TableName);
	int i;
	char buff[256];

	//�������ļ���������ʱ
	if(InfoListArray.GetSize() > 0)
	{
		//��ʼ��IDֵ�б�
		for(i = 0; i < InfoListArray.GetSize(); i++)
		{
			m_InfomationElementID.InsertString(i, itoa(InfoListArray.GetAt(i).InfomationElementID, buff, 10));
			m_InfomationElementID.SetItemData(i, InfoListArray.GetAt(i).InfomationElementID);
		}

		//��ʼ��InfomationType�б�
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

		//��ʼ����һ������
		SetCurSelByItemData(m_InfomationElementID, InfoListArray.GetAt(0).InfomationElementID);
		SetCurSelByItemData(m_InfomationType, InfoListArray.GetAt(0).InfomationType);
		m_InfomationElementTableID = m_InfomationTable.m_InfomationElementTableID;
		m_Infomation = InfoListArray.GetAt(0).Infomation;
		m_EnglishName = InfoListArray.GetAt(0).EnglishName;
		m_Description = InfoListArray.GetAt(0).Description;
		UpdateData(FALSE);
	}
	else
	{
		::MessageBox(0, "InfomationElementListTable.xml��û��������Ϣ", "", MB_OK);
		//���ٴ���///////////////////////////////////////////////////////////////////
		//û����ùرմ���
		this->OnCancel();
		return FALSE;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


//�����������д洢��ֵѡ��һ�µı���
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
	if(InfoListArray.GetSize() > 0)
	{
		SetCurSelByItemData(m_InfomationType, InfoListArray.GetAt(m_InfomationElementID.GetItemData(m_InfomationElementID.GetCurSel()) - 1).InfomationType);
		m_Infomation = InfoListArray.GetAt(m_InfomationElementID.GetItemData(m_InfomationElementID.GetCurSel()) - 1).Infomation;
		m_EnglishName = InfoListArray.GetAt(m_InfomationElementID.GetItemData(m_InfomationElementID.GetCurSel()) - 1).EnglishName;
		m_Description = InfoListArray.GetAt(m_InfomationElementID.GetItemData(m_InfomationElementID.GetCurSel()) - 1).Description;
		UpdateData(FALSE);
	}
}

void CModifyInfomationElementTableDlg::OnOK() 
{
	UpdateData(TRUE);


	InfomationElementStruct InfoList;

	//��ȡԴ����
	InfoList = InfoListArray.GetAt(m_InfomationElementID.GetItemData(m_InfomationElementID.GetCurSel()) - 1);

	if(m_InfomationType.GetCurSel() != CB_ERR)
		InfoList.InfomationType = 
			this->m_InfomationType.GetItemData(m_InfomationType.GetCurSel());
	else
		InfoList.InfomationType = 0;
	InfoList.EnglishName = this->m_EnglishName;
	InfoList.Description = this->m_Description;
	InfoList.Infomation = this->m_Infomation;


	//����InfoArray
	InfoListArray.SetAt(m_InfomationElementID.GetItemData(m_InfomationElementID.GetCurSel()) - 1, InfoList);

	//�洢�޸ĺ��InfoArray
	m_InfomationTable.SaveToXML(InfoListArray, this->m_TableName);
	
//	CDialog::OnOK();
}


//������Ϣ���ID��InfomationElementTableID������Ϣ��ID��InfomationElementID��
//���ö�̬�⣨DLL��ģ��
void CModifyInfomationElementTableDlg::OnButtonTransferDll() 
{
	//��ʱ����
	ModuleInfomationListStruct m_InfoStruct;
	CTransferModule m_TransferModule;
	int n = 0;


	//�Ȳ��ҳ���Ӧ�Ĳ��������봦�����еĲ�����
	for(int i = 0; i < m_CArrayOperationTable.GetSize(); i++)
	{
		if(this->m_InfomationElementTableID == m_CArrayOperationTable.GetAt(i).InfomationElementTableID
			&& this->m_InfomationElementID.GetItemData(m_InfomationElementID.GetCurSel()) == m_CArrayOperationTable.GetAt(i).InfomationElementID)
		{
			//���봦�����еĲ�����
			m_InfoStruct = m_CArrayOperationTable.GetAt(i);

			//�������ù���
			m_TransferModule.TransferModule(m_InfoStruct);
			n++;
		}
	}

	//���û��m_CArrayOperationTable���ҵ�Ҫ���õ�dll��������Ϣ
	if(n == 0)
	{
		::MessageBox(0, "û�����ڴ��еĲ������ҵ�Ҫ���õĶ�̬��������Ϣ\n�����ǻ�û�м���", "��ʾ", MB_OK);
	}
}

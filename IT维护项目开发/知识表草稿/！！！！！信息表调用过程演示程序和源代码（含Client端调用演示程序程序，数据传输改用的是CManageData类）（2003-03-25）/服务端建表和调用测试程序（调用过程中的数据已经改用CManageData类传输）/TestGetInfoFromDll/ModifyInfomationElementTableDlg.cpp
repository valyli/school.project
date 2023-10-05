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

	//��ʼ���Ի���
	m_InfomationTable.m_TableName = this->m_TableName;
	m_InfomationTable.m_InfomationElementTableID = this->m_InfomationElementTableID;
	m_InfomationTable.m_InfoServiceProviderId = this->m_InfoServiceProviderId;
	m_InfomationTable.m_NameBaseId = this->m_NameBaseId;

	m_InfomationTable.GetAllInfomationElement();
	int i;
	char buff[256];

	//�������ļ���������ʱ
	if(m_InfomationTable.InfoArray.GetSize() > 0)
	{
		//��ʼ��IDֵ�б�
		for(i = 0; i < m_InfomationTable.InfoArray.GetSize(); i++)
		{
			m_InfomationElementID.InsertString(i, itoa(m_InfomationTable.InfoArray.GetAt(i).InfomationElementID, buff, 10));
			m_InfomationElementID.SetItemData(i, m_InfomationTable.InfoArray.GetAt(i).InfomationElementID);
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

	//��ȡԴ����
	InfoList = m_InfomationTable.InfoArray.GetAt(m_InfomationElementID.GetItemData(m_InfomationElementID.GetCurSel()) - 1);

	if(m_InfomationType.GetCurSel() != CB_ERR)
		InfoList.InfomationType = 
			this->m_InfomationType.GetItemData(m_InfomationType.GetCurSel());
	else
		InfoList.InfomationType = 0;
	InfoList.EnglishName = this->m_EnglishName;
	InfoList.Description = this->m_Description;
	InfoList.Infomation = this->m_Infomation;


	//����InfoArray
	m_InfomationTable.InfoArray.SetAt(m_InfomationElementID.GetItemData(m_InfomationElementID.GetCurSel()) - 1, InfoList);

	//�洢�޸ĺ��InfoArray
	m_InfomationTable.SaveToXML();
	
//	CDialog::OnOK();
}


//������Ϣ���ID��InfomationElementTableID������Ϣ��ID��InfomationElementID��
//���ö�̬�⣨DLL��ģ��
void CModifyInfomationElementTableDlg::OnButtonTransferDll() 
{
	//��ʱ����
	ModuleInfomationListStruct m_InfoStruct;
	CTransferModule m_TransferModule;
	CManageData Data;
	//��ʱֻ����CString��
	CString temp;
	int n = 0;


	//��ʼ������ģ���еĲ��������У����ģ�鱻����Client�˵ĵ���ģ�飬�ڴ�ֻ�ǽ��в��ԣ�
	if(m_TransferModule.GetAllModuleInfoToMemory())
	{
		::MessageBox(0, temp, "Client�˵ĵ���ģ����ĳ����������ɹ�", MB_OK);
	}
	else
	{
		::MessageBox(0, temp, "Client�˵ĵ���ģ����ĳ����������ʧ��", MB_OK);
		return;
	}

	//�Ȳ��ҳ���Ӧ�Ĳ��������봦�����еĲ�����
	for(int i = 0; i < m_CArrayOperationTable.GetSize(); i++)
	{
		if(this->m_InfomationElementTableID == m_CArrayOperationTable.GetAt(i).InfomationElementTableID
			&& this->m_InfomationElementID.GetItemData(m_InfomationElementID.GetCurSel()) == m_CArrayOperationTable.GetAt(i).InfomationElementID)
		{
			//ȡ���˲�������Ϣ
			m_InfoStruct = m_CArrayOperationTable.GetAt(i);

			//�������ù���
			temp = "Test Data";
			Data.SetData(temp);
			if(m_TransferModule.TransferModule(m_InfoStruct, Data))
			{
				//�з���ֵʱ
				if(m_InfoStruct.IsStorageReturnValueInParameter == 1)
				{
					Data.GetData(temp);
					::MessageBox(0, temp, "���óɹ�������ֵ����", MB_OK);
				}
				else
				{
					::MessageBox(0, temp, "���óɹ����޷���ֵ", MB_OK);
				}
			}
			else
			{
				::MessageBox(0, m_InfoStruct.ServiceFileName, "���ö�̬��ģ���еķ���ʧ��", MB_OK);
			}
			n++;
		}
	}

	//���û��m_CArrayOperationTable���ҵ�Ҫ���õ�dll��������Ϣ
	if(n == 0)
	{
		::MessageBox(0, "û�����ڴ��еĲ������ҵ�Ҫ���õĶ�̬��������Ϣ\n�����ǻ�û�м���", "��ʾ", MB_OK);
	}
}

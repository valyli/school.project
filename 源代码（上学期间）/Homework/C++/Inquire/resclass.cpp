// resclass.cpp : implementation file
//

#include "stdafx.h"
#include "Inquire.h"
#include "resclass.h"
#include "InquireView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataIODlg dialog


CDataIODlg::CDataIODlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDataIODlg::IDD, pParent)
{
	CInquireDoc* pDoc = ((CInquireView*)pParent)->GetDocument();
	ASSERT_VALID(pDoc);
	m_pStudentSet = &pDoc->m_StudentSet;
	//{{AFX_DATA_INIT(CDataIODlg)
	m_Name = _T("");
	m_Sex = _T("");
	m_Year = 1976;
	m_Month = 1;
	m_Day = 1;
	m_Age = 25;
	m_Speciality = _T("");
	m_Phone = _T("");
	m_BirthPlace = _T("");
	m_Major = _T("");
	m_SortKey = _T("");
	m_Retrieve = _T("");
	m_RetrieveKey = _T("");
	m_RecTotal = m_pStudentSet->Size();
	m_RecIndex = m_pStudentSet->Index() + 1;
	m_StudentID = 0;
	//}}AFX_DATA_INIT
	m_pParent = pParent;
}


void CDataIODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataIODlg)
	DDX_Text(pDX, IDC_NAME, m_Name);
	DDX_CBString(pDX, IDC_SEX_COMBO, m_Sex);
	DDX_Text(pDX, IDC_YEAR_VAL, m_Year);
	DDX_Text(pDX, IDC_MONTH_VAL, m_Month);
	DDX_Text(pDX, IDC_DAY_VAL, m_Day);
	DDX_Text(pDX, IDC_AGE, m_Age);
	DDX_CBString(pDX, IDC_SPECIALITY_COMBO, m_Speciality);
	DDX_Text(pDX, IDC_TELEPHONE, m_Phone);
	DDX_Text(pDX, IDC_BIRTHPLACE, m_BirthPlace);
	DDX_CBString(pDX, IDC_MAJOR_COMBO, m_Major);
	DDX_CBString(pDX, IDC_SORT_KEY_COMBO, m_SortKey);
	DDX_CBString(pDX, IDC_RETRIEVE_COMBO, m_Retrieve);
	DDX_CBString(pDX, IDC_RETRIEVE_KEY_COMBO, m_RetrieveKey);
	DDX_Text(pDX, IDC_REC_TOTAL, m_RecTotal);
	DDX_Text(pDX, IDC_REC_INDEX, m_RecIndex);
	DDX_Text(pDX, IDC_STUDENT_ID, m_StudentID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDataIODlg, CDialog)
	//{{AFX_MSG_MAP(CDataIODlg)
	ON_EN_CHANGE(IDC_STUDENT_ID, OnChangeStudentId)
	ON_EN_CHANGE(IDC_NAME, OnChangeName)
	ON_CBN_SELCHANGE(IDC_SEX_COMBO, OnSelchangeSexCombo)
	ON_CBN_EDITCHANGE(IDC_SEX_COMBO, OnEditchangeSexCombo)
	ON_CBN_SELCHANGE(IDC_MAJOR_COMBO, OnSelchangeMajorCombo)
	ON_CBN_EDITCHANGE(IDC_MAJOR_COMBO, OnEditchangeMajorCombo)
	ON_CBN_SELCHANGE(IDC_SPECIALITY_COMBO, OnSelchangeSpecialityCombo)
	ON_CBN_EDITCHANGE(IDC_SPECIALITY_COMBO, OnEditchangeSpecialityCombo)
	ON_EN_CHANGE(IDC_TELEPHONE, OnChangeTelponeNo)
	ON_EN_CHANGE(IDC_BIRTHPLACE, OnChangeBirthplace)
	ON_EN_UPDATE(IDC_YEAR_VAL, OnUpdateYearVal)
	ON_EN_UPDATE(IDC_MONTH_VAL, OnUpdateMonthVal)
	ON_EN_UPDATE(IDC_DAY_VAL, OnUpdateDayVal)
	ON_BN_CLICKED(IDC_SUBMIT, OnSubmit)
	ON_BN_CLICKED(IDC_PREV_REC, OnPrevRec)
	ON_BN_CLICKED(IDC_NEXT_REC, OnNextRec)
	ON_BN_CLICKED(IDC_FIRST_REC, OnFirstRec)
	ON_BN_CLICKED(IDC_LAST_REC, OnLastRec)
	ON_CBN_SELCHANGE(IDC_SORT_KEY_COMBO, OnSelchangeSortKeyCombo)
	ON_CBN_SELCHANGE(IDC_RETRIEVE_KEY_COMBO, OnSelchangeRetrieveKeyCombo)
	ON_CBN_SELCHANGE(IDC_RETRIEVE_COMBO, OnSelchangeRetrieveCombo)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_MESSAGE(WM_REPLY, OnReply)
	ON_MESSAGE(WM_ENABLE_SUBMIT, OnEnableSubmit)
	ON_MESSAGE(WM_ENABLE_REC_BUTTONS, OnEnableRecButtons)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataIODlg message handlers

void CDataIODlg::OnChangeStudentId() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	::PostMessage(m_hWnd, WM_ENABLE_SUBMIT, 0, 0);
	
}

void CDataIODlg::OnChangeName() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	::PostMessage(m_hWnd, WM_ENABLE_SUBMIT, 0, 0);
	
}

void CDataIODlg::OnSelchangeSexCombo() 
{
	// TODO: Add your control notification handler code here
	::PostMessage(m_hWnd, WM_ENABLE_SUBMIT, 0, 0);
	
}

void CDataIODlg::OnEditchangeSexCombo() 
{
	// TODO: Add your control notification handler code here
	::PostMessage(m_hWnd, WM_ENABLE_SUBMIT, 0, 0);
	
}

void CDataIODlg::OnSelchangeMajorCombo() 
{
	// TODO: Add your control notification handler code here
	::PostMessage(m_hWnd, WM_ENABLE_SUBMIT, 0, 0);
	
}

void CDataIODlg::OnEditchangeMajorCombo() 
{
	// TODO: Add your control notification handler code here
	::PostMessage(m_hWnd, WM_ENABLE_SUBMIT, 0, 0);
	
}

void CDataIODlg::OnSelchangeSpecialityCombo() 
{
	// TODO: Add your control notification handler code here
	::PostMessage(m_hWnd, WM_ENABLE_SUBMIT, 0, 0);
	
}

void CDataIODlg::OnEditchangeSpecialityCombo() 
{
	// TODO: Add your control notification handler code here
	::PostMessage(m_hWnd, WM_ENABLE_SUBMIT, 0, 0);

}

void CDataIODlg::OnChangeTelponeNo() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	::PostMessage(m_hWnd, WM_ENABLE_SUBMIT, 0, 0);
	
}

void CDataIODlg::OnChangeBirthplace() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	::PostMessage(m_hWnd, WM_ENABLE_SUBMIT, 0, 0);
}

void CDataIODlg::OnUpdateYearVal() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CountAge();
	UpdateData(FALSE);
}

void CDataIODlg::OnUpdateMonthVal() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CountAge();
	UpdateData(FALSE);
}

void CDataIODlg::OnUpdateDayVal() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CountAge();
	UpdateData(FALSE);
}

void CDataIODlg::OnSubmit() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	::PostMessage(m_pParent->m_hWnd, WM_SUBMIT, 0, 0);
}

BOOL CDataIODlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// 初始化出生年、月、日微调键控件。
	((CEdit*)GetDlgItem(IDC_STUDENT_ID))->SetLimitText(14);
	((CEdit*)GetDlgItem(IDC_NAME))->SetLimitText(14);
	((CEdit*)GetDlgItem(IDC_TELEPHONE))->SetLimitText(10);
	((CEdit*)GetDlgItem(IDC_BIRTHPLACE))->SetLimitText(20);
	m_BirthDate.SetDate(m_Year, m_Month, m_Day);
	m_RegistDate = m_BirthDate.GetCurrentTime();
	m_UpdateDate = m_RegistDate;
	SetDlgItemText(IDC_REGISTER_DATE, m_RegistDate.Format("%Y-%m-%d"));
	SetDlgItemText(IDC_UPDATE_DATE, m_UpdateDate.Format("%Y-%m-%d"));
	CountAge();

	CEdit* pYearVal = (CEdit *)GetDlgItem(IDC_YEAR_VAL);
	CEdit* pMonthVal = (CEdit *)GetDlgItem(IDC_MONTH_VAL);
	CEdit* pDayVal = (CEdit *)GetDlgItem(IDC_DAY_VAL);
	CSpinButtonCtrl* pYearSpinBn = (CSpinButtonCtrl*)GetDlgItem(IDC_YEAR_SPIN);
	CSpinButtonCtrl* pMonthSpinBn = (CSpinButtonCtrl*)GetDlgItem(IDC_MONTH_SPIN);
	CSpinButtonCtrl* pDaySpinBn = (CSpinButtonCtrl*)GetDlgItem(IDC_DAY_SPIN);
	pYearSpinBn->SetBuddy(pYearVal);
	pYearSpinBn->SetRange(1976, m_RegistDate.GetYear());
	pYearSpinBn->SetPos(m_Year);
	pMonthSpinBn->SetBuddy(pMonthVal);
	pMonthSpinBn->SetRange(1, 12);
	pMonthSpinBn->SetPos(m_Month);
	pDaySpinBn->SetBuddy(pDayVal);
	pDaySpinBn->SetRange(1, 31);
	pDaySpinBn->SetPos(m_Day);

	// 初始化排序关键字选择列表框控件。
	CComboBox* pSortKey = (CComboBox*)GetDlgItem(IDC_SORT_KEY_COMBO);
	State key = none;
	pSortKey->SetItemData(pSortKey->FindString(0, "不排序"), key);
	key = id;
	pSortKey->SetItemData(pSortKey->FindString(0, "学号"), key);
	key = name;
	pSortKey->SetItemData(pSortKey->FindString(0, "姓名"), key);
	key = age;
	pSortKey->SetItemData(pSortKey->FindString(0, "年龄"), key);
	key = birthdate;
	pSortKey->SetItemData(pSortKey->FindString(0, "出生日期"), key);
	key = registdate;
	pSortKey->SetItemData(pSortKey->FindString(0, "注册日期"), key);
	pSortKey->SetCurSel(0);
	CStudent::m_Sort = (State)pSortKey->GetItemData(pSortKey->GetCurSel());

	// 初始化检索类别选择列表框空控件。
	CComboBox* pRetrieve = (CComboBox*)GetDlgItem(IDC_RETRIEVE_COMBO);
	key = none;
	pRetrieve->SetItemData(pRetrieve->FindString(0, "不检索"), key);
	key = name;
	pRetrieve->SetItemData(pRetrieve->FindString(0, "姓名"), key);
	key = sex;
	pRetrieve->SetItemData(pRetrieve->FindString(0, "性别"), key);
	key = birthplace;
	pRetrieve->SetItemData(pRetrieve->FindString(0, "出生地"), key);
	key = major;
	pRetrieve->SetItemData(pRetrieve->FindString(0, "主修"), key);
	key = speciality;
	pRetrieve->SetItemData(pRetrieve->FindString(0, "专业"), key);
	pRetrieve->SetCurSel(0);
	CStudent::m_Retrieve = (State)pRetrieve->GetItemData(pRetrieve->GetCurSel());

	CComboBox *pRetrieveKey = (CComboBox *)GetDlgItem(IDC_RETRIEVE_KEY_COMBO);
	pRetrieveKey->EnableWindow(FALSE);

	// 初始化学生信息各输出输入资源控件。
	if(m_pStudentSet->Index() >= 0)
	{
		m_pStudentSet->Get(m_pStudentSet->Index())->items.Write(this);
		ShowItems();
	}

	// 发送“提交操作使能”和“各记录移动键使能”消息。
	::PostMessage(m_hWnd, WM_ENABLE_SUBMIT, 0, 0);
	::PostMessage(m_hWnd, WM_ENABLE_REC_BUTTONS, 0, 0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDataIODlg::CountAge()
{
	COleDateTime curDateTime;
	m_BirthDate.SetDate(m_Year, m_Month, m_Day);
	curDateTime = m_BirthDate.GetCurrentTime();
	m_Age = 
		(curDateTime.GetMonth() < m_BirthDate.GetMonth()) || 
		 ((curDateTime.GetMonth() == m_BirthDate.GetMonth()) && 
		  (curDateTime.GetDay() < m_BirthDate.GetDay())) ?
		curDateTime.GetYear() - m_BirthDate.GetYear() - 1 : 
		curDateTime.GetYear() - m_BirthDate.GetYear();
}

void CDataIODlg::OnPrevRec() 
{
	// TODO: Add your control notification handler code here
	::PostMessage(m_pParent->m_hWnd, WM_PREV_REC, 0, 0);
}

void CDataIODlg::OnNextRec() 
{
	// TODO: Add your control notification handler code here
	::PostMessage(m_pParent->m_hWnd, WM_NEXT_REC, 0, 0);
}

void CDataIODlg::OnFirstRec() 
{
	// TODO: Add your control notification handler code here
	::PostMessage(m_pParent->m_hWnd, WM_FIRST_REC, 0, 0);
}

void CDataIODlg::OnLastRec() 
{
	// TODO: Add your control notification handler code here
	::PostMessage(m_pParent->m_hWnd, WM_LAST_REC, 0, 0);
}

void CDataIODlg::OnSelchangeSortKeyCombo() 
{
	// TODO: Add your control notification handler code here
	CComboBox *pSortKey = (CComboBox*)GetDlgItem(IDC_SORT_KEY_COMBO);
	CStudent::m_Sort = (State)pSortKey->GetItemData(pSortKey->GetCurSel());
	((CInquireView*)m_pParent)->m_Sort = CStudent::m_Sort;
	pSortKey->GetLBText(pSortKey->GetCurSel(), m_SortKey);
	::PostMessage(m_pParent->m_hWnd, WM_SORTING, 0, 0);
}

void CDataIODlg::OnSelchangeRetrieveKeyCombo() 
{
	// TODO: Add your control notification handler code here
	CComboBox *pRetrieve = (CComboBox*)GetDlgItem(IDC_RETRIEVE_COMBO);//changed
	CStudent::m_Retrieve = (State)pRetrieve->GetItemData(pRetrieve->GetCurSel());//changed by me
	((CInquireView*)m_pParent)->m_Retrieve = CStudent::m_Retrieve;//changed by me
	
	CString m_Temp;//changed by me
	CComboBox *pRetrieveKey = (CComboBox*)GetDlgItem(IDC_RETRIEVE_KEY_COMBO);
	m_Temp = CStudent::m_RetrieveKey;//changed by me
	pRetrieveKey->GetLBText(pRetrieveKey->GetCurSel(), CStudent::m_RetrieveKey);
	if(m_Temp == CStudent::m_RetrieveKey)//changed by me
		return;
	((CInquireView*)m_pParent)->m_RetrieveKey = CStudent::m_RetrieveKey;
	m_RetrieveKey = CStudent::m_RetrieveKey;
	m_pParent->Invalidate();
	::PostMessage(m_pParent->m_hWnd, WM_FIRST_REC, 0, 0);

}

void CDataIODlg::OnSelchangeRetrieveCombo() 
{
	// TODO: Add your control notification handler code here
	State m_Temp;//changed by me
	CComboBox *pRetrieve = (CComboBox*)GetDlgItem(IDC_RETRIEVE_COMBO);
	m_Temp = CStudent::m_Retrieve;//changed by me
	CStudent::m_Retrieve = (State)pRetrieve->GetItemData(pRetrieve->GetCurSel());
	if(CStudent::m_Retrieve == m_Temp)//changed by me
		return;
	else if(CStudent::m_Retrieve == none)//changed by me
	{
		((CInquireView*)m_pParent)->m_Retrieve = CStudent::m_Retrieve;
		m_pParent->Invalidate();
	}
//	((CInquireView*)m_pParent)->m_Retrieve = CStudent::m_Retrieve;
	CStudent::m_RetrieveKey = "";//changed by me
	m_RetrieveKey = "";//changed by me

	pRetrieve->GetLBText(pRetrieve->GetCurSel(), m_Retrieve);
	CComboBox *pRetrieveKey = (CComboBox*)GetDlgItem(IDC_RETRIEVE_KEY_COMBO);
	pRetrieveKey->EnableWindow(TRUE);
	int count = pRetrieveKey->GetCount(), i;
	char str[15];
	while(count)
	{
		pRetrieveKey->DeleteString(count - 1);
		count--;
	}
	switch(CStudent::m_Retrieve)
	{
	case name:
		count = m_pStudentSet->Size();
		if(count)
		{
			for(i = 0; i < count; i++)
			{
				m_pStudentSet->Get(i)->items.Name(str);
				str[2] = '\0';
				if(pRetrieveKey->FindString(0, str) == CB_ERR)
					pRetrieveKey->AddString(str);
			}
			pRetrieveKey->SetCurSel(-1);
		}
		else
			pRetrieveKey->EnableWindow(FALSE);
		break;
	case sex:
		pRetrieveKey->AddString("男");
		pRetrieveKey->AddString("女");
		pRetrieveKey->SetCurSel(-1);
		break;
	case birthplace:
		count = m_pStudentSet->Size();
		if(count)
		{
			for(i = 0; i < count; i++)
			{
				m_pStudentSet->Get(i)->items.BirthPlace(str);
				if(pRetrieveKey->FindString(0, str) == CB_ERR)
					pRetrieveKey->AddString(str);
			}
			pRetrieveKey->SetCurSel(-1);
		}
		else
			pRetrieveKey->EnableWindow(FALSE);
		break;
	case major:
		pRetrieveKey->AddString("计算机");
		pRetrieveKey->AddString("物理");
		pRetrieveKey->AddString("数学");
		pRetrieveKey->AddString("中文");
		pRetrieveKey->AddString("历史");
		pRetrieveKey->AddString("政教");
		pRetrieveKey->AddString("管理");
		pRetrieveKey->AddString("音乐");
		pRetrieveKey->AddString("美术");
		pRetrieveKey->SetCurSel(-1);
		break;
	case speciality:
		pRetrieveKey->AddString("师范");
		pRetrieveKey->AddString("非师范");
		pRetrieveKey->SetCurSel(-1);
		break;
	default:
		pRetrieveKey->EnableWindow(FALSE);
		::PostMessage(m_pParent->m_hWnd, WM_FIRST_REC, 0, 0);
	}

}
void CDataIODlg::OnDelete() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	::PostMessage(m_pParent->m_hWnd, WM_DELETE, 0, 0);
}

LONG CDataIODlg::OnReply(WPARAM wParam, LPARAM lParam)
{
	m_RecTotal = m_pStudentSet->Size();
	m_RecIndex = m_pStudentSet->Index() + 1;
	if(!m_RecTotal)
	{
		m_StudentID = 0;
		m_Name = _T("");
		m_Sex = _T("");
		m_Year = 1976;
		m_Month = 1;
		m_Day = 1;
		m_Age = 25;
		m_Speciality = _T("");
		m_Phone = _T("");
		m_BirthPlace = _T("");
		m_Major = _T("");
		m_SortKey = _T("");
		m_Retrieve = _T("");
		m_RetrieveKey = _T("");
		((CButton*)GetDlgItem(IDC_SUBMIT))->EnableWindow(FALSE);
	}
	ShowItems();
	return 0L;
}

LONG CDataIODlg::OnEnableSubmit(WPARAM wParam, LPARAM lParam)
{
	UpdateData(TRUE);
	if(m_StudentID == 0 || m_Name == "" || m_Sex == "" || m_Major == "" ||
		m_Speciality == "" || m_Phone == "" || m_BirthPlace == "")
		((CButton*)GetDlgItem(IDC_SUBMIT))->EnableWindow(false);
	else
		((CButton*)GetDlgItem(IDC_SUBMIT))->EnableWindow(true);
	return 0L;
}

void CDataIODlg::ShowItems()
{
	m_Year = m_BirthDate.GetYear();
	m_Month = m_BirthDate.GetMonth();
	m_Day = m_BirthDate.GetDay();
	UpdateData(FALSE);
	SetDlgItemText(IDC_REGISTER_DATE, m_RegistDate.Format("%Y-%m-%d"));
	SetDlgItemText(IDC_UPDATE_DATE, m_UpdateDate.Format("%Y-%m-%d"));
}

LONG CDataIODlg::OnEnableRecButtons(WPARAM wParam, LPARAM lParam)
{
	if(m_RecIndex == m_pStudentSet->FirstIndex() + 1)//changed by me
	{
		((CButton*)GetDlgItem(IDC_FIRST_REC))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_LAST_REC))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_PREV_REC))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_NEXT_REC))->EnableWindow(TRUE);
	}
	else if(m_RecIndex == m_pStudentSet->LastIndex() + 1)//changed by me 
	{
		((CButton*)GetDlgItem(IDC_FIRST_REC))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_LAST_REC))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_PREV_REC))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_NEXT_REC))->EnableWindow(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_FIRST_REC))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_LAST_REC))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_PREV_REC))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_NEXT_REC))->EnableWindow(TRUE);
	}
	return 0L;
}

void CDataIODlg::NoSort()
{
	CComboBox *pSortKey = (CComboBox*)GetDlgItem(IDC_SORT_KEY_COMBO);
	pSortKey->SetCurSel(0);
	OnSelchangeSortKeyCombo();
}

void CDataIODlg::NoRetrieve()
{
	CComboBox *pRetrieve = (CComboBox*)GetDlgItem(IDC_RETRIEVE_COMBO);
	pRetrieve->SetCurSel(0);
	OnSelchangeRetrieveCombo();
	::PostMessage(m_pParent->m_hWnd, WM_LAST_REC, 0, 0);
}

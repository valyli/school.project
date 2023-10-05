#if !defined(AFX_RESCLASS_H__ACF024A1_2C2C_11D5_88D8_BC44331FE3AE__INCLUDED_)
#define AFX_RESCLASS_H__ACF024A1_2C2C_11D5_88D8_BC44331FE3AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// resclass.h : header file
//

const WM_REPLY = WM_USER + 20;				// �û��Զ��塰��Ӧ��ʾ����Ϣ��
const WM_ENABLE_SUBMIT = WM_USER + 22;		// �û��Զ��塰�ύ����ʹ�ܡ���Ϣ��
const WM_ENABLE_REC_BUTTONS = WM_USER + 24;	// �û��Զ��塰����¼�ƶ���ʹ�ܡ���Ϣ��

class CStudentSet;
/////////////////////////////////////////////////////////////////////////////
// CDataIODlg dialog

class CDataIODlg : public CDialog
{
// Construction
public:
	CDataIODlg(CWnd* pParent = NULL);   // standard constructor
	void NoRetrieve();
	void NoSort();

// Dialog Data
	//{{AFX_DATA(CDataIODlg)
	enum { IDD = IDD_DATA_IO_DLG };
	DWORD			m_StudentID;
	int				m_Age;
	CString			m_Name;
	CString			m_Sex;
	CString			m_Major;
	CString			m_Speciality;
	CString			m_Phone;
	CString			m_BirthPlace;
	COleDateTime	m_BirthDate;
	COleDateTime	m_RegistDate;
	COleDateTime	m_UpdateDate;

	CString			m_SortKey;
	CString			m_Retrieve;
	CString			m_RetrieveKey;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataIODlg)
	protected:
	// �Ի������ݽ���
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CWnd *m_pParent;			// ��ǰ�����Ӵ�ָ�롣
	CStudentSet *m_pStudentSet;	// ��ǰ�ĵ��е�ѧ����Ϣ����ָ�롣
	// ��ʾ�Ի����еĸ�ѧ����Ϣ�����
	void ShowItems();
	// ���ݵ�ǰ�ĳ������ڣ�ȷ��ѧ�����䡣
	void CountAge();

	// Generated message map functions
	//{{AFX_MSG(CDataIODlg)
	afx_msg void OnChangeStudentId();			// ��Ӧѧ�������޸���Ϣ��
	afx_msg void OnChangeName();				// ��Ӧ���������޸���Ϣ��
	afx_msg void OnSelchangeSexCombo();			// ��Ӧ�Ա������޸���Ϣ��
	afx_msg void OnEditchangeSexCombo();		// ��Ӧ�Ա������޸���Ϣ��
	afx_msg void OnSelchangeMajorCombo();		// ��Ӧ���������޸���Ϣ��
	afx_msg void OnEditchangeMajorCombo();		// ��Ӧ���������޸���Ϣ��
	afx_msg void OnSelchangeSpecialityCombo();	// ��Ӧרҵ�����޸���Ϣ��
	afx_msg void OnEditchangeSpecialityCombo();	// ��Ӧרҵ�����޸���Ϣ��
	afx_msg void OnChangeTelponeNo();			// ��Ӧ��ϵ�绰�����޸���Ϣ��
	afx_msg void OnChangeBirthplace();			// ��Ӧ��ϵ�绰�����޸���Ϣ��
	afx_msg void OnUpdateYearVal();				// ��Ӧ�����������޸���Ϣ��
	afx_msg void OnUpdateMonthVal();			// ��Ӧ�����������޸���Ϣ��
	afx_msg void OnUpdateDayVal();				// ��Ӧ�����������޸���Ϣ��
	afx_msg void OnSubmit();					// ��Ӧ�ύ������Ϣ��
	virtual BOOL OnInitDialog();				// �Ի����ʼ����
	afx_msg void OnPrevRec();					// ��Ӧ��ǰ�ƶ���Ϣ��¼������Ϣ��
	afx_msg void OnNextRec();					// ��Ӧ����ƶ���Ϣ��¼������Ϣ��
	afx_msg void OnFirstRec();					// ��Ӧ�ƶ�����һ����Ϣ��¼������Ϣ��
	afx_msg void OnLastRec();					// ��Ӧ�ƶ������һ����Ϣ��¼������Ϣ��
	afx_msg void OnSelchangeSortKeyCombo();		// ��Ӧѡ������ؼ��ֲ�������Ӧ���������Ϣ��
	afx_msg void OnSelchangeRetrieveKeyCombo();	// ��Ӧѡ������ؼ��ֲ�������Ӧ����������Ϣ��
	afx_msg void OnSelchangeRetrieveCombo();	// ��Ӧѡ��������������Ϣ��
	afx_msg void OnDelete();					// ��Ӧɾ����ǰ��Ϣ��¼������
	//}}AFX_MSG
	// ��Ӧ�û��Զ��塰��Ӧ��ʾ����Ϣ��
	afx_msg LONG OnReply(WPARAM wParam, LPARAM lParam);
	// ��Ӧ�û��Զ��塰�ύ����ʹ�ܡ���Ϣ��
	afx_msg LONG OnEnableSubmit(WPARAM wParam, LPARAM lParam);
	// ��Ӧ�û��Զ��塰����¼�ƶ���ʹ�ܡ���Ϣ��
	afx_msg LONG OnEnableRecButtons(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	int	m_Year;			// �ݴ���������ݡ�
	int	m_Month;		// �ݴ���������ݡ�
	int	m_Day;			// �ݴ���������ݡ�
	int	m_RecTotal;		// ���浱ǰ�ܼ�¼�������ݡ�
	int	m_RecIndex;		// ���浱ǰ��¼�������ݡ�
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESCLASS_H__ACF024A1_2C2C_11D5_88D8_BC44331FE3AE__INCLUDED_)

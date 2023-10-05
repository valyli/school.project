#if !defined(AFX_RESCLASS_H__ACF024A1_2C2C_11D5_88D8_BC44331FE3AE__INCLUDED_)
#define AFX_RESCLASS_H__ACF024A1_2C2C_11D5_88D8_BC44331FE3AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// resclass.h : header file
//

const WM_REPLY = WM_USER + 20;				// 用户自定义“回应显示”消息。
const WM_ENABLE_SUBMIT = WM_USER + 22;		// 用户自定义“提交操作使能”消息。
const WM_ENABLE_REC_BUTTONS = WM_USER + 24;	// 用户自定义“各记录移动键使能”消息。

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
	// 对话框数据交换
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CWnd *m_pParent;			// 当前父类视窗指针。
	CStudentSet *m_pStudentSet;	// 当前文档中的学生信息集合指针。
	// 显示对话框中的各学生信息数据项。
	void ShowItems();
	// 根据当前的出生日期，确定学生年龄。
	void CountAge();

	// Generated message map functions
	//{{AFX_MSG(CDataIODlg)
	afx_msg void OnChangeStudentId();			// 响应学号数据修改消息。
	afx_msg void OnChangeName();				// 响应姓名数据修改消息。
	afx_msg void OnSelchangeSexCombo();			// 响应性别数据修改消息。
	afx_msg void OnEditchangeSexCombo();		// 响应性别数据修改消息。
	afx_msg void OnSelchangeMajorCombo();		// 响应主修数据修改消息。
	afx_msg void OnEditchangeMajorCombo();		// 响应主修数据修改消息。
	afx_msg void OnSelchangeSpecialityCombo();	// 响应专业数据修改消息。
	afx_msg void OnEditchangeSpecialityCombo();	// 响应专业数据修改消息。
	afx_msg void OnChangeTelponeNo();			// 响应联系电话数据修改消息。
	afx_msg void OnChangeBirthplace();			// 响应联系电话数据修改消息。
	afx_msg void OnUpdateYearVal();				// 响应出生年数据修改消息。
	afx_msg void OnUpdateMonthVal();			// 响应出生月数据修改消息。
	afx_msg void OnUpdateDayVal();				// 响应出生日数据修改消息。
	afx_msg void OnSubmit();					// 响应提交操作消息。
	virtual BOOL OnInitDialog();				// 对话框初始化。
	afx_msg void OnPrevRec();					// 响应向前移动信息记录操作消息。
	afx_msg void OnNextRec();					// 响应向后移动信息记录操作消息。
	afx_msg void OnFirstRec();					// 响应移动至第一个信息记录操作消息。
	afx_msg void OnLastRec();					// 响应移动至最后一个信息记录操作消息。
	afx_msg void OnSelchangeSortKeyCombo();		// 响应选择排序关键字并进行相应排序操作消息。
	afx_msg void OnSelchangeRetrieveKeyCombo();	// 响应选择检索关键字并进行相应检索操作消息。
	afx_msg void OnSelchangeRetrieveCombo();	// 响应选择排序类别操作消息。
	afx_msg void OnDelete();					// 响应删除当前信息记录操作。
	//}}AFX_MSG
	// 响应用户自定义“回应显示”消息。
	afx_msg LONG OnReply(WPARAM wParam, LPARAM lParam);
	// 响应用户自定义“提交操作使能”消息。
	afx_msg LONG OnEnableSubmit(WPARAM wParam, LPARAM lParam);
	// 响应用户自定义“各记录移动键使能”消息。
	afx_msg LONG OnEnableRecButtons(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	int	m_Year;			// 暂存出生年数据。
	int	m_Month;		// 暂存出生月数据。
	int	m_Day;			// 暂存出生日数据。
	int	m_RecTotal;		// 保存当前总记录个数数据。
	int	m_RecIndex;		// 保存当前记录索引数据。
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESCLASS_H__ACF024A1_2C2C_11D5_88D8_BC44331FE3AE__INCLUDED_)

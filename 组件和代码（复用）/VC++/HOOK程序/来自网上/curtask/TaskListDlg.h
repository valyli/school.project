// TaskListDlg.h : header file
//

#if !defined(AFX_TASKLISTDLG_H__F0707367_F0D4_11D2_AFD3_A75428821049__INCLUDED_)
#define AFX_TASKLISTDLG_H__F0707367_F0D4_11D2_AFD3_A75428821049__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CTaskListDlg dialog

class CTaskListDlg : public CDialog
{
// Construction
public:
	CTaskListDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTaskListDlg)
	enum { IDD = IDD_TASKLIST_DIALOG };
	CListBox	m_list1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTaskListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTaskListDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void GetTaskList (CListBox&list);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TASKLISTDLG_H__F0707367_F0D4_11D2_AFD3_A75428821049__INCLUDED_)

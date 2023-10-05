// ListsDlg.h : header file
//

#if !defined(AFX_LISTSDLG_H__F1CBB6C9_A96F_11D3_AEE1_00104B125379__INCLUDED_)
#define AFX_LISTSDLG_H__F1CBB6C9_A96F_11D3_AEE1_00104B125379__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CListsDlg dialog

class CListsDlg : public CDialog
{
// Construction
public:
	CListsDlg(CWnd* pParent = NULL);	// standard constructor
    void PopulateCombo();
    void PopulateTree();
	void PopulateListBox();
	void PopulateListControl();
	CString m_strMainDir;
	CStringList m_strList;


// Dialog Data
	//{{AFX_DATA(CListsDlg)
	enum { IDD = IDD_LISTS_DIALOG };
	CComboBox	m_cbMainDir;
	CListCtrl	m_lcDirDetails;
	CListBox	m_lbSubDirs;
	CTreeCtrl	m_treeFiles;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CListsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeMainDir();
	afx_msg void OnSelchangeSubDirs();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTSDLG_H__F1CBB6C9_A96F_11D3_AEE1_00104B125379__INCLUDED_)

// treeDlg.h : header file
//

#if !defined(AFX_TREEDLG_H__18ADF87F_828A_4E68_AAA8_9F87F576AB5A__INCLUDED_)
#define AFX_TREEDLG_H__18ADF87F_828A_4E68_AAA8_9F87F576AB5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// CTreeDlg dialog

class CTreeDlg : public CDialog
{
// Construction
public:
	CTreeDlg(CWnd* pParent = NULL);	// standard constructor
    int getdir(char *dirname);
	CImageList m_img;
// Dialog Data
	//{{AFX_DATA(CTreeDlg)
	enum { IDD = IDD_TREE_DIALOG };
	CTreeCtrl	m_TreeCtrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTreeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEDLG_H__18ADF87F_828A_4E68_AAA8_9F87F576AB5A__INCLUDED_)

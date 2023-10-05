// Example5EDlg.h : header file
//

#if !defined(AFX_EXAMPLE5EDLG_H__7A08E048_9B09_11D4_B71C_0000B48A052A__INCLUDED_)
#define AFX_EXAMPLE5EDLG_H__7A08E048_9B09_11D4_B71C_0000B48A052A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CExample5EDlg dialog

class CExample5EDlg : public CDialog
{
// Construction
public:
	CExample5EDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CExample5EDlg)
	enum { IDD = IDD_EXAMPLE5E_DIALOG };
	BOOL	m_bAutoPlay;
	BOOL	m_bCenter;
	BOOL	m_bTransparent;
	CString	m_cstrFileName;
	//}}AFX_DATA
	CAnimateCtrl	m_animateCtrl;
	CRect			m_rectAnimateCtrl;
	DWORD			m_dwStyle;
	void	ApplyChanges();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExample5EDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CExample5EDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBrowse();
	afx_msg void OnFileChange();
	afx_msg void OnCenter();
	afx_msg void OnAutoplay();
	afx_msg void OnTransparent();
	afx_msg void OnPlay();
	afx_msg void OnStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLE5EDLG_H__7A08E048_9B09_11D4_B71C_0000B48A052A__INCLUDED_)

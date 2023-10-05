#if !defined(AFX_SELSTYLEDLG_H__B7CD1506_CAC0_11D5_9486_5254AB113BB2__INCLUDED_)
#define AFX_SELSTYLEDLG_H__B7CD1506_CAC0_11D5_9486_5254AB113BB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelStyleDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SelStyleDlg dialog

class SelStyleDlg : public CDialog
{
// Construction
public:
	SelStyleDlg(CWnd* pParent = NULL);   // standard constructor
	CString m_SelStyle;
// Dialog Data
	//{{AFX_DATA(SelStyleDlg)
	enum { IDD = IDD_DIALOG_SEL_STYLE };
	int		m_x;
	int		m_y;
	CString	m_SelCombo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SelStyleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SelStyleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboSelStyle();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELSTYLEDLG_H__B7CD1506_CAC0_11D5_9486_5254AB113BB2__INCLUDED_)

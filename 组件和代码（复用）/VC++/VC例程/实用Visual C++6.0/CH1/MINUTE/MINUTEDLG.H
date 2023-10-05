// MinuteDlg.h : header file
//

#if !defined(AFX_MINUTEDLG_H__A6419BE6_A274_11D3_AEE1_00104B125379__INCLUDED_)
#define AFX_MINUTEDLG_H__A6419BE6_A274_11D3_AEE1_00104B125379__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMinuteDlg dialog

class CMinuteDlg : public CDialog
{
// Construction
public:
	BOOL ClickCountMessage();
	int m_nClickCount;
	CMinuteDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMinuteDlg)
	enum { IDD = IDD_MINUTE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMinuteDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMinuteDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPressMe();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MINUTEDLG_H__A6419BE6_A274_11D3_AEE1_00104B125379__INCLUDED_)

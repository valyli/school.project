// mciWndDlg.h : header file
//

#if !defined(AFX_MCIWNDDLG_H__69EFAE75_DBD8_11D2_BF13_CC601E893962__INCLUDED_)
#define AFX_MCIWNDDLG_H__69EFAE75_DBD8_11D2_BF13_CC601E893962__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMciWndDlg dialog

class CMciWndDlg : public CDialog
{
// Construction
public:
	CMciWndDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMciWndDlg)
	enum { IDD = IDD_MCIWND_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMciWndDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMciWndDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MCIWNDDLG_H__69EFAE75_DBD8_11D2_BF13_CC601E893962__INCLUDED_)

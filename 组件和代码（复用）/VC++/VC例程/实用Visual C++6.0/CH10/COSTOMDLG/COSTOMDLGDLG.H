// CostomDlgDlg.h : header file
//

#if !defined(AFX_COSTOMDLGDLG_H__C046ABD9_A3B4_4382_8410_763CA060961F__INCLUDED_)
#define AFX_COSTOMDLGDLG_H__C046ABD9_A3B4_4382_8410_763CA060961F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCostomDlgDlg dialog

class CCostomDlgDlg : public CDialog
{
// Construction
public:
	CCostomDlgDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCostomDlgDlg)
	enum { IDD = IDD_COSTOMDLG_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCostomDlgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCostomDlgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COSTOMDLGDLG_H__C046ABD9_A3B4_4382_8410_763CA060961F__INCLUDED_)

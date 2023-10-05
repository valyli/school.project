// DCDrawDlg.h : header file
//

#if !defined(AFX_DCDRAWDLG_H__8945B5E7_D32A_11D2_BF13_9998FA579965__INCLUDED_)
#define AFX_DCDRAWDLG_H__8945B5E7_D32A_11D2_BF13_9998FA579965__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDCDrawDlg dialog

class CDCDrawDlg : public CDialog
{
// Construction
public:
	CDCDrawDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDCDrawDlg)
	enum { IDD = IDD_DCDRAW_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDCDrawDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDCDrawDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDrawit();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DCDRAWDLG_H__8945B5E7_D32A_11D2_BF13_9998FA579965__INCLUDED_)

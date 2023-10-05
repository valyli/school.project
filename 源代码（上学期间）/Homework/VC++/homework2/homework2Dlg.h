// homework2Dlg.h : header file
//

#if !defined(AFX_HOMEWORK2DLG_H__04546A27_B9C3_11D5_8961_923491429B3C__INCLUDED_)
#define AFX_HOMEWORK2DLG_H__04546A27_B9C3_11D5_8961_923491429B3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHomework2Dlg dialog

class CHomework2Dlg : public CDialog
{
// Construction
public:
	void ShowComputerInfo(void);
	void ShowMemoryStatus(void);
	CHomework2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHomework2Dlg)
	enum { IDD = IDD_HOMEWORK2_DIALOG };
	CListCtrl	m_Show;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHomework2Dlg)
	public:
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
/*	CImageList m_SmallImageList;
	CImageList m_LargeImageList;
*/
	// Generated message map functions
	//{{AFX_MSG(CHomework2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonMem();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnButtonComputerinfo();
	afx_msg void OnButtonExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOMEWORK2DLG_H__04546A27_B9C3_11D5_8961_923491429B3C__INCLUDED_)

// homework1Dlg.h : header file
//

#if !defined(AFX_HOMEWORK1DLG_H__141302C9_B8D6_11D5_8961_EEEE76B07E38__INCLUDED_)
#define AFX_HOMEWORK1DLG_H__141302C9_B8D6_11D5_8961_EEEE76B07E38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHomework1Dlg dialog

class CHomework1Dlg : public CDialog
{
// Construction
public:
	bool isBackward;
	bool isForward;
	int m_Step;
	bool isplay;
	CHomework1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHomework1Dlg)
	enum { IDD = IDD_HOMEWORK1_DIALOG };
	int		m_Show;
	BOOL	m_Recycle;
	CString	m_State;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHomework1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	HICON m_Icon_backward;
	HICON m_Icon_play;
	HICON m_Icon_pause;
	HICON m_Icon_stop;
	HICON m_Icon_forward;
	HICON m_Icon_exit;
	HICON m_Icon_recycle;

	// Generated message map functions
	//{{AFX_MSG(CHomework1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonPlay();
	afx_msg void OnButtonStop();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonForward();
	afx_msg void OnButtonBackward();
	afx_msg void OnClose();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOMEWORK1DLG_H__141302C9_B8D6_11D5_8961_EEEE76B07E38__INCLUDED_)

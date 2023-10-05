// CityBreakDlg.h : header file
//

#if !defined(AFX_CITYBREAKDLG_H__160448D4_A5CB_11D3_AEE1_00104B125379__INCLUDED_)
#define AFX_CITYBREAKDLG_H__160448D4_A5CB_11D3_AEE1_00104B125379__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCityBreakDlg dialog

class CCityBreakDlg : public CDialog
{
// Construction
public:
	CCityBreakDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCityBreakDlg)
	enum { IDD = IDD_CITYBREAK_DIALOG };
	int		m_nDestination;
	int		m_nHotel;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCityBreakDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCityBreakDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnChampagne();
	afx_msg void OnDance();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CITYBREAKDLG_H__160448D4_A5CB_11D3_AEE1_00104B125379__INCLUDED_)

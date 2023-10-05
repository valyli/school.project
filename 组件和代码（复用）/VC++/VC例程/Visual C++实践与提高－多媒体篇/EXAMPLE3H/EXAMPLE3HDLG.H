// Example3HDlg.h : header file
//

#if !defined(AFX_EXAMPLE3HDLG_H__13743968_9FE8_11D4_B67F_444553540000__INCLUDED_)
#define AFX_EXAMPLE3HDLG_H__13743968_9FE8_11D4_B67F_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CExample3HDlg dialog

class CExample3HDlg : public CDialog
{
// Construction
public:
	CExample3HDlg(CWnd* pParent = NULL);	// standard constructor

public:
	CRichEditCtrl	m_ctlRichEdit;
	void	SetStyle1(CHARFORMAT& cf);
	void	SetStyle2(CHARFORMAT& cf);
	void	SetStyle3(CHARFORMAT& cf);
	void	DrawRichText();

// Dialog Data
	//{{AFX_DATA(CExample3HDlg)
	enum { IDD = IDD_EXAMPLE3H_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExample3HDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CExample3HDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLE3HDLG_H__13743968_9FE8_11D4_B67F_444553540000__INCLUDED_)

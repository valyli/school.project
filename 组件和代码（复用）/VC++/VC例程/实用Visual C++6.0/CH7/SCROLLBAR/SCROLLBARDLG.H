// ScrollBarDlg.h : header file
//

#if !defined(AFX_SCROLLBARDLG_H__DA4733A8_A891_11D3_B25B_E4FA8DFC1520__INCLUDED_)
#define AFX_SCROLLBARDLG_H__DA4733A8_A891_11D3_B25B_E4FA8DFC1520__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CScrollBarDlg dialog

class CScrollBarDlg : public CDialog
{
// Construction
public:
	CScrollBarDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CScrollBarDlg)
	enum { IDD = IDD_SCROLLBAR_DIALOG };
	CScrollBar	m_ScrollBar2;
	CScrollBar	m_ScrollBar1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScrollBarDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CScrollBarDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCROLLBARDLG_H__DA4733A8_A891_11D3_B25B_E4FA8DFC1520__INCLUDED_)

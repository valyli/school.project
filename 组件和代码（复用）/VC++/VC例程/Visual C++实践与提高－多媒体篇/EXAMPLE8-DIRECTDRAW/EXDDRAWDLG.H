// ExDDrawDlg.h : header file
//

#if !defined(AFX_EXDDRAWDLG_H__893E1AA6_A6BF_11D4_B67F_444553540000__INCLUDED_)
#define AFX_EXDDRAWDLG_H__893E1AA6_A6BF_11D4_B67F_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CExDDrawDlg dialog

class CExDDrawDlg : public CDialog
{
// Construction
public:
	CExDDrawDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CExDDrawDlg)
	enum { IDD = IDD_EXDDRAW_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExDDrawDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CExDDrawDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXDDRAWDLG_H__893E1AA6_A6BF_11D4_B67F_444553540000__INCLUDED_)

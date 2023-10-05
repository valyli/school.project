// Example3GDlg.h : header file
//

#if !defined(AFX_EXAMPLE3GDLG_H__B97A9E46_76EB_11D4_ABC8_BB4A1C883358__INCLUDED_)
#define AFX_EXAMPLE3GDLG_H__B97A9E46_76EB_11D4_ABC8_BB4A1C883358__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CExample3GDlg dialog

class CExample3GDlg : public CDialog
{
// Construction
public:
	CExample3GDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CExample3GDlg)
	enum { IDD = IDD_EXAMPLE3G_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExample3GDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CExample3GDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditDel();
	afx_msg void OnEditPaste();
	afx_msg void OnEditSelectall();
	afx_msg void OnEditSelectfont();
	afx_msg void OnEditUndo();
	afx_msg void OnFileClose();
	afx_msg void OnFileNew();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	//}}AFX_MSG
	afx_msg void OnInitMenuPopup( CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu );
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLE3GDLG_H__B97A9E46_76EB_11D4_ABC8_BB4A1C883358__INCLUDED_)

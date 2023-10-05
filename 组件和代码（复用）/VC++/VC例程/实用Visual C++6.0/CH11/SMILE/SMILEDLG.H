// SmileDlg.h : header file
//

#if !defined(AFX_SMILEDLG_H__2D336967_AE7F_11D3_B25B_FB89AF801635__INCLUDED_)
#define AFX_SMILEDLG_H__2D336967_AE7F_11D3_B25B_FB89AF801635__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSmileDlg dialog

class CSmileDlg : public CDialog
{
// Construction
public:
	CBitmapButton m_bbSmile;
	CSmileDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSmileDlg)
	enum { IDD = IDD_SMILE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSmileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSmileDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDisable();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMILEDLG_H__2D336967_AE7F_11D3_B25B_FB89AF801635__INCLUDED_)

// CDPlayerDlg.h : header file
//

#if !defined(AFX_CDPLAYERDLG_H__69EFAE67_DBD8_11D2_BF13_CC601E893962__INCLUDED_)
#define AFX_CDPLAYERDLG_H__69EFAE67_DBD8_11D2_BF13_CC601E893962__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCDPlayerDlg dialog

class CCDPlayerDlg : public CDialog
{
// Construction
public:
	CCDPlayerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCDPlayerDlg)
	enum { IDD = IDD_CDPLAYER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCDPlayerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCDPlayerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDPLAYERDLG_H__69EFAE67_DBD8_11D2_BF13_CC601E893962__INCLUDED_)

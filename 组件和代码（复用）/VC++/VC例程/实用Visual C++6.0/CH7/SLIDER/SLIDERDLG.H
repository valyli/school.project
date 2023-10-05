// SliderDlg.h : header file
//

#if !defined(AFX_SLIDERDLG_H__DA4733B6_A891_11D3_B25B_E4FA8DFC1520__INCLUDED_)
#define AFX_SLIDERDLG_H__DA4733B6_A891_11D3_B25B_E4FA8DFC1520__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSliderDlg dialog

class CSliderDlg : public CDialog
{
// Construction
public:
	CSliderDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSliderDlg)
	enum { IDD = IDD_SLIDER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSliderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSliderDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SLIDERDLG_H__DA4733B6_A891_11D3_B25B_E4FA8DFC1520__INCLUDED_)

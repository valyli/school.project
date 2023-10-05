// ProfileDemoDlg.h : header file
//

#if !defined(AFX_PROFILEDEMODLG_H__999CB665_53E3_11D2_AFCF_0080C7597ADC__INCLUDED_)
#define AFX_PROFILEDEMODLG_H__999CB665_53E3_11D2_AFCF_0080C7597ADC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CProfileDemoDlg dialog

class CProfileDemoDlg : public CDialog
{
// Construction
public:
	CProfileDemoDlg(CWnd* pParent = NULL);	// standard constructor
	void OnStart(); 
// Dialog Data
	//{{AFX_DATA(CProfileDemoDlg)
	enum { IDD = IDD_PROFILEDEMO_DIALOG };
	CProgressCtrl	m_pBar;
	CStatic	m_Info;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProfileDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	HRESULT hr;
	// Generated message map functions
	//{{AFX_MSG(CProfileDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROFILEDEMODLG_H__999CB665_53E3_11D2_AFCF_0080C7597ADC__INCLUDED_)

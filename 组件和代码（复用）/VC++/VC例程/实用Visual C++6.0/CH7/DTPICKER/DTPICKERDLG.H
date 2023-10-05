// dtpickerDlg.h : header file
//

#if !defined(AFX_DTPICKERDLG_H__EA4F0BC7_B01F_11D3_B25B_ED021A88CF34__INCLUDED_)
#define AFX_DTPICKERDLG_H__EA4F0BC7_B01F_11D3_B25B_ED021A88CF34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDtpickerDlg dialog

class CDtpickerDlg : public CDialog
{
// Construction
public:
	CDtpickerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDtpickerDlg)
	enum { IDD = IDD_DTPICKER_DIALOG };
	CDateTimeCtrl	m_myTime;
	CDateTimeCtrl	m_myDate;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDtpickerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDtpickerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnDatetimechangeMydate(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DTPICKERDLG_H__EA4F0BC7_B01F_11D3_B25B_ED021A88CF34__INCLUDED_)

// exmidiDlg.h : header file
//

#if !defined(AFX_EXMIDIDLG_H__B9232CC7_9A48_11D4_9300_5254AB10AACA__INCLUDED_)
#define AFX_EXMIDIDLG_H__B9232CC7_9A48_11D4_9300_5254AB10AACA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CExmidiDlg dialog
#include "emidi.h"
class CExmidiDlg : public CDialog
{
// Construction
public:
	CExmidiDlg(CWnd* pParent = NULL);	// standard constructor
	CExMidi m_midi;
// Dialog Data
	//{{AFX_DATA(CExmidiDlg)
	enum { IDD = IDD_EXMIDI_DIALOG };
	CSliderCtrl	m_slider;
	CString	m_status;
	CString	m_statuss;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExmidiDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CExmidiDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpen();
	afx_msg void OnPlay();
	afx_msg void OnPause();
	afx_msg void OnClose();
	afx_msg void OnAhead();
	afx_msg void OnBack();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnReleasedcaptureSlider(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXMIDIDLG_H__B9232CC7_9A48_11D4_9300_5254AB10AACA__INCLUDED_)

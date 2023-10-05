// exCDDlg.h : header file
//

#if !defined(AFX_EXCDDLG_H__EFED8AE7_9AB4_11D4_9300_5254AB10AACA__INCLUDED_)
#define AFX_EXCDDLG_H__EFED8AE7_9AB4_11D4_9300_5254AB10AACA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CExCDDlg dialog
#include "ComDisc.h"
class CExCDDlg : public CDialog
{
// Construction
public:
	CExCDDlg(CWnd* pParent = NULL);	// standard constructor
	void Open();
// Dialog Data
	//{{AFX_DATA(CExCDDlg)
	enum { IDD = IDD_EXCD_DIALOG };
	CComboBox	m_track;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExCDDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CComDisc m_cd;
//	BOOL     m_bOpen;
//	BOOL     m_bCDOpen;
//	BOOL     m_bCDAudio;
	int      m_nCurTrack;
	// Generated message map functions
	//{{AFX_MSG(CExCDDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPlay();
	afx_msg void OnPlaymode();
	afx_msg void OnPause();
	afx_msg void OnEject();
	afx_msg void OnNext();
	afx_msg void OnStop();
	afx_msg void OnLast();
	afx_msg void OnSelchangeTrack();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXCDDLG_H__EFED8AE7_9AB4_11D4_9300_5254AB10AACA__INCLUDED_)

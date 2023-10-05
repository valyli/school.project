// waverDlg.h : header file
//

#if !defined(AFX_WAVERDLG_H__FEB2D335_9A3A_11D4_9300_5254AB10AACA__INCLUDED_)
#define AFX_WAVERDLG_H__FEB2D335_9A3A_11D4_9300_5254AB10AACA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWaverDlg dialog
#include "waveaudio.h"
class CWaverDlg : public CDialog
{
// Construction
public:
	CWaverDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWaverDlg)
	enum { IDD = IDD_WAVER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWaverDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON      m_hIcon;
	CWave m_Wave;
	int m_dlgw;
	int m_dlgh;
	void CWaverDlg::DrawWave(HDC hdc,unsigned int x,unsigned int y,char *path);

	// Generated message map functions
	//{{AFX_MSG(CWaverDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPlay();
	afx_msg void OnOpen();
	afx_msg void OnRecord();
	afx_msg void OnSave();
	afx_msg void OnStop();
	afx_msg void OnInfo();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAVERDLG_H__FEB2D335_9A3A_11D4_9300_5254AB10AACA__INCLUDED_)

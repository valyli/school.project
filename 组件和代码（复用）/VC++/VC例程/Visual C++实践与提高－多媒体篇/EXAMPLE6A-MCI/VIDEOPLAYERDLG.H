// VideoPlayerDlg.h : header file
//

#if !defined(AFX_VIDEOPLAYERDLG_H__B35A40C9_7DB7_11D3_860F_F6E44D6C9F3C__INCLUDED_)
#define AFX_VIDEOPLAYERDLG_H__B35A40C9_7DB7_11D3_860F_F6E44D6C9F3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CVideoPlayerDlg dialog

#include "DigitalVideo.h"

class CVideoPlayerDlg : public CDialog
{
// Construction
public:
	CVideoPlayerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CVideoPlayerDlg)
	enum { IDD = IDD_VIDEOPLAYER_DIALOG };
	CScrollBar	m_displaybar;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoPlayerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON    m_hIcon;
	CDigitalvideo   m_Video;
	BOOL     m_Open;
	BOOL     m_Sound;
	BOOL     m_Loop;
	BOOL     m_FullScreen;
	CString  m_str;
	CDialog  *Display;
	int      m_flag ;
	//
	// Generated message map functions
	//{{AFX_MSG(CVideoPlayerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpen();
	afx_msg void OnInformation();
	afx_msg void OnStop();
	afx_msg void OnPause();
	afx_msg void OnPlay();
	afx_msg void OnNext();
	afx_msg void OnPrev();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLoop();
	afx_msg void OnSound();
	afx_msg void OnFullscreen();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEOPLAYERDLG_H__B35A40C9_7DB7_11D3_860F_F6E44D6C9F3C__INCLUDED_)

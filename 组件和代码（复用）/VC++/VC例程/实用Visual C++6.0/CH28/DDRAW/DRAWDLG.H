// DrawDlg.h : header file
//
#include "ddraw.h"
#if !defined(AFX_DRAWDLG_H__1EF30FC7_DA6A_11D2_BF13_CD9C9E30D962__INCLUDED_)
#define AFX_DRAWDLG_H__1EF30FC7_DA6A_11D2_BF13_CD9C9E30D962__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDrawDlg dialog


class CDrawDlg : public CDialog
{
// Construction
public:
	CDrawDlg(CWnd* pParent = NULL);	// standard constructor

	~CDrawDlg();
	IDirectDraw2* m_pIDraw;
	IDirectDrawSurface2* m_pIMainSurface;
	IDirectDrawSurface2* m_pIFlipSurface;

// Dialog Data
	//{{AFX_DATA(CDrawDlg)
	enum { IDD = IDD_DRAW_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDrawDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWDLG_H__1EF30FC7_DA6A_11D2_BF13_CD9C9E30D962__INCLUDED_)

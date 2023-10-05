// try3Dlg.h : header file
//

#if !defined(AFX_TRY3DLG_H__2857EDC7_82AA_11D5_8961_00609721CE30__INCLUDED_)
#define AFX_TRY3DLG_H__2857EDC7_82AA_11D5_8961_00609721CE30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTry3Dlg dialog

#include "Plotter.h"

class CTry3Dlg : public CDialog
{
// Construction
public:
	void Setdata();
	CTry3Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTry3Dlg)
	enum { IDD = IDD_TRY3_DIALOG };
	int		m_x;
	int		m_y;
	int		m_posx;
	int		m_posy;
	BYTE	m_penspeed;
	CString	m_LastOut;
	double	m_Phyposx;
	double	m_Phyposy;
	double	m_Step;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTry3Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	Plotter Print;
//	HANDLE hFile;////////////////////////////////

	// Generated message map functions
	//{{AFX_MSG(CTry3Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonPa();
	afx_msg void OnButtonPr();
	afx_msg void OnButtonPd();
	afx_msg void OnButtonPu();
	afx_msg void OnButtonInit();
	afx_msg void OnButtonVs();
	afx_msg void OnButtonPdc();
	afx_msg void OnButtonPuc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRY3DLG_H__2857EDC7_82AA_11D5_8961_00609721CE30__INCLUDED_)

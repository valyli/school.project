#if !defined(AFX_AVERAGENUMDLG_H__2D5A7621_CCE4_11D4_8E81_5254AB30C250__INCLUDED_)
#define AFX_AVERAGENUMDLG_H__2D5A7621_CCE4_11D4_8E81_5254AB30C250__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AverageNumDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAverageNumDlg dialog

class CAverageNumDlg : public CDialog
{
// Construction
public:
	int m_nMaxNum;
	CAverageNumDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAverageNumDlg)
	enum { IDD = IDD_AVERAGENUM_DLG };
	CSpinButtonCtrl	m_spinNum;
	int		m_avernum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAverageNumDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAverageNumDlg)
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AVERAGENUMDLG_H__2D5A7621_CCE4_11D4_8E81_5254AB30C250__INCLUDED_)

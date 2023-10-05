#if !defined(AFX_DISPLAYDLG_H__FEB2D33D_9A3A_11D4_9300_5254AB10AACA__INCLUDED_)
#define AFX_DISPLAYDLG_H__FEB2D33D_9A3A_11D4_9300_5254AB10AACA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// displaydlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// displaydlg dialog

class displaydlg : public CDialog
{
// Construction
public:
	displaydlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(displaydlg)
	enum { IDD = IDD_DISPLAY };
	CString	m_bit;
	CString	m_chan;
	CString	m_name;
	CString	m_long;
	CString	m_sam;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(displaydlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(displaydlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISPLAYDLG_H__FEB2D33D_9A3A_11D4_9300_5254AB10AACA__INCLUDED_)

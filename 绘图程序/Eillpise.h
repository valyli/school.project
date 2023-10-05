#if !defined(AFX_EILLPISE_H__E8797CC3_61D2_11D5_90D6_FAC93FBE6671__INCLUDED_)
#define AFX_EILLPISE_H__E8797CC3_61D2_11D5_90D6_FAC93FBE6671__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Eillpise.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEillpise dialog

class CEillpise : public CDialog
{
// Construction
public:
	CEillpise(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEillpise)
	enum { IDD = IDD_DIALOG1 };
	int		m_a;
	int		m_b;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEillpise)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEillpise)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EILLPISE_H__E8797CC3_61D2_11D5_90D6_FAC93FBE6671__INCLUDED_)

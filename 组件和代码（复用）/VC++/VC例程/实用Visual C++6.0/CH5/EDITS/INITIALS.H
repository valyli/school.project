#if !defined(AFX_INITIALS_H__F1CBB6C0_A96F_11D3_AEE1_00104B125379__INCLUDED_)
#define AFX_INITIALS_H__F1CBB6C0_A96F_11D3_AEE1_00104B125379__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Initials.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInitials window

class CInitials : public CEdit
{
// Construction
public:
	CInitials();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInitials)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CInitials();

	// Generated message map functions
protected:
	//{{AFX_MSG(CInitials)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INITIALS_H__F1CBB6C0_A96F_11D3_AEE1_00104B125379__INCLUDED_)

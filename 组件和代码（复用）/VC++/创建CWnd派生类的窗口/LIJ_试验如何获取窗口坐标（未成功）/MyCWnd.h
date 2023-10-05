#if !defined(AFX_MYCWND_H__3EA83B7E_BE55_4C0E_8C23_0C2D8EDDDCE1__INCLUDED_)
#define AFX_MYCWND_H__3EA83B7E_BE55_4C0E_8C23_0C2D8EDDDCE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyCWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MyCWnd window

class MyCWnd : public CWnd
{
// Construction
public:
	MyCWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MyCWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL Create(CWnd* pParentWnd);
	virtual ~MyCWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(MyCWnd)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCWND_H__3EA83B7E_BE55_4C0E_8C23_0C2D8EDDDCE1__INCLUDED_)

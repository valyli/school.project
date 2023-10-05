// SSplit.h : main header file for the SSPLIT application
//

#if !defined(AFX_SSPLIT_H__0C15E29F_D487_11D2_BF13_87F5B9EBB265__INCLUDED_)
#define AFX_SSPLIT_H__0C15E29F_D487_11D2_BF13_87F5B9EBB265__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSSplitApp:
// See SSplit.cpp for the implementation of this class
//

class CSSplitApp : public CWinApp
{
public:
	CSSplitApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSSplitApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSSplitApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SSPLIT_H__0C15E29F_D487_11D2_BF13_87F5B9EBB265__INCLUDED_)

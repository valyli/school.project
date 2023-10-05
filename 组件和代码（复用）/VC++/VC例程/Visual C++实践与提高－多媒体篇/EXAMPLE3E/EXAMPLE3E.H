// Example3E.h : main header file for the EXAMPLE3E application
//

#if !defined(AFX_EXAMPLE3E_H__134B4B84_7459_11D4_ABC8_C73FB0673F59__INCLUDED_)
#define AFX_EXAMPLE3E_H__134B4B84_7459_11D4_ABC8_C73FB0673F59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CExample3EApp:
// See Example3E.cpp for the implementation of this class
//

class CExample3EApp : public CWinApp
{
public:
	CExample3EApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExample3EApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CExample3EApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLE3E_H__134B4B84_7459_11D4_ABC8_C73FB0673F59__INCLUDED_)

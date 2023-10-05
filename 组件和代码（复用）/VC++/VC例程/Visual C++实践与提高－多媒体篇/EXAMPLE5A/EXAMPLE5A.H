// Example5A.h : main header file for the EXAMPLE5A application
//

#if !defined(AFX_EXAMPLE5A_H__F4775C64_9A3E_11D4_B67F_444553540000__INCLUDED_)
#define AFX_EXAMPLE5A_H__F4775C64_9A3E_11D4_B67F_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CExample5AApp:
// See Example5A.cpp for the implementation of this class
//

class CExample5AApp : public CWinApp
{
public:
	CExample5AApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExample5AApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CExample5AApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLE5A_H__F4775C64_9A3E_11D4_B67F_444553540000__INCLUDED_)

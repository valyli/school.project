// Example4C.h : main header file for the EXAMPLE4C application
//

#if !defined(AFX_EXAMPLE4C_H__B78C5929_A852_11D4_8EAF_0000B48A052A__INCLUDED_)
#define AFX_EXAMPLE4C_H__B78C5929_A852_11D4_8EAF_0000B48A052A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CExample4CApp:
// See Example4C.cpp for the implementation of this class
//

#define WM_DOREALIZE WM_USER+200

class CExample4CApp : public CWinApp
{
public:
	CExample4CApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExample4CApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CExample4CApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLE4C_H__B78C5929_A852_11D4_8EAF_0000B48A052A__INCLUDED_)

// Example3G.h : main header file for the EXAMPLE3G application
//

#if !defined(AFX_EXAMPLE3G_H__B97A9E44_76EB_11D4_ABC8_BB4A1C883358__INCLUDED_)
#define AFX_EXAMPLE3G_H__B97A9E44_76EB_11D4_ABC8_BB4A1C883358__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CExample3GApp:
// See Example3G.cpp for the implementation of this class
//

class CExample3GApp : public CWinApp
{
public:
	CExample3GApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExample3GApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CExample3GApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLE3G_H__B97A9E44_76EB_11D4_ABC8_BB4A1C883358__INCLUDED_)

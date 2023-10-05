// TestShellSystemType.h : main header file for the TESTSHELLSYSTEMTYPE application
//

#if !defined(AFX_TESTSHELLSYSTEMTYPE_H__86916AAC_24E7_4609_AB3B_FB74AF8AC191__INCLUDED_)
#define AFX_TESTSHELLSYSTEMTYPE_H__86916AAC_24E7_4609_AB3B_FB74AF8AC191__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestShellSystemTypeApp:
// See TestShellSystemType.cpp for the implementation of this class
//

class CTestShellSystemTypeApp : public CWinApp
{
public:
	CTestShellSystemTypeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestShellSystemTypeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestShellSystemTypeApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTSHELLSYSTEMTYPE_H__86916AAC_24E7_4609_AB3B_FB74AF8AC191__INCLUDED_)

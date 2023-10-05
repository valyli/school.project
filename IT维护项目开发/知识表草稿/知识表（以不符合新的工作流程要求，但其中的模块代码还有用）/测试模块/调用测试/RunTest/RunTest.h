// RunTest.h : main header file for the RUNTEST application
//

#if !defined(AFX_RUNTEST_H__871BF0C1_E795_40E6_A41D_7226B27EEF0A__INCLUDED_)
#define AFX_RUNTEST_H__871BF0C1_E795_40E6_A41D_7226B27EEF0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRunTestApp:
// See RunTest.cpp for the implementation of this class
//

class CRunTestApp : public CWinApp
{
public:
	CRunTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRunTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRunTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RUNTEST_H__871BF0C1_E795_40E6_A41D_7226B27EEF0A__INCLUDED_)

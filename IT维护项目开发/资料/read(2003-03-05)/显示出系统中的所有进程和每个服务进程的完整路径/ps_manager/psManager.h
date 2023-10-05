// psManager.h : main header file for the PSMANAGER application
//

#if !defined(AFX_PSMANAGER_H__8D43E574_4212_11D4_B568_005004FF1036__INCLUDED_)
#define AFX_PSMANAGER_H__8D43E574_4212_11D4_B568_005004FF1036__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPsManagerApp:
// See psManager.cpp for the implementation of this class
//

class CPsManagerApp : public CWinApp
{
public:
	CPsManagerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPsManagerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPsManagerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSMANAGER_H__8D43E574_4212_11D4_B568_005004FF1036__INCLUDED_)

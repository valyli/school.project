// MLaunch.h : main header file for the MLAUNCH application
//

#if !defined(AFX_MLAUNCH_H__4121F4E7_9202_11D2_B25C_8BE0A8C5C934__INCLUDED_)
#define AFX_MLAUNCH_H__4121F4E7_9202_11D2_B25C_8BE0A8C5C934__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMLaunchApp:
// See MLaunch.cpp for the implementation of this class
//

class CMLaunchApp : public CWinApp
{
public:
	CMLaunchApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMLaunchApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMLaunchApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MLAUNCH_H__4121F4E7_9202_11D2_B25C_8BE0A8C5C934__INCLUDED_)

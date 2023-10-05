// Example5E.h : main header file for the EXAMPLE5E application
//

#if !defined(AFX_EXAMPLE5E_H__7A08E046_9B09_11D4_B71C_0000B48A052A__INCLUDED_)
#define AFX_EXAMPLE5E_H__7A08E046_9B09_11D4_B71C_0000B48A052A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CExample5EApp:
// See Example5E.cpp for the implementation of this class
//

class CExample5EApp : public CWinApp
{
public:
	CExample5EApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExample5EApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CExample5EApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLE5E_H__7A08E046_9B09_11D4_B71C_0000B48A052A__INCLUDED_)

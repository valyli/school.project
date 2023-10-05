// ProcessKiller.h : main header file for the PROCESSKILLER application
//

#if !defined(AFX_PROCESSKILLER_H__1550A1BF_8655_423A_B40E_5EB0AFE96665__INCLUDED_)
#define AFX_PROCESSKILLER_H__1550A1BF_8655_423A_B40E_5EB0AFE96665__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CProcessKillerApp:
// See ProcessKiller.cpp for the implementation of this class
//

class CProcessKillerApp : public CWinApp
{
public:
	CProcessKillerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProcessKillerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CProcessKillerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROCESSKILLER_H__1550A1BF_8655_423A_B40E_5EB0AFE96665__INCLUDED_)

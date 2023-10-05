// Sysinfo.h : main header file for the SYSINFO application
//

#if !defined(AFX_SYSINFO_H__5964FCC4_A8D4_11D3_AEE1_00104B125379__INCLUDED_)
#define AFX_SYSINFO_H__5964FCC4_A8D4_11D3_AEE1_00104B125379__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSysinfoApp:
// See Sysinfo.cpp for the implementation of this class
//

class CSysinfoApp : public CWinApp
{
public:
	CSysinfoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSysinfoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSysinfoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSINFO_H__5964FCC4_A8D4_11D3_AEE1_00104B125379__INCLUDED_)

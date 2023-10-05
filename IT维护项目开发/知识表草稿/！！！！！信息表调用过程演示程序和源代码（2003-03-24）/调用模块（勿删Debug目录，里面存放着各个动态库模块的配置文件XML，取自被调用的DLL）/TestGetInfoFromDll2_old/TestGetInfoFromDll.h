// TestGetInfoFromDll.h : main header file for the TESTGETINFOFROMDLL application
//

#if !defined(AFX_TESTGETINFOFROMDLL_H__4FB28C2F_9141_4437_A2D0_21C0154C0998__INCLUDED_)
#define AFX_TESTGETINFOFROMDLL_H__4FB28C2F_9141_4437_A2D0_21C0154C0998__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestGetInfoFromDllApp:
// See TestGetInfoFromDll.cpp for the implementation of this class
//

class CTestGetInfoFromDllApp : public CWinApp
{
public:
	CTestGetInfoFromDllApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestGetInfoFromDllApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestGetInfoFromDllApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTGETINFOFROMDLL_H__4FB28C2F_9141_4437_A2D0_21C0154C0998__INCLUDED_)

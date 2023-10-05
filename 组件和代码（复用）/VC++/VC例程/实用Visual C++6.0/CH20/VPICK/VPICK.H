// VPick.h : main header file for the VPICK application
//

#if !defined(AFX_VPICK_H__0B845287_D4C6_11D2_BF13_FBDAC8B2DA65__INCLUDED_)
#define AFX_VPICK_H__0B845287_D4C6_11D2_BF13_FBDAC8B2DA65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CVPickApp:
// See VPick.cpp for the implementation of this class
//

class CVPickApp : public CWinApp
{
public:
	CVPickApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVPickApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CVPickApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VPICK_H__0B845287_D4C6_11D2_BF13_FBDAC8B2DA65__INCLUDED_)

// StatusMouse.h : main header file for the STATUSMOUSE application
//

#if !defined(AFX_STATUSMOUSE_H__44E69005_5A1C_11D1_B5D9_F41150DD6517__INCLUDED_)
#define AFX_STATUSMOUSE_H__44E69005_5A1C_11D1_B5D9_F41150DD6517__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CStatusMouseApp:
// See StatusMouse.cpp for the implementation of this class
//

class CStatusMouseApp : public CWinApp
{
public:
	CStatusMouseApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatusMouseApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CStatusMouseApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATUSMOUSE_H__44E69005_5A1C_11D1_B5D9_F41150DD6517__INCLUDED_)

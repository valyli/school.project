// dlgbar.h : main header file for the DLGBAR application
//

#if !defined(AFX_DLGBAR_H__E9683EC7_59B9_11D1_B5D9_BC53D39E0517__INCLUDED_)
#define AFX_DLGBAR_H__E9683EC7_59B9_11D1_B5D9_BC53D39E0517__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDlgbarApp:
// See dlgbar.cpp for the implementation of this class
//

class CDlgbarApp : public CWinApp
{
public:
	CDlgbarApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgbarApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDlgbarApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBAR_H__E9683EC7_59B9_11D1_B5D9_BC53D39E0517__INCLUDED_)

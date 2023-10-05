// SizeForm.h : main header file for the SIZEFORM application
//

#if !defined(AFX_SIZEFORM_H__4157B980_6DC7_11CD_BC53_EDB715115552__INCLUDED_)
#define AFX_SIZEFORM_H__4157B980_6DC7_11CD_BC53_EDB715115552__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSizeFormApp:
// See SizeForm.cpp for the implementation of this class
//

class CSizeFormApp : public CWinApp
{
public:
	CSizeFormApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSizeFormApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSizeFormApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIZEFORM_H__4157B980_6DC7_11CD_BC53_EDB715115552__INCLUDED_)

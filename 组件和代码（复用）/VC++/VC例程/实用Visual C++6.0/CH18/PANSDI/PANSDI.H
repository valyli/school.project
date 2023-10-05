// PanSDI.h : main header file for the PANSDI application
//

#if !defined(AFX_PANSDI_H__4157B994_6DC7_11CD_BC53_EDB715115552__INCLUDED_)
#define AFX_PANSDI_H__4157B994_6DC7_11CD_BC53_EDB715115552__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPanSDIApp:
// See PanSDI.cpp for the implementation of this class
//

class CPanSDIApp : public CWinApp
{
public:
	CPanSDIApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPanSDIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CPanSDIApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANSDI_H__4157B994_6DC7_11CD_BC53_EDB715115552__INCLUDED_)

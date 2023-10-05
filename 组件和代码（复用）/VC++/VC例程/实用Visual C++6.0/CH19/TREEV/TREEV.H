// TreeV.h : main header file for the TREEV application
//

#if !defined(AFX_TREEV_H__98AE21A7_A463_11CF_BC51_BAE7D2415650__INCLUDED_)
#define AFX_TREEV_H__98AE21A7_A463_11CF_BC51_BAE7D2415650__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTreeVApp:
// See TreeV.cpp for the implementation of this class
//

class CTreeVApp : public CWinApp
{
public:
	CTreeVApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeVApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTreeVApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEV_H__98AE21A7_A463_11CF_BC51_BAE7D2415650__INCLUDED_)

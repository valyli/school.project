// Database.h : main header file for the DATABASE application
//

#if !defined(AFX_DATABASE_H__C3797627_442D_11D2_953B_CDD998FF14B6__INCLUDED_)
#define AFX_DATABASE_H__C3797627_442D_11D2_953B_CDD998FF14B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDatabaseApp:
// See Database.cpp for the implementation of this class
//

class CDatabaseApp : public CWinApp
{
public:
	CDatabaseApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatabaseApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDatabaseApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATABASE_H__C3797627_442D_11D2_953B_CDD998FF14B6__INCLUDED_)

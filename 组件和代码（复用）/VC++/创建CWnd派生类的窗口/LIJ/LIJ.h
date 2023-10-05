// LIJ.h : main header file for the LIJ application
//

#if !defined(AFX_LIJ_H__BED99355_CBE4_4451_8E45_D0BAA5182F71__INCLUDED_)
#define AFX_LIJ_H__BED99355_CBE4_4451_8E45_D0BAA5182F71__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLIJApp:
// See LIJ.cpp for the implementation of this class
//

class CLIJApp : public CWinApp
{
public:
	CLIJApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLIJApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CLIJApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIJ_H__BED99355_CBE4_4451_8E45_D0BAA5182F71__INCLUDED_)

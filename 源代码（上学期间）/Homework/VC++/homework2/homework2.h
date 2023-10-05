// homework2.h : main header file for the HOMEWORK2 application
//

#if !defined(AFX_HOMEWORK2_H__04546A25_B9C3_11D5_8961_923491429B3C__INCLUDED_)
#define AFX_HOMEWORK2_H__04546A25_B9C3_11D5_8961_923491429B3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHomework2App:
// See homework2.cpp for the implementation of this class
//

class CHomework2App : public CWinApp
{
public:
	CHomework2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHomework2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHomework2App)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOMEWORK2_H__04546A25_B9C3_11D5_8961_923491429B3C__INCLUDED_)

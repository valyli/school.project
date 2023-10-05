// homework4.h : main header file for the HOMEWORK4 application
//

#if !defined(AFX_HOMEWORK4_H__B7CD14F7_CAC0_11D5_9486_5254AB113BB2__INCLUDED_)
#define AFX_HOMEWORK4_H__B7CD14F7_CAC0_11D5_9486_5254AB113BB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CHomework4App:
// See homework4.cpp for the implementation of this class
//

class CHomework4App : public CWinApp
{
public:
	CHomework4App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHomework4App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CHomework4App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOMEWORK4_H__B7CD14F7_CAC0_11D5_9486_5254AB113BB2__INCLUDED_)

// homework1.h : main header file for the HOMEWORK1 application
//

#if !defined(AFX_HOMEWORK1_H__141302C7_B8D6_11D5_8961_EEEE76B07E38__INCLUDED_)
#define AFX_HOMEWORK1_H__141302C7_B8D6_11D5_8961_EEEE76B07E38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHomework1App:
// See homework1.cpp for the implementation of this class
//

class CHomework1App : public CWinApp
{
public:
	CHomework1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHomework1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHomework1App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOMEWORK1_H__141302C7_B8D6_11D5_8961_EEEE76B07E38__INCLUDED_)

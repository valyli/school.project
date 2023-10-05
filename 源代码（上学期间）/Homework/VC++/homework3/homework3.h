// homework3.h : main header file for the HOMEWORK3 application
//

#if !defined(AFX_HOMEWORK3_H__924E8805_BB22_11D5_8961_B5D570A3E53F__INCLUDED_)
#define AFX_HOMEWORK3_H__924E8805_BB22_11D5_8961_B5D570A3E53F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHomework3App:
// See homework3.cpp for the implementation of this class
//

class CHomework3App : public CWinApp
{
public:
	CHomework3App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHomework3App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHomework3App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOMEWORK3_H__924E8805_BB22_11D5_8961_B5D570A3E53F__INCLUDED_)

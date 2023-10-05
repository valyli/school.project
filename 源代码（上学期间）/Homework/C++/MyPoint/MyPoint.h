// MyPoint.h : main header file for the MYPOINT application
//

#if !defined(AFX_MYPOINT_H__F13CC951_44C0_11D5_82DA_00E04C3B196D__INCLUDED_)
#define AFX_MYPOINT_H__F13CC951_44C0_11D5_82DA_00E04C3B196D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyPointApp:
// See MyPoint.cpp for the implementation of this class
//

class CMyPointApp : public CWinApp
{
public:
	CMyPointApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyPointApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMyPointApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPOINT_H__F13CC951_44C0_11D5_82DA_00E04C3B196D__INCLUDED_)

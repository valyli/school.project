// Exmaple4A.h : main header file for the EXMAPLE4A application
//

#if !defined(AFX_EXMAPLE4A_H__E7CCDF7A_9158_11D4_B67F_444553540000__INCLUDED_)
#define AFX_EXMAPLE4A_H__E7CCDF7A_9158_11D4_B67F_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CExmaple4AApp:
// See Exmaple4A.cpp for the implementation of this class
//

class CExmaple4AApp : public CWinApp
{
public:
	CExmaple4AApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExmaple4AApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CExmaple4AApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXMAPLE4A_H__E7CCDF7A_9158_11D4_B67F_444553540000__INCLUDED_)

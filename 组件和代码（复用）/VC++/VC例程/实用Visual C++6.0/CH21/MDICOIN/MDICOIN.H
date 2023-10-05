// MDICoin.h : main header file for the MDICOIN application
//

#if !defined(AFX_MDICOIN_H__73EB1924_6B2D_11CD_BC53_D9F8B661B44D__INCLUDED_)
#define AFX_MDICOIN_H__73EB1924_6B2D_11CD_BC53_D9F8B661B44D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMDICoinApp:
// See MDICoin.cpp for the implementation of this class
//

class CMDICoinApp : public CWinApp
{
public:
	CMDICoinApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDICoinApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMDICoinApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDICOIN_H__73EB1924_6B2D_11CD_BC53_D9F8B661B44D__INCLUDED_)

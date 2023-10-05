// SDICoin.h : main header file for the SDICOIN application
//

#if !defined(AFX_SDICOIN_H__B038A625_AD17_11D0_B1A4_20964CC10000__INCLUDED_)
#define AFX_SDICOIN_H__B038A625_AD17_11D0_B1A4_20964CC10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSDICoinApp:
// See SDICoin.cpp for the implementation of this class
//

class CSDICoinApp : public CWinApp
{
public:
	CSDICoinApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSDICoinApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSDICoinApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDICOIN_H__B038A625_AD17_11D0_B1A4_20964CC10000__INCLUDED_)

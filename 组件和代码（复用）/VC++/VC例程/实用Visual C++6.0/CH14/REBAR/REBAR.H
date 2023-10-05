// rebar.h : main header file for the REBAR application
//

#if !defined(AFX_REBAR_H__64C10F65_5AA6_11D1_B5D9_C30D74116017__INCLUDED_)
#define AFX_REBAR_H__64C10F65_5AA6_11D1_B5D9_C30D74116017__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRebarApp:
// See rebar.cpp for the implementation of this class
//

class CRebarApp : public CWinApp
{
public:
	CRebarApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRebarApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CRebarApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REBAR_H__64C10F65_5AA6_11D1_B5D9_C30D74116017__INCLUDED_)

// FindCom.h : main header file for the FINDCOM application
//

#if !defined(AFX_FINDCOM_H__2C2174D8_F445_4079_B10F_4A01A8D40146__INCLUDED_)
#define AFX_FINDCOM_H__2C2174D8_F445_4079_B10F_4A01A8D40146__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFindComApp:
// See FindCom.cpp for the implementation of this class
//

class CFindComApp : public CWinApp
{
public:
	CFindComApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindComApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CFindComApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDCOM_H__2C2174D8_F445_4079_B10F_4A01A8D40146__INCLUDED_)

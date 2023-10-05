// MLaunchDlg.h : main header file for the MLAUNCHDLG application
//

#if !defined(AFX_MLAUNCHDLG_H__48896565_967F_11CE_B78D_444553540000__INCLUDED_)
#define AFX_MLAUNCHDLG_H__48896565_967F_11CE_B78D_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMLaunchDlgApp:
// See MLaunchDlg.cpp for the implementation of this class
//

class CMLaunchDlgApp : public CWinApp
{
public:
	CMLaunchDlgApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMLaunchDlgApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMLaunchDlgApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MLAUNCHDLG_H__48896565_967F_11CE_B78D_444553540000__INCLUDED_)

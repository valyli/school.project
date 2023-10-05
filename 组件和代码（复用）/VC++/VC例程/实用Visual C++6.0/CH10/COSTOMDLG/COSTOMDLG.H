// CostomDlg.h : main header file for the COSTOMDLG application
//

#if !defined(AFX_COSTOMDLG_H__B3DA4D82_7697_4E65_A2E7_8F764C520D0C__INCLUDED_)
#define AFX_COSTOMDLG_H__B3DA4D82_7697_4E65_A2E7_8F764C520D0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCostomDlgApp:
// See CostomDlg.cpp for the implementation of this class
//

class CCostomDlgApp : public CWinApp
{
public:
	CCostomDlgApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCostomDlgApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCostomDlgApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COSTOMDLG_H__B3DA4D82_7697_4E65_A2E7_8F764C520D0C__INCLUDED_)

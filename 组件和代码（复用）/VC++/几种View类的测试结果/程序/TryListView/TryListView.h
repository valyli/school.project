// TryListView.h : main header file for the TRYLISTVIEW application
//

#if !defined(AFX_TRYLISTVIEW_H__575AA067_C9BC_4A70_A088_A62524345349__INCLUDED_)
#define AFX_TRYLISTVIEW_H__575AA067_C9BC_4A70_A088_A62524345349__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTryListViewApp:
// See TryListView.cpp for the implementation of this class
//

class CTryListViewApp : public CWinApp
{
public:
	CTryListViewApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTryListViewApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTryListViewApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRYLISTVIEW_H__575AA067_C9BC_4A70_A088_A62524345349__INCLUDED_)

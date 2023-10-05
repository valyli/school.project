// ListV.h : main header file for the LISTV application
//

#if !defined(AFX_LISTV_H__1CFD0E25_A393_11CF_BC51_9390FCB46551__INCLUDED_)
#define AFX_LISTV_H__1CFD0E25_A393_11CF_BC51_9390FCB46551__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CListVApp:
// See ListV.cpp for the implementation of this class
//

class CListVApp : public CWinApp
{
public:
	CListVApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListVApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CListVApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTV_H__1CFD0E25_A393_11CF_BC51_9390FCB46551__INCLUDED_)

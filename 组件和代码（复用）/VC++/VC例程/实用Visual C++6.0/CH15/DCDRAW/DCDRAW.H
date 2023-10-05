// DCDraw.h : main header file for the DCDRAW application
//

#if !defined(AFX_DCDRAW_H__8945B5E5_D32A_11D2_BF13_9998FA579965__INCLUDED_)
#define AFX_DCDRAW_H__8945B5E5_D32A_11D2_BF13_9998FA579965__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDCDrawApp:
// See DCDraw.cpp for the implementation of this class
//

class CDCDrawApp : public CWinApp
{
public:
	CDCDrawApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDCDrawApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDCDrawApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DCDRAW_H__8945B5E5_D32A_11D2_BF13_9998FA579965__INCLUDED_)

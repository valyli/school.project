// Smile.h : main header file for the SMILE application
//

#if !defined(AFX_SMILE_H__2D336965_AE7F_11D3_B25B_FB89AF801635__INCLUDED_)
#define AFX_SMILE_H__2D336965_AE7F_11D3_B25B_FB89AF801635__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSmileApp:
// See Smile.cpp for the implementation of this class
//

class CSmileApp : public CWinApp
{
public:
	CSmileApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSmileApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSmileApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMILE_H__2D336965_AE7F_11D3_B25B_FB89AF801635__INCLUDED_)

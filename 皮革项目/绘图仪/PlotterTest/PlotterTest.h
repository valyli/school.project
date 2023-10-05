// PlotterTest.h : main header file for the PLOTTERTEST application
//

#if !defined(AFX_PLOTTERTEST_H__81829BA5_8207_11D5_8961_00609721CE30__INCLUDED_)
#define AFX_PLOTTERTEST_H__81829BA5_8207_11D5_8961_00609721CE30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPlotterTestApp:
// See PlotterTest.cpp for the implementation of this class
//

class CPlotterTestApp : public CWinApp
{
public:
	CPlotterTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlotterTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPlotterTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLOTTERTEST_H__81829BA5_8207_11D5_8961_00609721CE30__INCLUDED_)

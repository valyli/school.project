// Slider.h : main header file for the SLIDER application
//

#if !defined(AFX_SLIDER_H__DA4733B4_A891_11D3_B25B_E4FA8DFC1520__INCLUDED_)
#define AFX_SLIDER_H__DA4733B4_A891_11D3_B25B_E4FA8DFC1520__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSliderApp:
// See Slider.cpp for the implementation of this class
//

class CSliderApp : public CWinApp
{
public:
	CSliderApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSliderApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSliderApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SLIDER_H__DA4733B4_A891_11D3_B25B_E4FA8DFC1520__INCLUDED_)

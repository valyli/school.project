// Shapes.h : main header file for the SHAPES application
//

#if !defined(AFX_SHAPES_H__907300C1_AF40_11D3_B25B_ACE5E3DA1335__INCLUDED_)
#define AFX_SHAPES_H__907300C1_AF40_11D3_B25B_ACE5E3DA1335__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CShapesApp:
// See Shapes.cpp for the implementation of this class
//

class CShapesApp : public CWinApp
{
public:
	CShapesApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShapesApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CShapesApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHAPES_H__907300C1_AF40_11D3_B25B_ACE5E3DA1335__INCLUDED_)

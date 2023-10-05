// MemViewView.h : interface of the CMemViewView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMVIEWVIEW_H__4BE8C4C2_CE02_11D5_9244_0050DAB40CEC__INCLUDED_)
#define AFX_MEMVIEWVIEW_H__4BE8C4C2_CE02_11D5_9244_0050DAB40CEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bEdit.h"


class CMemViewView : public CView
{
protected: // create from serialization only
	CMemViewView();
	DECLARE_DYNCREATE(CMemViewView)

// Attributes
public:
	CMemViewDoc* GetDocument();

    CSW_BDisplay m_BWnd;
// Operations
public:

    void    ShowAddress     (LPCTSTR MemAddr, LPCTSTR AddrLen = "0x1000");
    void    ShowAddress     (LPBYTE  MemAddr, UINT  AddrLen = 0x1000);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMemViewView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMemViewView();
protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMemViewView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MemViewView.cpp
inline CMemViewDoc* CMemViewView::GetDocument()
   { return (CMemViewDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEMVIEWVIEW_H__4BE8C4C2_CE02_11D5_9244_0050DAB40CEC__INCLUDED_)

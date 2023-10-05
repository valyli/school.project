#if !defined(AFX_OWNWND_H__100FDA0A_FDE9_4724_B5AE_48B017577FDE__INCLUDED_)
#define AFX_OWNWND_H__100FDA0A_FDE9_4724_B5AE_48B017577FDE__INCLUDED_

#include "HzGL.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OwnWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COwnWnd view


class COwnWnd : public CView
{
public:
	COwnWnd();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(COwnWnd)

// Attributes
public:
CHzGL m_hzgl;
// Operations
public:
	BOOL Create(const RECT& rect, CWnd* parent, UINT nID,DWORD dwStyle=WS_CHILD|WS_BORDER|WS_TABSTOP|WS_VISIBLE);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COwnWnd)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~COwnWnd();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	BOOL RegistryWindow();
	
	//{{AFX_MSG(COwnWnd)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OWNWND_H__100FDA0A_FDE9_4724_B5AE_48B017577FDE__INCLUDED_)

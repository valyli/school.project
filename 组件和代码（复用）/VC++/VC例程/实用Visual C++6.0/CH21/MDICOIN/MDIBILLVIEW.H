#if !defined(AFX_MDIBILLVIEW_H__73EB1937_6B2D_11CD_BC53_D9F8B661B44D__INCLUDED_)
#define AFX_MDIBILLVIEW_H__73EB1937_6B2D_11CD_BC53_D9F8B661B44D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MDIBillDoc.h"
// MDIBillView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMDIBillView view

class CMDIBillView : public CView
{
protected:
	CMDIBillView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMDIBillView)

// Attributes
public:

// Operations
public:
	CMDIBillDoc* GetDocument();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDIBillView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMDIBillView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMDIBillView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDIBILLVIEW_H__73EB1937_6B2D_11CD_BC53_D9F8B661B44D__INCLUDED_)

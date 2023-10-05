#if !defined(AFX_ARTVIEW_H__0B845297_D4C6_11D2_BF13_FBDAC8B2DA65__INCLUDED_)
#define AFX_ARTVIEW_H__0B845297_D4C6_11D2_BF13_FBDAC8B2DA65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ArtView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CArtView view

class CArtView : public CView
{
protected:
	CArtView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CArtView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArtView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CArtView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CArtView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARTVIEW_H__0B845297_D4C6_11D2_BF13_FBDAC8B2DA65__INCLUDED_)

// VPickView.h : interface of the CVPickView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VPICKVIEW_H__0B84528F_D4C6_11D2_BF13_FBDAC8B2DA65__INCLUDED_)
#define AFX_VPICKVIEW_H__0B84528F_D4C6_11D2_BF13_FBDAC8B2DA65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CVPickDoc;
class CVPickView : public CEditView
{
protected: // create from serialization only
	CVPickView();
	DECLARE_DYNCREATE(CVPickView)

// Attributes
public:
	CVPickDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVPickView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVPickView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVPickView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in VPickView.cpp
inline CVPickDoc* CVPickView::GetDocument()
   { return (CVPickDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VPICKVIEW_H__0B84528F_D4C6_11D2_BF13_FBDAC8B2DA65__INCLUDED_)

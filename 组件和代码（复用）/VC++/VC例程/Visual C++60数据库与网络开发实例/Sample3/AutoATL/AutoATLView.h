// AutoATLView.h : interface of the CAutoATLView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUTOATLVIEW_H__8BE69031_68EF_11D2_9AE7_00A0C9E52DCB__INCLUDED_)
#define AFX_AUTOATLVIEW_H__8BE69031_68EF_11D2_9AE7_00A0C9E52DCB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CAutoATLView : public CView
{
protected: // create from serialization only
	CAutoATLView();
	DECLARE_DYNCREATE(CAutoATLView)

// Attributes
public:
	CAutoATLDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoATLView)
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
	virtual ~CAutoATLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAutoATLView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in AutoATLView.cpp
inline CAutoATLDoc* CAutoATLView::GetDocument()
   { return (CAutoATLDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOATLVIEW_H__8BE69031_68EF_11D2_9AE7_00A0C9E52DCB__INCLUDED_)

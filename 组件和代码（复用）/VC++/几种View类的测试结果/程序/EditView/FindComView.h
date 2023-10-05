// FindComView.h : interface of the CFindComView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FINDCOMVIEW_H__40BD8ECB_A35F_491C_87BB_5F767543F42C__INCLUDED_)
#define AFX_FINDCOMVIEW_H__40BD8ECB_A35F_491C_87BB_5F767543F42C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFindComView : public CEditView
{
protected: // create from serialization only
	CFindComView();
	DECLARE_DYNCREATE(CFindComView)

// Attributes
public:
	CFindComDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindComView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	CButton m1;
	CButton m2;
	CButton m3;
	virtual ~CFindComView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFindComView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FindComView.cpp
inline CFindComDoc* CFindComView::GetDocument()
   { return (CFindComDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDCOMVIEW_H__40BD8ECB_A35F_491C_87BB_5F767543F42C__INCLUDED_)

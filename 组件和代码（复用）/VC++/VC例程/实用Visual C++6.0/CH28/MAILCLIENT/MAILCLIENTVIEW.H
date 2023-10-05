// MailClientView.h : interface of the CMailClientView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAILCLIENTVIEW_H__E087E9DB_DB17_11D2_BF13_AA406FC81D62__INCLUDED_)
#define AFX_MAILCLIENTVIEW_H__E087E9DB_DB17_11D2_BF13_AA406FC81D62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMailClientView : public CEditView
{
protected: // create from serialization only
	CMailClientView();
	DECLARE_DYNCREATE(CMailClientView)

// Attributes
public:
	CMailClientDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMailClientView)
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
	virtual ~CMailClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMailClientView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MailClientView.cpp
inline CMailClientDoc* CMailClientView::GetDocument()
   { return (CMailClientDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAILCLIENTVIEW_H__E087E9DB_DB17_11D2_BF13_AA406FC81D62__INCLUDED_)

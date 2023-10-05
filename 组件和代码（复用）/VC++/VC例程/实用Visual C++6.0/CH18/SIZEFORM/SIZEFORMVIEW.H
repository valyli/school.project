// SizeFormView.h : interface of the CSizeFormView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIZEFORMVIEW_H__4157B988_6DC7_11CD_BC53_EDB715115552__INCLUDED_)
#define AFX_SIZEFORMVIEW_H__4157B988_6DC7_11CD_BC53_EDB715115552__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSizeFormView : public CFormView
{
protected: // create from serialization only
	CSizeFormView();
	DECLARE_DYNCREATE(CSizeFormView)

public:
	//{{AFX_DATA(CSizeFormView)
	enum { IDD = IDD_SIZEFORM_FORM };
	CEdit	m_SizeableEdit;
	//}}AFX_DATA

// Attributes
public:
	CSizeFormDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSizeFormView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSizeFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSizeFormView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SizeFormView.cpp
inline CSizeFormDoc* CSizeFormView::GetDocument()
   { return (CSizeFormDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIZEFORMVIEW_H__4157B988_6DC7_11CD_BC53_EDB715115552__INCLUDED_)

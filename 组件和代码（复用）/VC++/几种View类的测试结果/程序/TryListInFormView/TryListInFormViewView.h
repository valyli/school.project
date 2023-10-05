// TryListInFormViewView.h : interface of the CTryListInFormViewView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRYLISTINFORMVIEWVIEW_H__6B5CC3B3_3929_4E2B_A957_D4CBFBBD2A5C__INCLUDED_)
#define AFX_TRYLISTINFORMVIEWVIEW_H__6B5CC3B3_3929_4E2B_A957_D4CBFBBD2A5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTryListInFormViewView : public CFormView
{
protected: // create from serialization only
	CTryListInFormViewView();
	DECLARE_DYNCREATE(CTryListInFormViewView)

public:
	//{{AFX_DATA(CTryListInFormViewView)
	enum{ IDD = IDD_TRYLISTINFORMVIEW_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CTryListInFormViewDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTryListInFormViewView)
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
	virtual ~CTryListInFormViewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTryListInFormViewView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TryListInFormViewView.cpp
inline CTryListInFormViewDoc* CTryListInFormViewView::GetDocument()
   { return (CTryListInFormViewDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRYLISTINFORMVIEWVIEW_H__6B5CC3B3_3929_4E2B_A957_D4CBFBBD2A5C__INCLUDED_)

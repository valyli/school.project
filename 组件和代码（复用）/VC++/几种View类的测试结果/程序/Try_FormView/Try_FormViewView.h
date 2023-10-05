// Try_FormViewView.h : interface of the CTry_FormViewView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRY_FORMVIEWVIEW_H__4D082F72_B3A3_4428_9897_E91CB120366C__INCLUDED_)
#define AFX_TRY_FORMVIEWVIEW_H__4D082F72_B3A3_4428_9897_E91CB120366C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTry_FormViewView : public CFormView
{
protected: // create from serialization only
	CTry_FormViewView();
	DECLARE_DYNCREATE(CTry_FormViewView)

public:
	//{{AFX_DATA(CTry_FormViewView)
	enum{ IDD = IDD_TRY_FORMVIEW_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CTry_FormViewDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTry_FormViewView)
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
	CButton m1;
	CButton m2;
	CButton m3;
	virtual ~CTry_FormViewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTry_FormViewView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Try_FormViewView.cpp
inline CTry_FormViewDoc* CTry_FormViewView::GetDocument()
   { return (CTry_FormViewDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRY_FORMVIEWVIEW_H__4D082F72_B3A3_4428_9897_E91CB120366C__INCLUDED_)

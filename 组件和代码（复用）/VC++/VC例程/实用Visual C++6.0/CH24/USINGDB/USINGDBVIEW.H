// UsingDBView.h : interface of the CUsingDBView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_USINGDBVIEW_H__B82F4AAF_A5E3_11CF_BC51_C38562E5D356__INCLUDED_)
#define AFX_USINGDBVIEW_H__B82F4AAF_A5E3_11CF_BC51_C38562E5D356__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CUsingDBSet;

class CUsingDBView : public CRecordView
{
protected: // create from serialization only
	CUsingDBView();
	DECLARE_DYNCREATE(CUsingDBView)

public:
	//{{AFX_DATA(CUsingDBView)
	enum{ IDD = IDD_USINGDB_FORM };
	CUsingDBSet* m_pSet;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CUsingDBDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUsingDBView)
	public:
	virtual CRecordset* OnGetRecordset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CUsingDBView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CUsingDBView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in UsingDBView.cpp
inline CUsingDBDoc* CUsingDBView::GetDocument()
   { return (CUsingDBDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USINGDBVIEW_H__B82F4AAF_A5E3_11CF_BC51_C38562E5D356__INCLUDED_)

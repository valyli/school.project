// DatabaseView.h : interface of the CDatabaseView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATABASEVIEW_H__C379762F_442D_11D2_953B_CDD998FF14B6__INCLUDED_)
#define AFX_DATABASEVIEW_H__C379762F_442D_11D2_953B_CDD998FF14B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CDatabaseView : public CFormView
{
protected: // create from serialization only
	CDatabaseView();
	DECLARE_DYNCREATE(CDatabaseView)

public:
	//{{AFX_DATA(CDatabaseView)
	enum { IDD = IDD_DATABASE_FORM };
	double	m_ssn;
	//}}AFX_DATA

// Attributes
public:
	CDatabaseDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatabaseView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDatabaseView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDatabaseView)
	afx_msg void OnButtonFind();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DatabaseView.cpp
inline CDatabaseDoc* CDatabaseView::GetDocument()
   { return (CDatabaseDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATABASEVIEW_H__C379762F_442D_11D2_953B_CDD998FF14B6__INCLUDED_)

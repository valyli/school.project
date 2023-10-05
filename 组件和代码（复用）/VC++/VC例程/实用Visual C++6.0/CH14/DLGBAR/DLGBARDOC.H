// dlgbarDoc.h : interface of the CDlgbarDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLGBARDOC_H__E9683ECD_59B9_11D1_B5D9_BC53D39E0517__INCLUDED_)
#define AFX_DLGBARDOC_H__E9683ECD_59B9_11D1_B5D9_BC53D39E0517__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDlgbarDoc : public CDocument
{
protected: // create from serialization only
	CDlgbarDoc();
	DECLARE_DYNCREATE(CDlgbarDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgbarDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDlgbarDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDlgbarDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBARDOC_H__E9683ECD_59B9_11D1_B5D9_BC53D39E0517__INCLUDED_)

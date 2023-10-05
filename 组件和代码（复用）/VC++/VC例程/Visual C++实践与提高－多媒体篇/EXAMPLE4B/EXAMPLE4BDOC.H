// Example4BDoc.h : interface of the CExample4BDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXAMPLE4BDOC_H__B78C590A_A852_11D4_8EAF_0000B48A052A__INCLUDED_)
#define AFX_EXAMPLE4BDOC_H__B78C590A_A852_11D4_8EAF_0000B48A052A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CExample4BDoc : public CDocument
{
protected: // create from serialization only
	CExample4BDoc();
	DECLARE_DYNCREATE(CExample4BDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExample4BDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExample4BDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CExample4BDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLE4BDOC_H__B78C590A_A852_11D4_8EAF_0000B48A052A__INCLUDED_)

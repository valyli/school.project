// Example4CDoc.h : interface of the CExample4CDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXAMPLE4CDOC_H__B78C592F_A852_11D4_8EAF_0000B48A052A__INCLUDED_)
#define AFX_EXAMPLE4CDOC_H__B78C592F_A852_11D4_8EAF_0000B48A052A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CExample4CDoc : public CDocument
{
protected: // create from serialization only
	CExample4CDoc();
	DECLARE_DYNCREATE(CExample4CDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExample4CDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExample4CDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CExample4CDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLE4CDOC_H__B78C592F_A852_11D4_8EAF_0000B48A052A__INCLUDED_)

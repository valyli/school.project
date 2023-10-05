// PrintItDoc.h : interface of the CPrintItDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRINTITDOC_H__8B30B42A_6C2F_11CD_BC53_E9F379BB6D52__INCLUDED_)
#define AFX_PRINTITDOC_H__8B30B42A_6C2F_11CD_BC53_E9F379BB6D52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPrintItDoc : public CDocument
{
protected: // create from serialization only
	CPrintItDoc();
	DECLARE_DYNCREATE(CPrintItDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrintItDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPrintItDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPrintItDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINTITDOC_H__8B30B42A_6C2F_11CD_BC53_E9F379BB6D52__INCLUDED_)

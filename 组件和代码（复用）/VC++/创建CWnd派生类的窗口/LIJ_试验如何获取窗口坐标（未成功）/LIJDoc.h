// LIJDoc.h : interface of the CLIJDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LIJDOC_H__C5A0B608_D707_4812_AA2F_D96FFBC62DFC__INCLUDED_)
#define AFX_LIJDOC_H__C5A0B608_D707_4812_AA2F_D96FFBC62DFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLIJDoc : public CDocument
{
protected: // create from serialization only
	CLIJDoc();
	DECLARE_DYNCREATE(CLIJDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLIJDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLIJDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLIJDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIJDOC_H__C5A0B608_D707_4812_AA2F_D96FFBC62DFC__INCLUDED_)

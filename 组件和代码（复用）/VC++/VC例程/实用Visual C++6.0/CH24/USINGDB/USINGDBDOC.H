// UsingDBDoc.h : interface of the CUsingDBDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_USINGDBDOC_H__B82F4AAD_A5E3_11CF_BC51_C38562E5D356__INCLUDED_)
#define AFX_USINGDBDOC_H__B82F4AAD_A5E3_11CF_BC51_C38562E5D356__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CUsingDBDoc : public CDocument
{
protected: // create from serialization only
	CUsingDBDoc();
	DECLARE_DYNCREATE(CUsingDBDoc)

// Attributes
public:
	CUsingDBSet m_usingDBSet;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUsingDBDoc)
	public:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CUsingDBDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CUsingDBDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USINGDBDOC_H__B82F4AAD_A5E3_11CF_BC51_C38562E5D356__INCLUDED_)

// TreeVDoc.h : interface of the CTreeVDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TREEVDOC_H__98AE21AD_A463_11CF_BC51_BAE7D2415650__INCLUDED_)
#define AFX_TREEVDOC_H__98AE21AD_A463_11CF_BC51_BAE7D2415650__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CTreeVDoc : public CDocument
{
protected: // create from serialization only
	CTreeVDoc();
	DECLARE_DYNCREATE(CTreeVDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeVDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTreeVDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTreeVDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEVDOC_H__98AE21AD_A463_11CF_BC51_BAE7D2415650__INCLUDED_)

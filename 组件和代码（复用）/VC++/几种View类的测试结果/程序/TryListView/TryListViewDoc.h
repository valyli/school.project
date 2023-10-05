// TryListViewDoc.h : interface of the CTryListViewDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRYLISTVIEWDOC_H__DC52C1B6_8DFB_4EC0_9FCB_8D1DDC014022__INCLUDED_)
#define AFX_TRYLISTVIEWDOC_H__DC52C1B6_8DFB_4EC0_9FCB_8D1DDC014022__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTryListViewDoc : public CDocument
{
protected: // create from serialization only
	CTryListViewDoc();
	DECLARE_DYNCREATE(CTryListViewDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTryListViewDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTryListViewDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTryListViewDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRYLISTVIEWDOC_H__DC52C1B6_8DFB_4EC0_9FCB_8D1DDC014022__INCLUDED_)

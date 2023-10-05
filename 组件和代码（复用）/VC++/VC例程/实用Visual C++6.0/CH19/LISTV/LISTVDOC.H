// ListVDoc.h : interface of the CListVDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTVDOC_H__1CFD0E2B_A393_11CF_BC51_9390FCB46551__INCLUDED_)
#define AFX_LISTVDOC_H__1CFD0E2B_A393_11CF_BC51_9390FCB46551__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CListVDoc : public CDocument
{
protected: // create from serialization only
	CListVDoc();
	DECLARE_DYNCREATE(CListVDoc)

// Attributes
public:

// Operations
public:
	const CStringList& GetElements( );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListVDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation

	virtual ~CListVDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CListVDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CStringList m_listElements;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTVDOC_H__1CFD0E2B_A393_11CF_BC51_9390FCB46551__INCLUDED_)

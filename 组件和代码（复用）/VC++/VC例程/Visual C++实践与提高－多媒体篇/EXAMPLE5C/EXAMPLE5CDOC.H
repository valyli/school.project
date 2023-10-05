// Example5CDoc.h : interface of the CExample5CDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXAMPLE5CDOC_H__F4775C92_9A3E_11D4_B67F_444553540000__INCLUDED_)
#define AFX_EXAMPLE5CDOC_H__F4775C92_9A3E_11D4_B67F_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CExample5CDoc : public CDocument
{
protected: // create from serialization only
	CExample5CDoc();
	DECLARE_DYNCREATE(CExample5CDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExample5CDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExample5CDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CExample5CDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLE5CDOC_H__F4775C92_9A3E_11D4_B67F_444553540000__INCLUDED_)

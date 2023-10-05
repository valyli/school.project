// Exmaple4ADoc.h : interface of the CExmaple4ADoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXMAPLE4ADOC_H__E7CCDF80_9158_11D4_B67F_444553540000__INCLUDED_)
#define AFX_EXMAPLE4ADOC_H__E7CCDF80_9158_11D4_B67F_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CExmaple4ADoc : public CDocument
{
protected: // create from serialization only
	CExmaple4ADoc();
	DECLARE_DYNCREATE(CExmaple4ADoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExmaple4ADoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExmaple4ADoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CExmaple4ADoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXMAPLE4ADOC_H__E7CCDF80_9158_11D4_B67F_444553540000__INCLUDED_)

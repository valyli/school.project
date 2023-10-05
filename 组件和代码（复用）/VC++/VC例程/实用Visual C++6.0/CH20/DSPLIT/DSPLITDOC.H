// DsplitDoc.h : interface of the CDsplitDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DSPLITDOC_H__0C15E28B_D487_11D2_BF13_87F5B9EBB265__INCLUDED_)
#define AFX_DSPLITDOC_H__0C15E28B_D487_11D2_BF13_87F5B9EBB265__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDsplitDoc : public CDocument
{
protected: // create from serialization only
	CDsplitDoc();
	DECLARE_DYNCREATE(CDsplitDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDsplitDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDsplitDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDsplitDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSPLITDOC_H__0C15E28B_D487_11D2_BF13_87F5B9EBB265__INCLUDED_)

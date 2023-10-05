// AutoserverDoc.h : interface of the CAutoserverDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUTOSERVERDOC_H__B282D1CA_DD47_11D2_BF13_996F03973C62__INCLUDED_)
#define AFX_AUTOSERVERDOC_H__B282D1CA_DD47_11D2_BF13_996F03973C62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CAutoserverDoc : public CDocument
{
protected: // create from serialization only
	CAutoserverDoc();
	DECLARE_DYNCREATE(CAutoserverDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoserverDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAutoserverDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAutoserverDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CAutoserverDoc)
	afx_msg double SquareRoot(double dInputVal);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOSERVERDOC_H__B282D1CA_DD47_11D2_BF13_996F03973C62__INCLUDED_)

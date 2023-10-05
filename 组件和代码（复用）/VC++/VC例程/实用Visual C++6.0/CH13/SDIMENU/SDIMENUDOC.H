// sdimenuDoc.h : interface of the CSdimenuDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SDIMENUDOC_H__9B730121_5513_11D1_B5D9_DB30231F0417__INCLUDED_)
#define AFX_SDIMENUDOC_H__9B730121_5513_11D1_B5D9_DB30231F0417__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSdimenuDoc : public CDocument
{
protected: // create from serialization only
	CSdimenuDoc();
	DECLARE_DYNCREATE(CSdimenuDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSdimenuDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSdimenuDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSdimenuDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDIMENUDOC_H__9B730121_5513_11D1_B5D9_DB30231F0417__INCLUDED_)

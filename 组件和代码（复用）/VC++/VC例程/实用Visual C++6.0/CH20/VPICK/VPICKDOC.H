// VPickDoc.h : interface of the CVPickDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VPICKDOC_H__0B84528D_D4C6_11D2_BF13_FBDAC8B2DA65__INCLUDED_)
#define AFX_VPICKDOC_H__0B84528D_D4C6_11D2_BF13_FBDAC8B2DA65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CVPickDoc : public CDocument
{
protected: // create from serialization only
	CVPickDoc();
	DECLARE_DYNCREATE(CVPickDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVPickDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVPickDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVPickDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VPICKDOC_H__0B84528D_D4C6_11D2_BF13_FBDAC8B2DA65__INCLUDED_)

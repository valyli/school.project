// FSDoc.h : interface of the CFSDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FSDOC_H__CFD6F974_3691_11D3_98A9_204C4F4F5020__INCLUDED_)
#define AFX_FSDOC_H__CFD6F974_3691_11D3_98A9_204C4F4F5020__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFSDoc : public CDocument
{
protected: // create from serialization only
	CFSDoc();
	DECLARE_DYNCREATE(CFSDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFSDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFSDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFSDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FSDOC_H__CFD6F974_3691_11D3_98A9_204C4F4F5020__INCLUDED_)

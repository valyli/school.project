// ToolbarDoc.h : interface of the CToolbarDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOOLBARDOC_H__EDCE7FCB_58A0_11D1_B5D9_F552C9B11214__INCLUDED_)
#define AFX_TOOLBARDOC_H__EDCE7FCB_58A0_11D1_B5D9_F552C9B11214__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CToolbarDoc : public CDocument
{
protected: // create from serialization only
	CToolbarDoc();
	DECLARE_DYNCREATE(CToolbarDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolbarDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CToolbarDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CToolbarDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLBARDOC_H__EDCE7FCB_58A0_11D1_B5D9_F552C9B11214__INCLUDED_)

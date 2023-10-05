// FindComDoc.h : interface of the CFindComDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FINDCOMDOC_H__5DF3A2B3_BDFE_4CD1_A8EE_F4CF69B89777__INCLUDED_)
#define AFX_FINDCOMDOC_H__5DF3A2B3_BDFE_4CD1_A8EE_F4CF69B89777__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFindComDoc : public CDocument
{
protected: // create from serialization only
	CFindComDoc();
	DECLARE_DYNCREATE(CFindComDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindComDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFindComDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFindComDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDCOMDOC_H__5DF3A2B3_BDFE_4CD1_A8EE_F4CF69B89777__INCLUDED_)

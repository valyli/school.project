// Try_FormViewDoc.h : interface of the CTry_FormViewDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRY_FORMVIEWDOC_H__B64E806F_861A_4DAC_AAC7_84EF22A9FF79__INCLUDED_)
#define AFX_TRY_FORMVIEWDOC_H__B64E806F_861A_4DAC_AAC7_84EF22A9FF79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTry_FormViewDoc : public CDocument
{
protected: // create from serialization only
	CTry_FormViewDoc();
	DECLARE_DYNCREATE(CTry_FormViewDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTry_FormViewDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTry_FormViewDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTry_FormViewDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRY_FORMVIEWDOC_H__B64E806F_861A_4DAC_AAC7_84EF22A9FF79__INCLUDED_)

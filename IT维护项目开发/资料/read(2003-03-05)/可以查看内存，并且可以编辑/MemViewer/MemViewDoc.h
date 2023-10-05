// MemViewDoc.h : interface of the CMemViewDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMVIEWDOC_H__4BE8C4C0_CE02_11D5_9244_0050DAB40CEC__INCLUDED_)
#define AFX_MEMVIEWDOC_H__4BE8C4C0_CE02_11D5_9244_0050DAB40CEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMemViewDoc : public CDocument
{
protected: // create from serialization only
	CMemViewDoc();
	DECLARE_DYNCREATE(CMemViewDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMemViewDoc)
	public:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMemViewDoc();
protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMemViewDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEMVIEWDOC_H__4BE8C4C0_CE02_11D5_9244_0050DAB40CEC__INCLUDED_)

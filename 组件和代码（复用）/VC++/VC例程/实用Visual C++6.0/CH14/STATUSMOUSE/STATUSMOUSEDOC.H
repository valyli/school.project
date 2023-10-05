// StatusMouseDoc.h : interface of the CStatusMouseDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATUSMOUSEDOC_H__44E6900B_5A1C_11D1_B5D9_F41150DD6517__INCLUDED_)
#define AFX_STATUSMOUSEDOC_H__44E6900B_5A1C_11D1_B5D9_F41150DD6517__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CStatusMouseDoc : public CDocument
{
protected: // create from serialization only
	CStatusMouseDoc();
	DECLARE_DYNCREATE(CStatusMouseDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatusMouseDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStatusMouseDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CStatusMouseDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATUSMOUSEDOC_H__44E6900B_5A1C_11D1_B5D9_F41150DD6517__INCLUDED_)

// PropertyAppDoc.h : interface of the CPropertyAppDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROPERTYAPPDOC_H__3508914A_4921_11D5_9EAD_00E04C6832A0__INCLUDED_)
#define AFX_PROPERTYAPPDOC_H__3508914A_4921_11D5_9EAD_00E04C6832A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPropertyAppDoc : public CDocument
{
protected: // create from serialization only
	CPropertyAppDoc();
	DECLARE_DYNCREATE(CPropertyAppDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertyAppDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPropertyAppDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPropertyAppDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTYAPPDOC_H__3508914A_4921_11D5_9EAD_00E04C6832A0__INCLUDED_)

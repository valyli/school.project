// TryListInFormViewDoc.h : interface of the CTryListInFormViewDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRYLISTINFORMVIEWDOC_H__C19FD1DF_EF5C_4F7A_90A3_7BB8BE0A53B4__INCLUDED_)
#define AFX_TRYLISTINFORMVIEWDOC_H__C19FD1DF_EF5C_4F7A_90A3_7BB8BE0A53B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTryListInFormViewDoc : public CDocument
{
protected: // create from serialization only
	CTryListInFormViewDoc();
	DECLARE_DYNCREATE(CTryListInFormViewDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTryListInFormViewDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTryListInFormViewDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTryListInFormViewDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRYLISTINFORMVIEWDOC_H__C19FD1DF_EF5C_4F7A_90A3_7BB8BE0A53B4__INCLUDED_)

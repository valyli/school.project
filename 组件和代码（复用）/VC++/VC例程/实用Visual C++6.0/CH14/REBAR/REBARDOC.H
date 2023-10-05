// rebarDoc.h : interface of the CRebarDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_REBARDOC_H__64C10F6B_5AA6_11D1_B5D9_C30D74116017__INCLUDED_)
#define AFX_REBARDOC_H__64C10F6B_5AA6_11D1_B5D9_C30D74116017__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRebarDoc : public CDocument
{
protected: // create from serialization only
	CRebarDoc();
	DECLARE_DYNCREATE(CRebarDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRebarDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRebarDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRebarDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REBARDOC_H__64C10F6B_5AA6_11D1_B5D9_C30D74116017__INCLUDED_)

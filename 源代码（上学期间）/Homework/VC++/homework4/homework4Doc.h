// homework4Doc.h : interface of the CHomework4Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HOMEWORK4DOC_H__B7CD14FD_CAC0_11D5_9486_5254AB113BB2__INCLUDED_)
#define AFX_HOMEWORK4DOC_H__B7CD14FD_CAC0_11D5_9486_5254AB113BB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHomework4Doc : public CDocument
{
protected: // create from serialization only
	CHomework4Doc();
	DECLARE_DYNCREATE(CHomework4Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHomework4Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHomework4Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHomework4Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOMEWORK4DOC_H__B7CD14FD_CAC0_11D5_9486_5254AB113BB2__INCLUDED_)

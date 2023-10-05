// homework5Doc.h : interface of the CHomework5Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HOMEWORK5DOC_H__A26C8F0C_CBAA_11D5_9486_5254AB113BB2__INCLUDED_)
#define AFX_HOMEWORK5DOC_H__A26C8F0C_CBAA_11D5_9486_5254AB113BB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct PointQueue
{
	int count;
	POINT* apt;
};

class CHomework5Doc : public CDocument
{
protected: // create from serialization only
	CHomework5Doc();
	DECLARE_DYNCREATE(CHomework5Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHomework5Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	int m_count;
	PointQueue* m_apt;
	virtual ~CHomework5Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHomework5Doc)
	afx_msg void OnAppExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOMEWORK5DOC_H__A26C8F0C_CBAA_11D5_9486_5254AB113BB2__INCLUDED_)

// MailClientDoc.h : interface of the CMailClientDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAILCLIENTDOC_H__E087E9D9_DB17_11D2_BF13_AA406FC81D62__INCLUDED_)
#define AFX_MAILCLIENTDOC_H__E087E9D9_DB17_11D2_BF13_AA406FC81D62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMailClientDoc : public CDocument
{
protected: // create from serialization only
	CMailClientDoc();
	DECLARE_DYNCREATE(CMailClientDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMailClientDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMailClientDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMailClientDoc)
	afx_msg void OnFileReceive();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAILCLIENTDOC_H__E087E9D9_DB17_11D2_BF13_AA406FC81D62__INCLUDED_)

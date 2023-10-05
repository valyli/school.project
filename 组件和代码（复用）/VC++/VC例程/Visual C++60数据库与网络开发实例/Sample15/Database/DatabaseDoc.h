// DatabaseDoc.h : interface of the CDatabaseDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATABASEDOC_H__C379762D_442D_11D2_953B_CDD998FF14B6__INCLUDED_)
#define AFX_DATABASEDOC_H__C379762D_442D_11D2_953B_CDD998FF14B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "RecordsetEmployees.h"

class CDatabaseDoc : public CDocument
{
protected: // create from serialization only
	CDatabaseDoc();
	DECLARE_DYNCREATE(CDatabaseDoc)

// Custom member functions and variables
public:
	CRecordsetEmployees * GetRecSet() {return m_pSet;}
	BOOL IsFileOpen() {return m_bFileOpen;}

protected:
	CDatabase * m_pDB;
	CRecordsetEmployees * m_pSet;
	BOOL m_bFileOpen;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatabaseDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDatabaseDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDatabaseDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATABASEDOC_H__C379762D_442D_11D2_953B_CDD998FF14B6__INCLUDED_)

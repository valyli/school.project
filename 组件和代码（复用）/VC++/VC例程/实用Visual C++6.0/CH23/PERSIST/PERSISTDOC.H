// PersistDoc.h : interface of the CPersistDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PERSISTDOC_H__0E26626F_D58C_11D2_BF13_BC2C81A6F265__INCLUDED_)
#define AFX_PERSISTDOC_H__0E26626F_D58C_11D2_BF13_BC2C81A6F265__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPersistDoc : public CDocument
{
protected: // create from serialization only
	CPersistDoc();
	DECLARE_DYNCREATE(CPersistDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPersistDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	CObArray m_BlobArray;
	UINT m_uClipFormat;			//** New Format Member
	void DeleteBlobs();
	virtual ~CPersistDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	
// Generated message map functions
protected:
	//{{AFX_MSG(CPersistDoc)
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PERSISTDOC_H__0E26626F_D58C_11D2_BF13_BC2C81A6F265__INCLUDED_)

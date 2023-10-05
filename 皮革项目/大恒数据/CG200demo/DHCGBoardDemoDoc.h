// DHCGBoardDemoDoc.h : interface of the CDHCGBoardDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DHCGBOARDDEMODOC_H__591A738F_C6AB_11D4_8E81_5254AB30C250__INCLUDED_)
#define AFX_DHCGBOARDDEMODOC_H__591A738F_C6AB_11D4_8E81_5254AB30C250__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDHCGBoardDemoDoc : public CDocument
{
protected: // create from serialization only
	CDHCGBoardDemoDoc();
	DECLARE_DYNCREATE(CDHCGBoardDemoDoc)

// Attributes
public:
	HANDLE hdib;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDHCGBoardDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDHCGBoardDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	void FreeDIBHandle();
protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDHCGBoardDemoDoc)
	afx_msg void OnFileSaveAs();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DHCGBOARDDEMODOC_H__591A738F_C6AB_11D4_8E81_5254AB30C250__INCLUDED_)

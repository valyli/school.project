#if !defined(AFX_MDIBILLDOC_H__73EB1936_6B2D_11CD_BC53_D9F8B661B44D__INCLUDED_)
#define AFX_MDIBILLDOC_H__73EB1936_6B2D_11CD_BC53_D9F8B661B44D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MDIBillDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMDIBillDoc document

class CMDIBillDoc : public CDocument
{
protected:
	CMDIBillDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMDIBillDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDIBillDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	int GetBillCount();
	virtual ~CMDIBillDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	int m_nBills;
	//{{AFX_MSG(CMDIBillDoc)
	afx_msg void OnEditAddBill();
	afx_msg void OnEditRemoveBill();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDIBILLDOC_H__73EB1936_6B2D_11CD_BC53_D9F8B661B44D__INCLUDED_)

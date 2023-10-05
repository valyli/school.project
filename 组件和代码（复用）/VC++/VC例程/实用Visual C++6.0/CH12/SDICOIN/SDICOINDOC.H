// SDICoinDoc.h : interface of the CSDICoinDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SDICOINDOC_H__B038A62B_AD17_11D0_B1A4_20964CC10000__INCLUDED_)
#define AFX_SDICOINDOC_H__B038A62B_AD17_11D0_B1A4_20964CC10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSDICoinDoc : public CDocument
{
protected: // create from serialization only
	CSDICoinDoc();
	DECLARE_DYNCREATE(CSDICoinDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSDICoinDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	int GetCoinCount();
	virtual ~CSDICoinDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	int m_nCoins;
	//{{AFX_MSG(CSDICoinDoc)
	afx_msg void OnEditAddCoin();
	afx_msg void OnEditRemoveCoin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDICOINDOC_H__B038A62B_AD17_11D0_B1A4_20964CC10000__INCLUDED_)

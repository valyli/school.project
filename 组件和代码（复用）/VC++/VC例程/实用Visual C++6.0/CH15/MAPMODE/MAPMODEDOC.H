// MapModeDoc.h : interface of the CMapModeDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPMODEDOC_H__5A16F2AB_D3F4_11D2_BF13_9D35B3385D65__INCLUDED_)
#define AFX_MAPMODEDOC_H__5A16F2AB_D3F4_11D2_BF13_9D35B3385D65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMapModeDoc : public CDocument
{
protected: // create from serialization only
	CMapModeDoc();
	DECLARE_DYNCREATE(CMapModeDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapModeDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMapModeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMapModeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPMODEDOC_H__5A16F2AB_D3F4_11D2_BF13_9D35B3385D65__INCLUDED_)

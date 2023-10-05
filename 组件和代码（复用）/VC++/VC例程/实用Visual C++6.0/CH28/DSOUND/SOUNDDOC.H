// SoundDoc.h : interface of the CSoundDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOUNDDOC_H__27C9F38B_D960_11D2_BF13_FB46B2140062__INCLUDED_)
#define AFX_SOUNDDOC_H__27C9F38B_D960_11D2_BF13_FB46B2140062__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSoundDoc : public CDocument
{
protected: // create from serialization only
	CSoundDoc();
	DECLARE_DYNCREATE(CSoundDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoundDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSoundDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSoundDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOUNDDOC_H__27C9F38B_D960_11D2_BF13_FB46B2140062__INCLUDED_)

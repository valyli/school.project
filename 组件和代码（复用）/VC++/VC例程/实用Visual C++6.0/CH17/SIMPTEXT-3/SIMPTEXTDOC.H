// SimpTextDoc.h : interface of the CSimpTextDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMPTEXTDOC_H__4157B972_6DC7_11CD_BC53_EDB715115552__INCLUDED_)
#define AFX_SIMPTEXTDOC_H__4157B972_6DC7_11CD_BC53_EDB715115552__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSimpTextDoc : public CDocument
{
protected: // create from serialization only
	CSimpTextDoc();
	DECLARE_DYNCREATE(CSimpTextDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpTextDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSimpTextDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSimpTextDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPTEXTDOC_H__4157B972_6DC7_11CD_BC53_EDB715115552__INCLUDED_)

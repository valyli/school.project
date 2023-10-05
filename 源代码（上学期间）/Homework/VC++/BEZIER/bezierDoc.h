// bezierDoc.h : interface of the CBezierDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BEZIERDOC_H__72ED866C_B234_4602_A381_C080480927C9__INCLUDED_)
#define AFX_BEZIERDOC_H__72ED866C_B234_4602_A381_C080480927C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
typedef CArray<CPoint, CPoint&> CArrayPoint;
typedef CTypedPtrList<CObList, CArrayPoint*> CListPoint;

class CBezierDoc : public COleDocument
{
protected: // create from serialization only
	CBezierDoc();
	DECLARE_DYNCREATE(CBezierDoc)

// Attributes
public:
	//绘图过程中用于存储正在绘制的结点
	CArrayPoint* m_Temp;
	//用于存储已经绘制好的闭合贝赛尔曲线的结点
	CListPoint m_List;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBezierDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual ~CBezierDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBezierDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BEZIERDOC_H__72ED866C_B234_4602_A381_C080480927C9__INCLUDED_)

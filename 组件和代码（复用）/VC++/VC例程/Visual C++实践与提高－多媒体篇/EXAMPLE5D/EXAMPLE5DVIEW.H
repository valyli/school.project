// Example5DView.h : interface of the CExample5DView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXAMPLE5DVIEW_H__F4A0C2AC_9AC8_11D4_B67F_444553540000__INCLUDED_)
#define AFX_EXAMPLE5DVIEW_H__F4A0C2AC_9AC8_11D4_B67F_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CExample5DView : public CView
{
protected: // create from serialization only
	CExample5DView();
	DECLARE_DYNCREATE(CExample5DView)

// Attributes
public:
	CExample5DDoc* GetDocument();

// Operations
public:

protected:
	POINT m_clientPt;		//图像所在位置
	int m_playIndex;		//图像的索引
	void CreateImageList();	//用于创建图像列表的函数
	CImageList m_imageList;	//图像列表对象
	int m_imageNumber;		//图像列表中图像的数量
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExample5DView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExample5DView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CExample5DView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Example5DView.cpp
inline CExample5DDoc* CExample5DView::GetDocument()
   { return (CExample5DDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLE5DVIEW_H__F4A0C2AC_9AC8_11D4_B67F_444553540000__INCLUDED_)

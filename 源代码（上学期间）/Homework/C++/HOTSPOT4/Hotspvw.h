// hotspvw.h : interface of the CHotspot4View class
//
/////////////////////////////////////////////////////////////////////////////

class CHotspot4View : public CView
{
protected: // create from serialization only
	CHotspot4View();
	DECLARE_DYNCREATE(CHotspot4View)

// Attributes
public:
	CHotspot4Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHotspot4View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHotspot4View();
	void DrawLine(CPoint point1, CPoint point2);
	void OutlineRegion(void);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	CPoint m_oldPoint;		//Holds coordinates of previous vertex.
	CPen* m_oldPen;
	int m_oldMode;

// Generated message map functions
protected:
	//{{AFX_MSG(CHotspot4View)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnModeDefine();
	afx_msg void OnModeTest();
	afx_msg void OnUpdateModeTest(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileNewhotspot(CCmdUI* pCmdUI);
	afx_msg void OnFileNewhotspot();
	afx_msg void OnUpdateFileSavehotspot(CCmdUI* pCmdUI);
	afx_msg void OnFileSavehotspot();
	afx_msg void OnEditEdithotspot();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in hotspvw.cpp
inline CHotspot4Doc* CHotspot4View::GetDocument()
   { return (CHotspot4Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

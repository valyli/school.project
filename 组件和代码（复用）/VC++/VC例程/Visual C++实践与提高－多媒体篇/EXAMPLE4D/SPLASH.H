// CG: This file was added by the Splash Screen component.

#ifndef _SPLASH_SCRN_
#define _SPLASH_SCRN_

// Splash.h : header file
//

/////////////////////////////////////////////////////////////////////////////
//   Splash Screen class

class CSplashWnd : public CWnd
{
// Construction
protected:
	CSplashWnd();

// Attributes:
public:
	CBitmap m_bitmap;

// Operations
public:
	static void EnableSplashScreen(BOOL bEnable = TRUE);
	static void ShowSplashScreen(CWnd* pParentWnd = NULL);
	static BOOL PreTranslateAppMessage(MSG* pMsg);
public:
	CDC m_dcText,m_dcImage;//显示dc的兼容内存dc
	CBitmap* m_pBitmap;//位图对象指针
	CBitmap* m_pOldBitmapText,
	*m_pOldBitmap;//跟踪内存dc中的原位图
	CRgn m_rgn;//用于生成矩形区域
	CRect   m_TextRect ;//显示文字的矩形区域
	int     m_nCurPos  ;//文字当前位置
	
	void CSplashWnd::DrawText(CDC *pDC,int x, int y, int nAlign,CString sFontName, int nFONTSIZE0,COLORREF crTextColor, CString sText);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplashWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	~CSplashWnd();
	virtual void PostNcDestroy();

protected:
	BOOL Create(CWnd* pParentWnd = NULL);
	void HideSplashScreen();
	static BOOL c_bShowSplashWnd;
	static CSplashWnd* c_pSplashWnd;

// Generated message map functions
protected:
	//{{AFX_MSG(CSplashWnd)
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#endif

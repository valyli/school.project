// ChildView.h : interface of the CChildView class
// 编码: Leezy
// 最后修改日期：5.8
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDVIEW_H__94E17C6B_1EE0_11D4_A0AA_0080AD76C3BA__INCLUDED_)
#define AFX_CHILDVIEW_H__94E17C6B_1EE0_11D4_A0AA_0080AD76C3BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


////////////////////////////////Sound Effection ID /////////////////////////
#define  SNDEFF_COUNT      4
#define  SNDEFF_MUSIC      0
#define  SNDEFF_KILL       1
#define  SNDEFF_ACTIVE     2
#define  SNDEFF_GAMEOVER   3

/////////////////////////////////////////////////////////////////////////////
// CChildView window
#include "mmsystem.h"
#include "ddraw.h"
#include "dsound.h"

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:
	SameBallMap m_dMap;//该类可以继承所有有关的函数
private:
	IDirectSound* m_lpDirectSound;
	IDirectSoundBuffer* m_lpDSMusic;
	IDirectSoundBuffer* m_lpDSKill;
	IDirectSoundBuffer* m_lpDSActive;
	IDirectSoundBuffer* m_lpDSGameOver;
	IDirectDraw* m_pIDirectDraw;
	IDirectDrawSurface* m_lpDDSPrimary;
	IDirectDrawSurface* m_lpDDSSource;
	IDirectDrawPalette* m_lpDDPalette;
	CRect m_dRed;
	CRect m_dBlue;
	CRect m_dGreen;
	CRect m_dBlack;
	int   m_iActivePage;//

// Operations
public:
private:
	HRESULT CChildView::CreateSecondarySurface(int cx, int cy, IDirectDrawSurface **ppDDS);
	HRESULT CChildView::LoadDDBitmap(UINT nID, IDirectDrawSurface **ppDDS);
	HRESULT CChildView::CopyDDBitmap(CBitmap *pbmImage, IDirectDrawSurface *pDDS);
	HRESULT CChildView::ReLoadDDBitmap(UINT nID, IDirectDrawSurface *pDDS);
	HRESULT CChildView::LoadDDPalette(UINT idBitmap, IDirectDrawPalette **ppDDP);



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildView)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public://职能函数
	IDirectSoundBuffer* m_grlpSoundEffect[4];
	void PlaySoundEffect(int nSound,DWORD nFlag=0);
	BOOL RestoreDSBuffers();
	BOOL InitBuffers();
	BOOL InitDD();
	BOOL InitDS();
	void FreeDS();
	void FreeDD();
	void GameOver(int ndCurrentScore);
	BOOL m_bIsActive;//
	BOOL m_bNeedPaint;//
	void ShowMessage(CString nS);
	CPoint m_dPointMouseAt;//
	void ShowStatus(int nBallCount, int nScore=-1, int nRemain=-1);
	int m_iObjSize;//
	UINT m_uBmpID;
	virtual ~CChildView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CChildView)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnFileNew();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnViewScorelist();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__94E17C6B_1EE0_11D4_A0AA_0080AD76C3BA__INCLUDED_)

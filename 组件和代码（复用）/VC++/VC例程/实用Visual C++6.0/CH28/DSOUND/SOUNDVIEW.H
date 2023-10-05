// SoundView.h : interface of the CSoundView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOUNDVIEW_H__27C9F38D_D960_11D2_BF13_FB46B2140062__INCLUDED_)
#define AFX_SOUNDVIEW_H__27C9F38D_D960_11D2_BF13_FB46B2140062__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "mmsystem.h"
#include "DSOUND.H"
#include "math.h"

class CSoundView : public CView
{
protected: // create from serialization only
	CSoundView();
	DECLARE_DYNCREATE(CSoundView)

// Attributes
public:
	CSoundDoc* GetDocument();
	IDirectSound*			m_pDSObject;
	IDirectSoundBuffer*		m_pDSBuffer;
	IDirectSoundBuffer*		m_pDSMix;
	DSBUFFERDESC			m_DSBufferDesc;
	void PlayFreq(double dFreq);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoundView)
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
	virtual ~CSoundView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSoundView)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SoundView.cpp
inline CSoundDoc* CSoundView::GetDocument()
   { return (CSoundDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOUNDVIEW_H__27C9F38D_D960_11D2_BF13_FB46B2140062__INCLUDED_)

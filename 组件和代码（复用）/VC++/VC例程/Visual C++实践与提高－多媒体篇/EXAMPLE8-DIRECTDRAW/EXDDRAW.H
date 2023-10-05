// ExDDraw.h : main header file for the EXDDRAW application
//

#if !defined(AFX_EXDDRAW_H__893E1AA4_A6BF_11D4_B67F_444553540000__INCLUDED_)
#define AFX_EXDDRAW_H__893E1AA4_A6BF_11D4_B67F_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include"ddraw.h"
/////////////////////////////////////////////////////////////////////////////
// CExDDrawApp:
// See ExDDraw.cpp for the implementation of this class
//
class CExDDrawApp : public CWinApp
{
public:
	CExDDrawApp();
public:
	LPDIRECTDRAW            lpDD;           // DirectDraw对象
    LPDIRECTDRAWSURFACE     lpDDSPrimary;   // DirectDraw主表面
    LPDIRECTDRAWSURFACE     lpDDSBack; // DirectDraw后备缓冲区
	LPDIRECTDRAWPALETTE     lpDDPal;        // DirectDraw调色板
	LPDIRECTDRAWSURFACE     lpDDSOne;       // 离屏表面 1
	int						m_EndApp;
	int                     m_total;
public:
	HRESULT              restoreAll(  );
	int					 updateFrame(  );
	IDirectDrawPalette * DDLoadPalette(IDirectDraw *pdd, LPCSTR szBitmap);
    IDirectDrawSurface * DDLoadBitmap(IDirectDraw *pdd, LPCSTR szBitmap, int dx, int dy);
    HRESULT              DDReLoadBitmap(IDirectDrawSurface *pdds, LPCSTR szBitmap);
    HRESULT              DDCopyBitmap(IDirectDrawSurface *pdds, HBITMAP hbm, int x, int y, int dx, int dy);
	HRESULT              DDSetColorKey(IDirectDrawSurface *pdds, COLORREF rgb);
    DWORD                DDColorMatch(IDirectDrawSurface *pdds, COLORREF rgb);
	BOOL                 initFail(HWND hwnd);
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExDDrawApp)
	public:
	virtual BOOL InitInstance();
	virtual int Run();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CExDDrawApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXDDRAW_H__893E1AA4_A6BF_11D4_B67F_444553540000__INCLUDED_)

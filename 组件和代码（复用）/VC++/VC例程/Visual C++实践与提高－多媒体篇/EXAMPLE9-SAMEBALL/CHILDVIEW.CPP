// ChildView.cpp : implementation of the CChildView class
// 编码: Leezy
// 最后修改日期：5.9
//

#include "stdafx.h"
#include "SameBall.h"
#include "Ball.h"
#include "MapNode.h"
#include "SameBallMap.h"
#include "ChildView.h"
#include "mainfrm.h"
#include "NameInDlg.h"
#include "ScoreList.h"
#include "wave.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef _DEBUG
#define OutMg(x) MessageBox(x);
#else
#define OutMg(x) ;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildView

CChildView::CChildView()
{
	for(int i=0;i<SNDEFF_COUNT;i++)
		m_grlpSoundEffect[i]=NULL;
	m_lpDirectSound=NULL;

	m_pIDirectDraw=NULL;
	m_lpDDSPrimary=NULL;
	m_lpDDSSource=NULL;
	m_lpDDPalette=NULL;
	m_dPointMouseAt.x=-1;
	m_dPointMouseAt.y=-1;
	m_bIsActive=true;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_WM_TIMER()
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_VIEW_SCORELIST, OnViewScorelist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	HBRUSH hBrush;
	hBrush=(HBRUSH)GetStockObject(BLACK_BRUSH);
	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), hBrush, NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	m_bNeedPaint=true;
	
	// Do not call CWnd::OnPaint() for painting messages
}


BOOL CChildView::InitDD()
{
		// 初始化目标Rect				
		m_dMap.SetSize(m_iObjSize);
		// 计算静态源图位置
		m_dRed.left=0;
		m_dRed.top=0;
		m_dRed.right=m_iObjSize-1;
		m_dRed.bottom=m_iObjSize-1;
		m_dGreen.CopyRect(m_dRed);
		m_dGreen.OffsetRect(0,m_iObjSize);
		m_dBlue.CopyRect(m_dGreen);
		m_dBlue.OffsetRect(0,m_iObjSize);
		m_dBlack.CopyRect(m_dBlue);
		m_dBlack.OffsetRect(0,m_iObjSize*4);
		m_iActivePage=0;
		

		HRESULT hr;
		hr = DirectDrawCreate(NULL,&m_pIDirectDraw,NULL);
		if FAILED( hr )
		{
			MessageBox("DirectDraw 初始化错！\nDirectDrawCreate","Line:65");
		} // if

		// Set our cooperative level to be windowed...
		hr = m_pIDirectDraw->SetCooperativeLevel(m_hWnd,
						DDSCL_NORMAL);
		if FAILED( hr ) 
		{
			MessageBox("DirectDraw 初始化错！\nSetCooperativeLevel","Line:73");
		} // if

		// Create our primary surface
		DDSURFACEDESC ddsd;
		ZeroMemory(&ddsd,sizeof(ddsd));
		ddsd.dwSize = sizeof(ddsd);
		ddsd.dwFlags = DDSD_CAPS;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
    
		hr = m_pIDirectDraw->CreateSurface(&ddsd,&m_lpDDSPrimary,NULL);
		if ( FAILED( hr ) ) 
		{
			MessageBox("DirectDraw 初始化错！\nCreateSurface","Line:86");
		} // if

		// Since we're windowed, we need to create a clipper
		// and attach it to the primary surface.
		IDirectDrawClipper* lpDDClipper;
		hr = m_pIDirectDraw->CreateClipper(0,&lpDDClipper,NULL);
		if ( FAILED( hr ) ) {
			MessageBox("DirectDraw 初始化错！\nCreateClipper","Line:94");
		} // if
		CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
		ASSERT(pFrame);
		hr = lpDDClipper->SetHWnd(0,pFrame->GetSafeHwnd());
		if ( FAILED( hr ) ) 
		{
			MessageBox("DirectDraw 初始化错！\nSetHWnd","Line:101");
		} // if

		hr = m_lpDDSPrimary->SetClipper(lpDDClipper);
		if ( FAILED( hr ) ) 
		{
			MessageBox("DirectDraw 初始化错！\nSetClipper","Line:107");
		} // if

		// Check the surface format...will we need a palette?
		DDPIXELFORMAT ddpf;
		ZeroMemory(&ddpf,sizeof(ddpf));
		ddpf.dwSize = sizeof(ddpf);
		hr = m_lpDDSPrimary->GetPixelFormat(&ddpf);
		if ( FAILED( hr ) ) 
		{
			MessageBox("DirectDraw 初始化错！\nGetPixelFormat","Line:117");
		} // if

		if ( ddpf.dwFlags & DDPF_PALETTEINDEXED8 ) {
			// We are palettized, so create a palette and attach it to
			// the primary surface.
			hr = LoadDDPalette(IDB_BALL64,&m_lpDDPalette);
			if ( FAILED( hr ) ) 
			{
			MessageBox("DirectDraw 初始化错！\nLoadDDPalette","Line:126");
			} // if

			m_lpDDSPrimary->SetPalette(m_lpDDPalette);
			if ( FAILED( hr ) ) 
			{
			MessageBox("DirectDraw 初始化错！\nSetPalette","Line:132");
			} // if
		} // if

		// Load our table bitmap
	hr = LoadDDBitmap(m_uBmpID,&m_lpDDSSource); 
	lpDDClipper->Release();
	if(SUCCEEDED(hr))
	{
//		m_iDrawMode=DRAWMODE_DIRECTDRAW;
		return true;
	}
	else
	{
		MessageBox("DirectDraw 调用失败！\n程序无法继续，对不起！","error");
//		m_iDrawMode=DRAWMODE_WINGDI;
		PostMessage(WM_QUIT);				// will be removed
		return false;
	}


}

HRESULT CChildView::CreateSecondarySurface(int cx, int cy, IDirectDrawSurface **ppDDS)
{
	// Check our pointer
	ASSERT(ppDDS != NULL);
	if ( ppDDS == NULL ) {
		// NULL input pointer...
		return E_POINTER;
	} // if

	// Complete the surface description structure
	DDSURFACEDESC ddsd;
	ZeroMemory(&ddsd,sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	ddsd.dwWidth = cx;
	ddsd.dwHeight = cy;

	HRESULT hr = m_pIDirectDraw->CreateSurface(&ddsd,ppDDS,NULL);//&pIDDSTemp,NULL);
    if ( FAILED(hr) ) {
		// Some error
		*ppDDS = NULL;
		return hr;
	} // if


	return hr;
}

HRESULT CChildView::LoadDDBitmap(UINT nID, IDirectDrawSurface **ppDDS)
{

	ASSERT(ppDDS != NULL);
	if ( ppDDS == NULL ) {
		// NULL input pointer...
		return E_POINTER;
	} // if

	// Pull the bitmap from resources
	CBitmap bmImage;
	VERIFY(bmImage.LoadBitmap(nID));

	// Determine its size
	BITMAP bm;
	bmImage.GetBitmap(&bm);

	// Create a surface to contain the bitmap
	HRESULT hr = CreateSecondarySurface(bm.bmWidth,bm.bmHeight,ppDDS);//&pIDDSTemp);
    if ( FAILED(hr) ) {
		// Some error
		*ppDDS = NULL;
		return hr;
	} // if

	// Copy the bitmap to the surface
	hr = CopyDDBitmap(&bmImage,*ppDDS);//pIDDSTemp);
    if ( FAILED(hr) ) {
		// Some error
		*ppDDS = NULL;
		return hr;
	} // if


	return hr;

}

HRESULT CChildView::CopyDDBitmap(CBitmap *pbmImage, IDirectDrawSurface *pDDS)
{
	// Restore the surface
    pDDS->Restore();

	// Create a memory DC to contain the bitmap
	CDC dcImage;
	dcImage.CreateCompatibleDC(NULL);
	CBitmap* pBitmapMono = (CBitmap*)dcImage.SelectObject(pbmImage);

	// Determine its size
	BITMAP bm;
	pbmImage->GetBitmap(&bm);

	// Complete the surface description
	DDSURFACEDESC ddsd;
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
	pDDS->GetSurfaceDesc(&ddsd);

	// Copy in the bitmap
	HDC hdc = NULL;
	HRESULT hr = pDDS->GetDC(&hdc);
    if ( SUCCEEDED(hr) ) {
		::StretchBlt(hdc,0,0,ddsd.dwWidth,ddsd.dwHeight,dcImage,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
		pDDS->ReleaseDC(hdc);
    } // if

	// Clean up
	dcImage.SelectObject(pBitmapMono);

	return hr;
}

HRESULT CChildView::ReLoadDDBitmap(UINT nID, IDirectDrawSurface *pDDS)
{
	// Pull the bitmap from resources
	CBitmap bmImage;
	VERIFY(bmImage.LoadBitmap(nID));

	// Copy the bitmap back to the surface
	return CopyDDBitmap(&bmImage,pDDS);

}

HRESULT CChildView::LoadDDPalette(UINT idBitmap, IDirectDrawPalette **ppDDP)
{
	PALETTEENTRY ape[256];
	for ( int i = 0; i < 256; i++ ) {
		ape[i].peRed   = (BYTE)(((i >> 5) & 0x07) * 255 / 7);
		ape[i].peGreen = (BYTE)(((i >> 2) & 0x07) * 255 / 7);
		ape[i].peBlue  = (BYTE)(((i >> 0) & 0x03) * 255 / 3);
		ape[i].peFlags = (BYTE)0;
	} // for
    HRSRC hBitmap = NULL;
    if ( (hBitmap = ::FindResource(NULL,MAKEINTRESOURCE(idBitmap),RT_BITMAP))) {
		LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)::LockResource(::LoadResource(NULL,hBitmap));
		if ( lpbi != NULL ) {
			RGBQUAD* prgb = (RGBQUAD*)((BYTE*)lpbi + lpbi->biSize);
			int iNumColors;
			if (lpbi == NULL || lpbi->biSize < sizeof(BITMAPINFOHEADER))
				iNumColors = 0;
			else if (lpbi->biBitCount > 8)
				iNumColors = 0;
			else if (lpbi->biClrUsed == 0)
				iNumColors = 1 << lpbi->biBitCount;
			else
				iNumColors = lpbi->biClrUsed;

			//  Pull the color information
			for( i = 0; i < iNumColors; i++ ) {
				ape[i].peRed   = prgb[i].rgbRed;
				ape[i].peGreen = prgb[i].rgbGreen;
				ape[i].peBlue  = prgb[i].rgbBlue;
				ape[i].peFlags = 0;
			} // for
		} // if
    } // if

	HRESULT hr = m_pIDirectDraw->CreatePalette(DDPCAPS_8BIT,ape,ppDDP,NULL);//&pIDDPTemp,NULL);
    if ( FAILED(hr) ) {
		// Some error
		*ppDDP = NULL;
		return hr;
	} // if

	return hr;

}

BOOL CChildView::DestroyWindow() 
{
	FreeDD();
	FreeDS();
	KillTimer(1);	
	return CWnd ::DestroyWindow();
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd ::OnCreate(lpCreateStruct) == -1)
		return -1;
	if(InitDD())
		OutMg("InitDD OK");
	if(InitDS())
		OutMg("InitDS OK");
	PlaySoundEffect(SNDEFF_MUSIC,DSBPLAY_LOOPING);
	m_dMap.ReNew();				// modified by leezy May.20
	m_bNeedPaint=true;
	SetTimer(1,60,NULL);
	return 0;
}

void CChildView::OnFileNew() 
{
	m_dMap.ReNew();
	m_bNeedPaint=true;
	ShowStatus(-1,0,150);		// add by leezy May.20
	ShowMessage("新游戏");

}

void CChildView::ShowStatus(int nBallCount, int nScore, int nRemain)
{
	CString dS;
	CSameBallApp* pApp;
	pApp=(CSameBallApp*)AfxGetApp();
	if(nBallCount>=0)
	{
		dS.Format("选定：   %5d",nBallCount);
		((CMainFrame*)pApp->m_pMainWnd)->ShowStatus(1,dS);
	}
	if(nBallCount>=2)
	{
		nBallCount-=2;
		dS.Format("分值：   %5d",nBallCount*nBallCount);
		((CMainFrame*)pApp->m_pMainWnd)->ShowStatus(2,dS);
	}
	else
	{
		dS.Format("分值：   %5d",0);
		((CMainFrame*)pApp->m_pMainWnd)->ShowStatus(2,dS);
	}
	if(nScore>=0)
	{
		dS.Format("已得分： %5d",nScore);
		((CMainFrame*)pApp->m_pMainWnd)->ShowStatus(3,dS);
	}
	if(nRemain>=0)
	{
		dS.Format("剩余：   %5d",nRemain);
		((CMainFrame*)pApp->m_pMainWnd)->ShowStatus(4,dS);
	}


}

void CChildView::OnMouseMove(UINT nFlags, CPoint point) 
{
	int ti,iSeleted;
	if(point.x==0 || point.y==0)
	{
		ShowMessage("移动鼠标以选择相同的球");
		ShowStatus(0);
		m_dMap.MouseOn(-1,-1,iSeleted);
		return;
	}
	point.x=point.x/m_iObjSize;
	point.y=point.y/m_iObjSize;
	if(point==m_dPointMouseAt)
		return;
	ti=m_dMap.MouseOn(point.y,point.x,iSeleted);
	ASSERT(ti!=MOUSEON_ERROR);
	if(ti==MOUSEON_SUCCESS)
	{
		PlaySoundEffect(SNDEFF_ACTIVE);
		m_bNeedPaint=true;
		ShowStatus(iSeleted);
		ShowMessage("点击左键以消除此块");
	}
	if(ti==MOUSEON_NOTSEL)
	{
		m_bNeedPaint=true;
		ShowStatus(0);
		ShowMessage("移动鼠标以选择相同的球");
	}
	m_dPointMouseAt.x=point.x;
	m_dPointMouseAt.y=point.y;
//	CWnd ::OnMouseMove(nFlags, point);
}

void CChildView::ShowMessage(CString nS)
{
	CString dS;
	CSameBallApp* pApp;
	pApp=(CSameBallApp*)AfxGetApp();
	((CMainFrame*)pApp->m_pMainWnd)->ShowStatus(0,nS);

}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int iResult;
	int iSeleted,iScoreCount,iRemainBalls;
	m_bNeedPaint=true;
	point.x=point.x/m_iObjSize;
	point.y=point.y/m_iObjSize;
	iResult=m_dMap.KillBall(point.y,point.x,iScoreCount,iRemainBalls);
	if(iResult==KILLBALL_ERROR || iResult==KILLBALL_NOT)
		return;
	PlaySoundEffect(SNDEFF_KILL);
	ShowStatus(-1,iScoreCount,iRemainBalls);
	if(iResult==KILLBALL_OK)
	{
		iResult=m_dMap.MouseOn(m_dPointMouseAt.y,m_dPointMouseAt.x,iSeleted);
		ASSERT(iResult!=MOUSEON_ERROR);
		if(iResult==MOUSEON_SUCCESS)
		{
			ShowStatus(iSeleted);
			ShowMessage("点击左键以消除此块");
		}
		if(iResult==MOUSEON_NOTSEL)
		{
			ShowStatus(0);
			ShowMessage("移动鼠标以选择相同的球");
		}
		return;
	}
	ShowMessage("游戏结束。");
	OnTimer(1);
	PlaySoundEffect(SNDEFF_GAMEOVER);
	GameOver(iScoreCount);
	OnFileNew();
	
	iResult=m_dMap.MouseOn(m_dPointMouseAt.y,m_dPointMouseAt.x,iSeleted);
	ASSERT(iResult!=MOUSEON_ERROR);
	if(iResult==MOUSEON_SUCCESS)
	{
		ShowStatus(iSeleted);
		ShowMessage("点击左键以消除此块");
	}
	if(iResult==MOUSEON_NOTSEL)
	{
		ShowStatus(0);
		ShowMessage("移动鼠标以选择相同的球");
	}
//	CWnd ::OnLButtonDown(nFlags, point);
}

void CChildView::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent!=1)
		return;
	CPoint dPoint;
	CRect ddtRect;
	CRect drcRect;
	CRect* prcRect;
	MapNode* pNode;
	HRESULT  ddrval;
	dPoint.x=dPoint.y=0;
	ClientToScreen(&dPoint);
	if(m_bNeedPaint)		// 绘制静态区
	{
		m_iActivePage=0;
		m_bNeedPaint=false;
		m_dMap.BeginGetStatic();
		pNode=m_dMap.GetNextStatic();
		while(pNode)
		{
			// source area
			if(pNode->iGroupNumber<0)
			{
				prcRect=&m_dBlack;
			}
			else
				switch(pNode->pBall->iClr)
				{
				case 0:
					prcRect=&m_dRed;
					break;
				case 1:
					prcRect=&m_dGreen;
					break;
				case 2:
					prcRect=&m_dBlue;					
				}
			// destination area
			ddtRect.CopyRect(&pNode->dRect);
			ddtRect.OffsetRect(dPoint);
			// paint 
			while( 1 )
			{
				ddrval = m_lpDDSPrimary->Blt(&ddtRect, m_lpDDSSource, prcRect, 0, NULL );	
				if( ddrval == DD_OK )
						break;
				if( ddrval == DDERR_SURFACELOST )
					if(!m_lpDDSPrimary->Restore() == DD_OK &&
							m_lpDDSSource->Restore()     == DD_OK &&
							ReLoadDDBitmap(m_uBmpID,m_lpDDSSource) == DD_OK)
						break;
				if( ddrval != DDERR_WASSTILLDRAWING )
					break;
			}
			//	get next node
			pNode=m_dMap.GetNextStatic();
		}
	//
	}
	if(m_bIsActive)			// 绘制动态区
	{
		m_dMap.BeginGetActive();
		pNode=m_dMap.GetNextActive();
		if(!pNode || !pNode->pBall)
			return;
		// source area
		if(++m_iActivePage>10)
		{
			if(m_iActivePage>20)
				m_iActivePage=11;
			drcRect.left=(m_iActivePage-11)*m_iObjSize;
			drcRect.right=drcRect.left+m_iObjSize;
			drcRect.top=(pNode->pBall->iClr+3)*m_iObjSize;
			drcRect.bottom=drcRect.top+m_iObjSize;
		}
		else
		{
			drcRect.left=(m_iActivePage)*m_iObjSize;
			drcRect.right=drcRect.left+m_iObjSize;
			drcRect.top=pNode->pBall->iClr*m_iObjSize;
			drcRect.bottom=drcRect.top+m_iObjSize;
		}
		while(pNode)
		{
		//  destination area
			ddtRect.CopyRect(&pNode->dRect);
			ddtRect.OffsetRect(dPoint);
			// paint 
			while( 1 )
			{
				ddrval = m_lpDDSPrimary->Blt(&ddtRect, m_lpDDSSource, drcRect, 0, NULL );	
				if( ddrval == DD_OK )
						break;
				if( ddrval == DDERR_SURFACELOST )
					if(!m_lpDDSPrimary->Restore() == DD_OK &&
							m_lpDDSSource->Restore()     == DD_OK &&
							ReLoadDDBitmap(m_uBmpID,m_lpDDSSource) == DD_OK)
						break;
				if( ddrval != DDERR_WASSTILLDRAWING )
					break;
			}
			//	get next node
			pNode=m_dMap.GetNextActive();	
		}
	}

}

void CChildView::OnEditUndo() 
{
	int iResult,iSeleted,iScoreCount,iRemain;
	if(m_dMap.OnUndo(iScoreCount,iRemain)==ONUNDO_ERROR)
		return;
	iResult=m_dMap.MouseOn(m_dPointMouseAt.y,m_dPointMouseAt.x,iSeleted);
	ASSERT(iResult!=MOUSEON_ERROR);
	if(iResult==MOUSEON_SUCCESS)
	{
		ShowStatus(iSeleted,iScoreCount,iRemain);
		ShowMessage("点击左键以消除此块");
	}
	if(iResult==MOUSEON_NOTSEL)
	{
		ShowStatus(0,iScoreCount,iRemain);
		ShowMessage("移动鼠标以选择相同的球");
	}
	m_bNeedPaint=true;

}

void CChildView::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_dMap.bCanUndo);
}

void CChildView::GameOver(int ndCurrentScore)
{
	int i,j,k;
	BOOL	bOnList=false;
	int	dId=NULL;
	CString sB;
	CString asName[5];
	CNameInDlg dlg;
	int   adScore[5];
	m_bIsActive=false;
	for(i=0,j=1;i<5;i++)
	{
		if(!((CSameBallApp*)AfxGetApp())->GetScoreListItem(j,sB,k))
			if((sB==_T("Error")) && i==0)
			{
				dlg.SetWindowText("排行榜数据出错！请将你的名字输入");
				dlg.DoModal();
				asName[0]=dlg.m_sName;
				adScore[0]=ndCurrentScore;
				for(k=1;k<5;k++)
				{
					asName[k]=_T("Noname");
					adScore[k]=0;
				}
				break ;
			}
				
		if(k>=ndCurrentScore)
		{
			asName[i]=sB;
			adScore[i]=k;
			j++;
		}
		else
		{
			// get input
			dlg.DoModal();
			asName[i]=dlg.m_sName;
			adScore[i]=ndCurrentScore;
			ndCurrentScore=0;
			bOnList=true;
			switch(i+1)
			{
			case 1:		dId=IDC_NAME1;	break;
			case 2:		dId=IDC_NAME2;	break;
			case 3:		dId=IDC_NAME3;	break;
			case 4:		dId=IDC_NAME4;	break;
			case 5:		dId=IDC_NAME5;	break;
			}
		}
		if(j>5 && i<4)
		{
			asName[4]=_T("Noname");
			adScore[4]=0;
			break;
		}
	}
	if(bOnList)
		for(i=0;i<5;i++)
		{
			if(!((CSameBallApp*)AfxGetApp())->SetScoreListItem(i+1,asName[i],adScore[i]))
				((CSameBallApp*)AfxGetApp())->SetScoreListItem(i+1,"NewPlayer",adScore[i]);
		}
	CScoreList sdlg;
	if(bOnList)
	{
		sdlg.m_dCurrentId=dId;
		if(dId==IDC_NAME1)
			sdlg.m_sMessage=_T("恭喜你荣登榜首！");
		else
			sdlg.m_sMessage=_T("恭喜你上榜！");
	}
	else
	{
		sdlg.m_dCurrentId=0;
		sdlg.m_sMessage=_T("很遗憾，你未能上榜！");
	}
	sdlg.m_sName1=asName[0];
	sdlg.m_sScore1.Format("%4d",adScore[0]);
	sdlg.m_sName2=asName[1];
	sdlg.m_sScore2.Format("%4d",adScore[1]);
	sdlg.m_sName3=asName[2];
	sdlg.m_sScore3.Format("%4d",adScore[2]);
	sdlg.m_sName4=asName[3];
	sdlg.m_sScore4.Format("%4d",adScore[3]);
	sdlg.m_sName5=asName[4];
	sdlg.m_sScore5.Format("%4d",adScore[4]);
	sdlg.DoModal();
	ShowStatus(-1,0,150);
	m_bIsActive=true;
}

void CChildView::OnViewScorelist() 
{
	
	int i,j,k;
//	BOOL	bOnList=false;
	CString sB;
	CString asName[5];
	CScoreList sdlg;
	int   adScore[5];
	m_bIsActive=false;
	for(i=0,j=1;i<5;i++,j++)
	{
		if(!((CSameBallApp*)AfxGetApp())->GetScoreListItem(j,sB,k))
			if((sB==_T("Error")) && i==0)
			{
				MessageBox("排行榜出错!");
				return ;
			}
				
			asName[i]=sB;
			adScore[i]=k;
	}
	sdlg.m_dCurrentId=0;
	sdlg.m_sName1=asName[0];
	sdlg.m_sScore1.Format("%4d",adScore[0]);
	sdlg.m_sName2=asName[1];
	sdlg.m_sScore2.Format("%4d",adScore[1]);
	sdlg.m_sName3=asName[2];
	sdlg.m_sScore3.Format("%4d",adScore[2]);
	sdlg.m_sName4=asName[3];
	sdlg.m_sScore4.Format("%4d",adScore[3]);
	sdlg.m_sName5=asName[4];
	sdlg.m_sScore5.Format("%4d",adScore[4]);
	sdlg.DoModal();
	m_bIsActive=true;
}

void CChildView::FreeDD()
{
	if(m_lpDDPalette)
	{
		m_lpDDPalette->Release();
		m_lpDDPalette=NULL;
	}
	if(m_lpDDSPrimary)
	{
		m_lpDDSPrimary->Release();
		m_lpDDSPrimary=NULL;
	}
	if(m_lpDDSSource)
	{
		m_lpDDSSource->Release();
		m_lpDDSSource=NULL;
	}
	if(m_pIDirectDraw)
	{
		m_pIDirectDraw->Release();
		m_pIDirectDraw=NULL;
	}

}

void CChildView::FreeDS()
{
	DWORD dStatus;
	for(int i=0;i<SNDEFF_COUNT;i++)
	{
		if(m_grlpSoundEffect[i])
		{
			dStatus=m_grlpSoundEffect[i]->GetStatus(&dStatus);
			if((dStatus & DSBSTATUS_LOOPING) ||(dStatus & DSBSTATUS_PLAYING))
				m_grlpSoundEffect[i]->Stop();
			m_grlpSoundEffect[i]->Release();
			m_grlpSoundEffect[i]=NULL;
		}
	}
}

BOOL CChildView::InitDS()
{
  // Create the DS object
  if (DirectSoundCreate(NULL, &m_lpDirectSound, NULL) != DS_OK) {
    MessageBox("Could not create DirectSound object!",
      "DirectSound Error");
    return FALSE;
  }

  // Set the cooperation level for the DS object
  if (m_lpDirectSound->SetCooperativeLevel(m_hWnd,//GetSafeHwnd(),
    DSSCL_NORMAL) != DS_OK) {
    MessageBox("Could not set cooperative level!",
      "DirectSound Error");
    return FALSE;
  }

  // Initialize the DS buffers
  if (!InitBuffers()) {
    MessageBox("Could not initialize DirectSound buffers!",
      "DirectSound Error");
    return FALSE;
  }
	return true;

}

BOOL CChildView::InitBuffers()
{
  // Initialize waves
  CWave waves[SNDEFF_COUNT];
  if(!waves[SNDEFF_MUSIC].Create(IDW_MUSIC))
	  return false;
  if(!waves[SNDEFF_KILL].Create(IDW_KILL))
	  return false;
  if(!waves[SNDEFF_ACTIVE].Create(IDW_ACTIVE))
	  return false;
  if(!waves[SNDEFF_GAMEOVER].Create(IDW_GAMEOVER))
	  return false;

  // Initialize DS buffers
  for (int i = 0; i < SNDEFF_COUNT; i++)
  {
    // Get the wave information
    DWORD         dwDataLen = waves[i].GetDataLen();
    WAVEFORMATEX  wfFormat;
    waves[i].GetFormat(wfFormat);

    // Setup the DS buffer description
    DSBUFFERDESC  dsbdDesc;
    ZeroMemory(&dsbdDesc, sizeof(DSBUFFERDESC));
    dsbdDesc.dwSize = sizeof(DSBUFFERDESC);
    dsbdDesc.dwFlags = DSBCAPS_CTRLDEFAULT | DSBCAPS_STATIC;
    dsbdDesc.dwBufferBytes = dwDataLen;
    dsbdDesc.lpwfxFormat = &wfFormat;

    // Create the DS buffer
    if (m_lpDirectSound->CreateSoundBuffer(&dsbdDesc,
      &m_grlpSoundEffect[i], NULL) != DS_OK)
      return FALSE;

    // Lock the DS buffer
    BYTE* pDSBuffData;
    if (m_grlpSoundEffect[i]->Lock(0, dwDataLen, (LPLPVOID)&pDSBuffData,
      &dwDataLen, NULL, 0, 0) != DS_OK)
      return FALSE;

    // Write wave data to the DS buffer
    dwDataLen = waves[i].GetData(pDSBuffData, dwDataLen);

    // Unlock the DS buffer
    if (m_grlpSoundEffect[i]->Unlock(pDSBuffData, dwDataLen, NULL, 0) !=
      DS_OK)
      return FALSE;

  }

  return TRUE;
}

BOOL CChildView::RestoreDSBuffers()
{
  // Restore the buffers
	for(int i=0;i<SNDEFF_COUNT;i++)
	{
		 if (m_grlpSoundEffect[i]->Restore() != DS_OK)
			return FALSE;
	}
  // Re-initialize the buffers
  return InitBuffers();
}

void CChildView::PlaySoundEffect(int nSound,DWORD nFlag)
{
	DWORD dStatus;
	if(!m_grlpSoundEffect[nSound])
		return;
	dStatus=m_grlpSoundEffect[nSound]->GetStatus(&dStatus);
	if((dStatus & DSBSTATUS_LOOPING) ||(dStatus & DSBSTATUS_PLAYING))
	{
			if(m_grlpSoundEffect[nSound]->Stop()!=DS_OK)
				OutMg("Can't stop playing!");
	}
	m_grlpSoundEffect[nSound]->Play(0,0,nFlag);

}

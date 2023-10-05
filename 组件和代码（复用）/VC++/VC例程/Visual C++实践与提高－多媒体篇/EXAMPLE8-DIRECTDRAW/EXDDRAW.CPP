// ExDDraw.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ExDDraw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExDDrawApp

BEGIN_MESSAGE_MAP(CExDDrawApp, CWinApp)
	//{{AFX_MSG_MAP(CExDDrawApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExDDrawApp construction

CExDDrawApp::CExDDrawApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}
/////////////////////////////////////////////////////////////////////////////
// The one and only CExDDrawApp object
CExDDrawApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CExDDrawApp initialization
BOOL CExDDrawApp::InitInstance()
{
//初始化成员函数并设置一个时钟
	m_EndApp = 0;
	m_total = 0;
	//int t=SetTimer(NULL,1,100,NULL);
	//if(t == 0)
	//	AfxMessageBox("Set Timer failed");
//初始化对象
	CWnd                *m_pWnd;
	HWND				hwnd;	
    DDSURFACEDESC       ddsd;
    DDSCAPS             ddscaps;
    HRESULT             ddrval;
	HDC                 hdc;
	//创建窗口
	m_pWnd = new CWnd;
	CRect rect(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	if (!m_pWnd->CreateEx(WS_EX_APPWINDOW,AfxRegisterWndClass(CS_DBLCLKS,
		::LoadCursor(NULL,IDC_ARROW),
                                     (HBRUSH)GetStockObject(WHITE_BRUSH),
                                     AfxGetApp()->LoadIcon(IDR_MAINFRAME)),
		"exdraw",WS_SYSMENU | WS_POPUP | WS_VISIBLE,rect,NULL,NULL))
		return NULL;
	if (!IsWindow(m_pWnd->m_hWnd))
		return NULL;
	hwnd = m_pWnd->m_hWnd;
	//创建对象DirectDraw
    ddrval = DirectDrawCreate( NULL, &lpDD, NULL );
    if( ddrval != DD_OK )
    {
		return initFail(hwnd);
    }
    //设置独占协作模式
    ddrval = lpDD->SetCooperativeLevel( hwnd, DDSCL_EXCLUSIVE | 
		              DDSCL_FULLSCREEN|DDSCL_ALLOWREBOOT);
    if( ddrval != DD_OK )
    {
		return initFail(hwnd);
    }
    // 设置显示模式640x480x8
    ddrval = lpDD->SetDisplayMode( 640, 480, 8);
    if( ddrval != DD_OK )
    {
		return initFail(hwnd);
    }
    // 创建带有一个后备缓冲区的主表面
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE |
			  DDSCAPS_FLIP |
			  DDSCAPS_COMPLEX;
    ddsd.dwBackBufferCount = 1;
    ddrval = lpDD->CreateSurface( &ddsd, &lpDDSPrimary, NULL );
    if( ddrval != DD_OK )
    {
		return initFail(hwnd);
    }
	//贴上后备缓冲区
    ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
    ddrval = lpDDSPrimary->GetAttachedSurface(&ddscaps, &lpDDSBack);
    if( ddrval != DD_OK )
    {
		return initFail(hwnd);
    }
    //创建并设置调色板
    lpDDPal = DDLoadPalette(lpDD, "IDB_BITMAP");
    if (lpDDPal)
        lpDDSPrimary->SetPalette(lpDDPal);
    //通过装载位图创建离屏表面
    lpDDSOne = DDLoadBitmap(lpDD, "IDB_BITMAP", 0, 0);
    if( lpDDSOne == NULL )
    {
		return initFail(hwnd);
    }
    // 为位图设置彩色键码
    DDSetColorKey(lpDDSOne, RGB(0,0,0));
	return TRUE;
}
int CExDDrawApp::Run() 
{
	MSG msg;
	int flag = 1;
	while(flag)
	{
		GetMessage(&msg,NULL,0,0);
		if(msg.message == WM_KEYDOWN)
		{
			switch(msg.wParam){
			case VK_ESCAPE:
			case VK_F12:
			case VK_DELETE :
				flag = 0;
				AfxMessageBox("yeah,kick the ok to exit");
				break;
			}
		}
		updateFrame();
	}	  
	ExitInstance();
	return CWinApp::Run();
}

int CExDDrawApp::ExitInstance() 
{
    if( lpDD != NULL )
    {
	if( lpDDSPrimary != NULL )
	{
	    lpDDSPrimary->Release();
	    lpDDSPrimary = NULL;
	}
	if( lpDDSOne != NULL )
	{
	    lpDDSOne->Release();
	    lpDDSOne = NULL;
	}
	if( lpDDPal != NULL )
	{
	    lpDDPal->Release();
	    lpDDPal = NULL;
	}
	lpDD->Release();
	lpDD = NULL;
    }
	return CWinApp::ExitInstance();
}
int CExDDrawApp::updateFrame() 
{
    static DWORD	lastTickCount[3] = {0,0,0};
    static int		currentFrame[3] = {0,0,0};
    DWORD		thisTickCount;
    RECT		rcRect;
    DWORD		delay[3] = {50, 78, 13};
    int			i;
    int			xpos[3] = {288, 190, 416};
    int			ypos[3] = {128, 300, 256};
    HRESULT		ddrval;
    //决定需要显示那一个表面
    thisTickCount = GetTickCount();
    for(i=0; i<3; i++)
    {
		if((thisTickCount - lastTickCount[i]) > delay[i])
		{
			lastTickCount[i] = thisTickCount;
			currentFrame[i]++;
			if(currentFrame[i] > 59)
			{
				currentFrame[i] = 0;
			}
		}
    }
    // Blit the stuff for the next frame
    rcRect.left = 0;
    rcRect.top = 0;
    rcRect.right = 640;
    rcRect.bottom = 480;
    while( 1 )
    {
        ddrval = lpDDSBack->BltFast( 0, 0, lpDDSOne,
            &rcRect, DDBLTFAST_NOCOLORKEY );
		if( ddrval == DD_OK )
		{
			break;
		}
		if( ddrval == DDERR_SURFACELOST )
		{
			ddrval = restoreAll();
			if( ddrval != DD_OK )
			{
				return 0;
			}
		}
		if( ddrval != DDERR_WASSTILLDRAWING )
		{
			return 0;
		}
	}
	if(ddrval != DD_OK)
	{
		return 0;
	}
	//把3个圆环复制到表面
    for( i=0; i<3; i++ )
    {
        rcRect.left   = currentFrame[i]%10*64;
        rcRect.top    = currentFrame[i]/10*64 + 480;
        rcRect.right  = currentFrame[i]%10*64 + 64;
        rcRect.bottom = currentFrame[i]/10*64 + 64 + 480;
		while( 1 )
		{
			ddrval = lpDDSBack->BltFast( xpos[i], ypos[i], lpDDSOne,
									 &rcRect, DDBLTFAST_SRCCOLORKEY );
			if( ddrval == DD_OK )
			{
				break;
			}
			if( ddrval == DDERR_SURFACELOST )
			{
				ddrval = restoreAll();
				if( ddrval != DD_OK )
				{
					return 0;
				}
			}
			if( ddrval != DDERR_WASSTILLDRAWING )
			{
				return 0;
			}
		}
	}
    //翻转表面
    while( 1 )
    {
		ddrval = lpDDSPrimary->Flip( NULL, 0 );
		if( ddrval == DD_OK )
		{
			break;
		}
		if( ddrval == DDERR_SURFACELOST )
		{
			ddrval = restoreAll();
			if( ddrval != DD_OK )
			{
				break;
			}
		}
		if( ddrval != DDERR_WASSTILLDRAWING )
		{
			break;
		}
    }
	return 1;
} 
IDirectDrawSurface * CExDDrawApp::DDLoadBitmap(IDirectDraw *pdd, LPCSTR szBitmap, int dx, int dy)
{
    HBITMAP             hbm;
    BITMAP              bm;
    DDSURFACEDESC       ddsd;
    IDirectDrawSurface *pdds;

    //
    //  try to load the bitmap as a resource, if that fails, try it as a file
    //
    hbm = (HBITMAP)LoadImage(GetModuleHandle(NULL), szBitmap, IMAGE_BITMAP, dx, dy, LR_CREATEDIBSECTION);

    if (hbm == NULL)
	hbm = (HBITMAP)LoadImage(NULL, szBitmap, IMAGE_BITMAP, dx, dy, LR_LOADFROMFILE|LR_CREATEDIBSECTION);

    if (hbm == NULL)
	return NULL;

    //得到位图的大小
    GetObject(hbm, sizeof(bm), &bm);      // get size of bitmap
    //为位图创建表面
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    ddsd.dwWidth = bm.bmWidth;
    ddsd.dwHeight = bm.bmHeight;
    if (pdd->CreateSurface(&ddsd, &pdds, NULL) != DD_OK)
	return NULL;
	//复制位图
    DDCopyBitmap(pdds, hbm, 0, 0, 0, 0);
    DeleteObject(hbm);
    return pdds;
}
/*
 *  DDReLoadBitmap
 *
 *  load a bitmap from a file or resource into a directdraw surface.
 *  normaly used to re-load a surface after a restore.
 *
 */
HRESULT CExDDrawApp::DDReLoadBitmap(IDirectDrawSurface *pdds, LPCSTR szBitmap)
{
    HBITMAP             hbm;
    HRESULT             hr;

    hbm = (HBITMAP)LoadImage(GetModuleHandle(NULL), szBitmap, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

    if (hbm == NULL)
        hbm = (HBITMAP)LoadImage(NULL, szBitmap, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);

    if (hbm == NULL)
    {
        OutputDebugString("句柄为空\n");
        return E_FAIL;
    }
    hr = DDCopyBitmap(pdds, hbm, 0, 0, 0, 0);
    if (hr != DD_OK)
    {
        OutputDebugString("函数失败\n");
    }


    DeleteObject(hbm);
    return hr;
}
//复制位图
HRESULT CExDDrawApp::DDCopyBitmap(IDirectDrawSurface *pdds, HBITMAP hbm, int x, int y, int dx, int dy)
{
    HDC                 hdcImage;
    HDC                 hdc;
    BITMAP              bm;
    DDSURFACEDESC       ddsd;
    HRESULT             hr;

    if (hbm == NULL || pdds == NULL)
        return E_FAIL;

    pdds->Restore();

    //将位图选入设备环境中
    hdcImage = CreateCompatibleDC(NULL);
    if (!hdcImage)
        OutputDebugString("DC创建失败\n");
    SelectObject(hdcImage, hbm);

    //获得位图尺寸
    GetObject(hbm, sizeof(bm), &bm);    // get size of bitmap
    dx = dx == 0 ? bm.bmWidth  : dx;    // use the passed size, unless zero
    dy = dy == 0 ? bm.bmHeight : dy;

    //获得表面尺寸
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
    pdds->GetSurfaceDesc(&ddsd);

    if ((hr = pdds->GetDC(&hdc)) == DD_OK)
    {
        StretchBlt(hdc, 0, 0, ddsd.dwWidth, ddsd.dwHeight, hdcImage, x, y, dx, dy, SRCCOPY);
        pdds->ReleaseDC(hdc);
    }

    DeleteDC(hdcImage);

    return hr;
}

//
//  DDLoadPalette
//
//  Create a DirectDraw palette object from a bitmap resoure
//
//  if the resource does not exist or NULL is passed create a
//  default 332 palette.
//
IDirectDrawPalette * CExDDrawApp::DDLoadPalette(IDirectDraw *pdd, LPCSTR szBitmap)
{
    IDirectDrawPalette* ddpal;
    int                 i;
    int                 n;
    int                 fh;
    HRSRC               h;
    LPBITMAPINFOHEADER  lpbi;
    PALETTEENTRY        ape[256];
    RGBQUAD *           prgb;

    for (i=0; i<256; i++)
    {
        ape[i].peRed   = (BYTE)(((i >> 5) & 0x07) * 255 / 7);
        ape[i].peGreen = (BYTE)(((i >> 2) & 0x07) * 255 / 7);
        ape[i].peBlue  = (BYTE)(((i >> 0) & 0x03) * 255 / 3);
        ape[i].peFlags = (BYTE)0;
    }

    if (szBitmap && (h = FindResource(NULL, szBitmap, RT_BITMAP)))
    {
        lpbi = (LPBITMAPINFOHEADER)LockResource(LoadResource(NULL, h));
        if (!lpbi)
            OutputDebugString("资源读取失败\n");
        prgb = (RGBQUAD*)((BYTE*)lpbi + lpbi->biSize);

        if (lpbi == NULL || lpbi->biSize < sizeof(BITMAPINFOHEADER))
            n = 0;
        else if (lpbi->biBitCount > 8)
            n = 0;
        else if (lpbi->biClrUsed == 0)
            n = 1 << lpbi->biBitCount;
        else
            n = lpbi->biClrUsed;

        for(i=0; i<n; i++ )
        {
            ape[i].peRed   = prgb[i].rgbRed;
            ape[i].peGreen = prgb[i].rgbGreen;
            ape[i].peBlue  = prgb[i].rgbBlue;
            ape[i].peFlags = 0;
        }
    }
    else if (szBitmap && (fh = _lopen(szBitmap, OF_READ)) != -1)
    {
        BITMAPFILEHEADER bf;
        BITMAPINFOHEADER bi;

        _lread(fh, &bf, sizeof(bf));
        _lread(fh, &bi, sizeof(bi));
        _lread(fh, ape, sizeof(ape));
        _lclose(fh);

        if (bi.biSize != sizeof(BITMAPINFOHEADER))
            n = 0;
        else if (bi.biBitCount > 8)
            n = 0;
        else if (bi.biClrUsed == 0)
            n = 1 << bi.biBitCount;
        else
            n = bi.biClrUsed;

        for(i=0; i<n; i++ )
        {
            BYTE r = ape[i].peRed;
            ape[i].peRed  = ape[i].peBlue;
            ape[i].peBlue = r;
        }
    }

    pdd->CreatePalette(DDPCAPS_8BIT, ape, &ddpal, NULL);

    return ddpal;
}
/*
 * convert a RGB color to a pysical color.
 */
DWORD CExDDrawApp::DDColorMatch(IDirectDrawSurface *pdds, COLORREF rgb)
{
    COLORREF rgbT;
    HDC hdc;
    DWORD dw = CLR_INVALID;
    DDSURFACEDESC ddsd;
    HRESULT hres;


    if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK)
    {
        rgbT = GetPixel(hdc, 0, 0);             // save current pixel value
        SetPixel(hdc, 0, 0, rgb);               // set our value
        pdds->ReleaseDC(hdc);
    }

    ddsd.dwSize = sizeof(ddsd);
    while ((hres = pdds->Lock(NULL, &ddsd, 0, NULL)) == DDERR_WASSTILLDRAWING)
        ;

    if (hres == DD_OK)
    {
        dw  = *(DWORD *)ddsd.lpSurface;                     
        dw &= (1 << ddsd.ddpfPixelFormat.dwRGBBitCount)-1;  
        pdds->Unlock(NULL);
    }

 
    if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK)
    {
        SetPixel(hdc, 0, 0, rgbT);
        pdds->ReleaseDC(hdc);
    }

    return dw;
}
//设置颜色键码
HRESULT CExDDrawApp::DDSetColorKey(IDirectDrawSurface *pdds, COLORREF rgb)
{
    DDCOLORKEY          ddck;

    ddck.dwColorSpaceLowValue  = DDColorMatch(pdds, rgb);
    ddck.dwColorSpaceHighValue = ddck.dwColorSpaceLowValue;
    return pdds->SetColorKey(DDCKEY_SRCBLT, &ddck);
}
BOOL CExDDrawApp::initFail( HWND hwnd )
{
    ExitInstance();
    AfxMessageBox("DirectDraw 初始化失败");
    DestroyWindow( hwnd );
    return FALSE;
}
HRESULT CExDDrawApp::restoreAll( )
{
    HRESULT	ddrval;

    ddrval = lpDDSPrimary->Restore();
    if( ddrval == DD_OK )
    {
	ddrval = lpDDSOne->Restore();
	if( ddrval == DD_OK )
	{
            DDReLoadBitmap(lpDDSOne, "IDB_BITMAP");
	}
    }
    return ddrval;
}
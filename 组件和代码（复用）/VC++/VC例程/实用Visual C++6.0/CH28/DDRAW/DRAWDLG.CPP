// DrawDlg.cpp : implementation file
//

#include "stdafx.h"
#include "initguid.h"
#include "Draw.h"
#include "DrawDlg.h"
#include "math.h"
//#include "initguid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawDlg dialog

CDrawDlg::CDrawDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDrawDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDrawDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pIDraw=NULL;
	m_pIMainSurface=NULL;

	CoInitialize(NULL);
}

CDrawDlg::~CDrawDlg()
{
	if (m_pIMainSurface)
	{
		m_pIDraw->SetCooperativeLevel(m_hWnd,DDSCL_NORMAL);
		m_pIDraw->RestoreDisplayMode();
		m_pIMainSurface->Release();
	}
	if (m_pIDraw) m_pIDraw->Release();
	CoUninitialize();
}

BOOL CDrawDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//**Initialize the OLE?COM library
	if (FAILED(CoInitialize(NULL))) return false;

	//Create a direct draw object and interface
	HRESULT hr=CoCreateInstance(CLSID_DirectDraw,NULL,
		CLSCTX_ALL,IID_IDirectDraw2,(void **)&m_pIDraw);

	if (!FAILED(hr))
	{
		hr=m_pIDraw->Initialize((struct _GUID*)NULL);
		if (hr!=DD_OK) return FALSE;
	}
	
	//**Set exclusive full screen mode 
	m_pIDraw->SetCooperativeLevel(m_hWnd,
		DDSCL_EXCLUSIVE|DDSCL_FULLSCREEN|DDSCL_ALLOWREBOOT);

	//**Set up a surface description structure
	DDSURFACEDESC DrawSurfaceDesc;
	memset(&DrawSurfaceDesc,0,sizeof(DrawSurfaceDesc));
	DrawSurfaceDesc.dwSize=sizeof(DrawSurfaceDesc);
	DrawSurfaceDesc.dwFlags=DDSD_CAPS
			| DDSD_BACKBUFFERCOUNT;
	DrawSurfaceDesc.ddsCaps.dwCaps=DDSCAPS_COMPLEX
		|DDSCAPS_FLIP|DDSCAPS_PRIMARYSURFACE;
	DrawSurfaceDesc.dwBackBufferCount=1;
	//**Create the primary surface
	hr=m_pIDraw->CreateSurface(&DrawSurfaceDesc,
		(IDirectDrawSurface**)&m_pIMainSurface,NULL);
	if (FAILED(hr)) return false;

	//**Find the back buffer
	DrawSurfaceDesc.ddsCaps.dwCaps=DDSCAPS_BACKBUFFER;
	hr=m_pIMainSurface->GetAttachedSurface(
		&DrawSurfaceDesc.ddsCaps,&m_pIFlipSurface);


	SetTimer(1,50,0);//**Start the 50ms Timer

	return true;
}

void CDrawDlg::OnTimer(UINT nIDEvent) 
{
	CDialog::OnTimer(nIDEvent);

	static RECT rc={0,0,0,0};
	static double dPetals=2.0;

	//**Clear the surface quickly with blit
	if (rc.right>0)
	{
		DDBLTFX dbltfx;
		dbltfx.dwSize=sizeof(DDBLTFX);
		dbltfx.dwFillColor=RGB(0,0,0);
		HRESULT hr=m_pIFlipSurface->Blt(&rc,NULL,
			&rc,DDBLT_COLORFILL,&dbltfx);
	}
	HDC hdc=NULL;

	//**Get a device context for the surface
	if (m_pIFlipSurface->GetDC(&hdc)==DD_OK)
	{
		if (hdc)
		{
			CDC dc;
			dc.Attach(hdc);

			rc.right=dc.GetDeviceCaps(HORZRES);
			rc.bottom=dc.GetDeviceCaps(VERTRES);
	
			double mx=(double) (rc.right>>1);
			double my=(double) (rc.bottom>>1);

			CPen psCol(PS_SOLID,1,RGB(0,255,0));
			CPen *ppsOld=dc.SelectObject(&psCol);
	
			double sx=mx/2;
			double sy=my/2;
			double sAngle=0.0;
	
			//**Draw the graphical animation
			for (int i=0;i<(int)dPetals;i++)
			{
				double s1a=sin(sAngle);
				double c1a=cos(sAngle);
				double s2a=sin(sAngle*dPetals);
				double c2a=cos(sAngle*dPetals);
				int x=(int)(mx+sx*c1a+sx*c2a);
				int y=(int)(my+sy*s1a-sy*s2a);
				if (i==0) dc.MoveTo(x,y);
				else	dc.LineTo(x,y);
				sAngle+=0.01745;
			}

			dPetals+=0.1;
			dc.SelectObject(ppsOld);
			dc.Detach();
		}
		m_pIFlipSurface->ReleaseDC(hdc);
	}

	//**Show the newly drawn surface
	m_pIMainSurface->Flip(NULL,DDFLIP_WAIT);
}

void CDrawDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDrawDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDrawDlg, CDialog)
	//{{AFX_MSG_MAP(CDrawDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawDlg message handlers



void CDrawDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDrawDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDrawDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



// ImageProperty.cpp : implementation file
//

#include "stdafx.h"
#include "ImageProperty.h"
#include "resource.h"
#include "mainfrm.h"
#include "dhcgboarddemoView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageProperty_Image property page

IMPLEMENT_DYNCREATE(CImageProperty_Image, CPropertyPage)

CImageProperty_Image::CImageProperty_Image() : CPropertyPage(CImageProperty_Image::IDD)
{
	//{{AFX_DATA_INIT(CImageProperty_Image)
	//}}AFX_DATA_INIT
	//	m_bIsLive=false;
}

CImageProperty_Image::~CImageProperty_Image()
{
}

void CImageProperty_Image::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageProperty_Image)
	DDX_Control(pDX, IDC_SATURATION_SB, m_HSBSaturation);
	DDX_Control(pDX, IDC_BRIGHTNESS_SB, m_HSBBrightness);
	DDX_Control(pDX, IDC_CONTRAST_SB, m_HSBContrast);
	DDX_Control(pDX, IDC_HUE_SB, m_HSBHue);
	DDX_Control(pDX, IDC_BANDPASS_SB, m_HSBBandPass);
	DDX_Control(pDX, IDC_CLAMPLEVEL_SB, m_HSBClampLevel);
	DDX_Text(pDX, IDC_BriNum, m_BriValue);
	DDX_Text(pDX, IDC_ConNum, m_ConValue);
	DDX_Text(pDX, IDC_HueNum, m_HueValue);
	DDX_Text(pDX, IDC_SatNum, m_SatValue);
	DDX_Text(pDX, IDC_CLAMPLEVELNum, m_ClampValue);
	DDX_Text(pDX, IDC_BANDPASSNum, m_BandValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImageProperty_Image, CPropertyPage)
	//{{AFX_MSG_MAP(CImageProperty_Image)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_BUTTON_LIVE, OnButtonLive)
	ON_BN_CLICKED(IDC_BUTTON_FREEZE, OnButtonFreeze)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageProperty_Image message handlers

BOOL CImageProperty_Image::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_HSBBrightness.SetScrollRange(0,255);
	m_HSBContrast.SetScrollRange(0,255);
	m_HSBHue.SetScrollRange(0,255);
	m_HSBSaturation.SetScrollRange(0,255);

	
	m_HSBBrightness.SetScrollPos(nADBri);
	m_HSBContrast.SetScrollPos(nADCon);
	m_HSBHue.SetScrollPos(nADHue);
	m_HSBSaturation.SetScrollPos(nADSat);
	m_HSBBandPass.SetScrollPos(nADBand);
	m_HSBClampLevel.SetScrollPos(nADClamp);

	char sVal[16];
	itoa( m_HSBBrightness.GetScrollPos(), sVal, 10);
	m_BriValue = _T(sVal);
	itoa( m_HSBContrast.GetScrollPos(), sVal, 10);
	m_ConValue = _T(sVal);
	itoa( m_HSBHue.GetScrollPos(), sVal, 10);
	m_HueValue = _T(sVal);
	itoa( m_HSBSaturation.GetScrollPos(), sVal, 10);
	m_SatValue = _T(sVal);

//
	m_BriValue.Format("%d",nADBri);
	m_ConValue.Format("%d",nADCon);
	m_HueValue.Format("%d",nADHue);
	m_SatValue.Format("%d",nADSat);
	m_BandValue.Format("%d",nADBand);
	m_ClampValue.Format("%d",nADClamp);
	//
	if(CGoption==0)//cg200
	{
		GetDlgItem(IDC_CLAMPLEVEL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CLAMPLEVEL_SB)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CLAMPLEVELNum)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BANDPASS)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BANDPASS_SB)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BANDPASSNum)->ShowWindow(SW_SHOW);
		m_HSBBandPass.SetScrollRange(0,127);
		m_HSBClampLevel.SetScrollRange(0,255);

		itoa( m_HSBBandPass.GetScrollPos(), sVal, 10);
		m_BandValue = _T(sVal);
		itoa( m_HSBClampLevel.GetScrollPos(), sVal, 10);
		m_ClampValue = _T(sVal);

		m_BandValue.Format("%d",nADBand);
		m_ClampValue.Format("%d",nADClamp);
	}
	UpdateData(FALSE);
	//	m_bIsLive=false;
	//	CG210Capture(hcg,FALSE);
	GetDlgItem(IDC_BUTTON_LIVE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_FREEZE)->EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CImageProperty_Image::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default

	int nCurPos;
	switch( nSBCode )
	{
		case SB_THUMBPOSITION:
			pScrollBar->SetScrollPos( nPos );
			break;
		case SB_LINERIGHT:
			nCurPos = pScrollBar->GetScrollPos();
			nCurPos++;
			if( nCurPos > 255 )
				nCurPos = 255;
			pScrollBar->SetScrollPos( nCurPos );
			break;
		case SB_LINELEFT:
			nCurPos = pScrollBar->GetScrollPos();
			nCurPos--;
			if( nCurPos < 0 )
				nCurPos = 0;
			pScrollBar->SetScrollPos( nCurPos );
			break;
		case SB_PAGERIGHT:
			nCurPos = pScrollBar->GetScrollPos();
			nCurPos += 10;
			if( nCurPos > 255 )
				nCurPos = 255;
			pScrollBar->SetScrollPos( nCurPos );
			break;
		case SB_PAGELEFT:
			nCurPos = pScrollBar->GetScrollPos();
			nCurPos -= 10;
			if( nCurPos < 0 )
				nCurPos = 0;
			pScrollBar->SetScrollPos( nCurPos );
			break;
		case SB_THUMBTRACK:
			pScrollBar->SetScrollPos( nPos );
			break;
	}

	nCurPos = pScrollBar->GetScrollPos();
	char sPos[16];
	itoa( nCurPos, sPos, 10 );
	if( pScrollBar == &m_HSBBrightness )
	{
		m_BriValue = _T(sPos);
		nADBri = nCurPos ;
		if(CGoption==0) CG200SetADParam(hcg, AD_BRIGHTNESS, nCurPos);
		else CG210SetADParam(hcg, AD_BRIGHTNESS, nCurPos);
	}
	else if( pScrollBar == &m_HSBContrast )
	{
		m_ConValue = _T(sPos);
		nADCon = nCurPos ;
		if(CGoption==0) CG200SetADParam(hcg, AD_CONTRAST, nCurPos);
		else CG210SetADParam(hcg, AD_CONTRAST, nCurPos);
	}
	else if( pScrollBar == &m_HSBHue )
	{
		m_HueValue = _T(sPos);
		nADHue = nCurPos ;
		if(CGoption==0) CG200SetADParam(hcg, AD_HUE, nCurPos);
		else CG210SetADParam(hcg, AD_HUE, nCurPos);
	}
	else if( pScrollBar == &m_HSBSaturation )
	{
		m_SatValue = _T(sPos);
		nADSat = nCurPos ;
		if(CGoption==0) CG200SetADParam(hcg, AD_SATURATION, nCurPos);
		else CG210SetADParam(hcg, AD_SATURATION, nCurPos);
	}
	else if( pScrollBar == &m_HSBBandPass )
	{
		m_BandValue = _T(sPos);
		nADBand = nCurPos ;
		if(CGoption==0) CG200SetADParam(hcg, AD_BANDPASS, nCurPos);
		//	else CG210SetADParam(hcg, AD_SATURATION, nCurPos);
	}
	else if( pScrollBar == &m_HSBClampLevel )
	{
		m_ClampValue = _T(sPos);
		nADClamp = nCurPos ;
		if(CGoption==0) CG200SetADParam(hcg, AD_CLAMPLEVEL, nCurPos);
		//	else CG210SetADParam(hcg, AD_SATURATION, nCurPos);
	}	
	UpdateData(FALSE);
	
	CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CImageProperty_Image::OnDefault() 
{
	// TODO: Add your control notification handler code here


	if(CGoption==0)
	{
		m_HSBBrightness.SetScrollPos(139);
		m_HSBContrast.SetScrollPos(80);
		m_HSBHue.SetScrollPos(1);
		m_HSBSaturation.SetScrollPos(64);
		m_HSBBandPass.SetScrollPos(0);
		m_HSBClampLevel.SetScrollPos(64);

		char sVal[16];
		itoa( m_HSBBrightness.GetScrollPos(), sVal, 10);
		m_BriValue = _T(sVal);
		itoa( m_HSBContrast.GetScrollPos(), sVal, 10);
		m_ConValue = _T(sVal);
		itoa( m_HSBHue.GetScrollPos(), sVal, 10);
		m_HueValue = _T(sVal);
		itoa( m_HSBSaturation.GetScrollPos(), sVal, 10);
		m_SatValue = _T(sVal);
		itoa( m_HSBBandPass.GetScrollPos(), sVal, 10);
		m_BandValue = _T(sVal);
		itoa( m_HSBClampLevel.GetScrollPos(), sVal, 10);
		m_ClampValue = _T(sVal);
		nADBri = 139 ;
		nADCon = 80 ;
		nADHue = 1 ;
		nADSat = 64 ;
		nADClamp=64;
		nADBand=0;
		CG200SetADParam(hcg, AD_BRIGHTNESS, 139);
		CG200SetADParam(hcg, AD_CONTRAST, 80);
		CG200SetADParam(hcg, AD_HUE, 1);
		CG200SetADParam(hcg, AD_SATURATION, 64);
		CG200SetADParam(hcg, AD_BANDPASS, 0);
		CG200SetADParam(hcg, AD_CLAMPLEVEL, 64);
	}
	else 
	{
		m_HSBBrightness.SetScrollPos(128);
		m_HSBContrast.SetScrollPos(128);
		m_HSBHue.SetScrollPos(128);
		m_HSBSaturation.SetScrollPos(128);
		
		char sVal[16];
		itoa( m_HSBBrightness.GetScrollPos(), sVal, 10);
		m_BriValue = _T(sVal);
		itoa( m_HSBContrast.GetScrollPos(), sVal, 10);
		m_ConValue = _T(sVal);
		itoa( m_HSBHue.GetScrollPos(), sVal, 10);
		m_HueValue = _T(sVal);
		itoa( m_HSBSaturation.GetScrollPos(), sVal, 10);
		m_SatValue = _T(sVal);
		
		nADBri = 128 ;
		nADCon = 128 ;
		nADHue = 128 ;
		nADSat = 128 ;
		CG210SetADParam(hcg, AD_BRIGHTNESS, 128);
		CG210SetADParam(hcg, AD_CONTRAST, 128);
		CG210SetADParam(hcg, AD_HUE, 128);
		CG210SetADParam(hcg, AD_SATURATION, 128);
	}
	UpdateData(FALSE);
	
}

void CImageProperty_Image::OnButtonLive() 
{
	// TODO: Add your control notification handler code here
//	CG210SetDispWindow(hcg, m_rcDisp.left, m_rcDisp.top, m_rcDisp.Width(), m_rcDisp.Height());
	CMainFrame* pMainfrm=(CMainFrame*)AfxGetMainWnd();
	CDHCGBoardDemoView* pView=pMainfrm->GetView();//GetActiveView();
	if(pView!=NULL)
	{
		if(!pView->m_bDDraw)
		{
			if(AfxMessageBox("图象卡需要处于Dirctx下，初始化吗？",MB_OKCANCEL,NULL)==IDOK)
			{
				pView->SendMessage(WM_COMMAND,ID_CGCARD_MODE_DIRECTX);
			}
			else
				return;
		}
		pView->SendMessage(WM_COMMAND,ID_CGBOARDPLAY);
		//	m_bIsLive=true;
		GetDlgItem(IDC_BUTTON_LIVE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_FREEZE)->EnableWindow(TRUE);
		
	}
}

void CImageProperty_Image::OnButtonFreeze() 
{
	// TODO: Add your control notification handler code here
	
	CMainFrame* pMainfrm=(CMainFrame*)AfxGetMainWnd();
	CDHCGBoardDemoView* pView=pMainfrm->GetView();
	if(pView!=NULL)
	{
		pView->SendMessage(WM_COMMAND,ID_CGBOARDSTOP);
		GetDlgItem(IDC_BUTTON_LIVE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_FREEZE)->EnableWindow(FALSE);//
	}

}


///////////////////////
// End of Image



/////////////////////////////////////////////////////////////////////////////
// CImageProperty_Source property page

IMPLEMENT_DYNCREATE(CImageProperty_Source, CPropertyPage)

CImageProperty_Source::CImageProperty_Source() : CPropertyPage(CImageProperty_Source::IDD)
{
	//{{AFX_DATA_INIT(CImageProperty_Source)

	//}}AFX_DATA_INIT
}

CImageProperty_Source::~CImageProperty_Source()
{
}

void CImageProperty_Source::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageProperty_Source)
	DDX_Radio(pDX, IDC_RADIO_SOURCE1, m_VideoSource);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImageProperty_Source, CPropertyPage)
	//{{AFX_MSG_MAP(CImageProperty_Source)
	ON_BN_CLICKED(IDC_RADIO_SOURCE1, OnRadioSource1)
	ON_BN_CLICKED(IDC_RADIO_SOURCE2, OnRadioSource2)
	ON_BN_CLICKED(IDC_RADIO_SOURCE3, OnRadioSource3)
	ON_BN_CLICKED(IDC_RADIO_SOURCE4, OnRadioSource4)
	ON_BN_CLICKED(IDC_RADIO_SOURCE5, OnRadioSource5)
	ON_BN_CLICKED(IDC_RADIO_SOURCE6, OnRadioSource6)
	ON_BN_CLICKED(IDC_RADIO_YC1, OnRadioYc1)
	ON_BN_CLICKED(IDC_RADIO_YC2, OnRadioYc2)
	ON_BN_CLICKED(IDC_RADIO_YC3, OnRadioYc3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageProperty_Source message handlers

BOOL CImageProperty_Source::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	m_VideoSource = nADSource;

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CImageProperty_Source::OnRadioSource1() 
{
	// TODO: Add your control notification handler code here
	m_VideoSource=0;
	nADSource = 0 ;
	if(CGoption==0)	CG200SetADParam(hcg, AD_SOURCE, nADSource);
	else CG210SetADParam(hcg, AD_SOURCE, nADSource);
}

void CImageProperty_Source::OnRadioSource2() 
{
	// TODO: Add your control notification handler code here
	m_VideoSource=1;
	nADSource = 1 ;
	if(CGoption==0) CG200SetADParam(hcg, AD_SOURCE, nADSource);
	else CG210SetADParam(hcg, AD_SOURCE, nADSource);
	
}

void CImageProperty_Source::OnRadioSource3() 
{
	// TODO: Add your control notification handler code here
	m_VideoSource=2;
	nADSource = 2 ;
	if(CGoption==0) CG200SetADParam(hcg, AD_SOURCE, nADSource);
	else CG210SetADParam(hcg, AD_SOURCE, nADSource);
	
}

void CImageProperty_Source::OnRadioSource4() 
{
	// TODO: Add your control notification handler code here
	m_VideoSource=3;
	nADSource = 3 ;
	if(CGoption==0) CG200SetADParam(hcg, AD_SOURCE, nADSource);
	else CG210SetADParam(hcg, AD_SOURCE, nADSource);
	
}

void CImageProperty_Source::OnRadioSource5() 
{
	// TODO: Add your control notification handler code here
	m_VideoSource=4;
	nADSource = 4 ;
	if(CGoption==1)
		CG210SetADParam(hcg, AD_SOURCE, nADSource);
	
}

void CImageProperty_Source::OnRadioSource6() 
{
	// TODO: Add your control notification handler code here
	m_VideoSource=5;
	nADSource = 5 ;
	if(CGoption==1)
		CG210SetADParam(hcg, AD_SOURCE, nADSource);
}

void CImageProperty_Source::OnRadioYc1() 
{
	// TODO: Add your control notification handler code here
	m_VideoSource=6;
	nADSource = 6 ;
	if(CGoption==1) CG210SetADParam(hcg, AD_SOURCE, nADSource);
	
}

void CImageProperty_Source::OnRadioYc2() 
{
	// TODO: Add your control notification handler code here
	m_VideoSource=7;
	nADSource = 7 ;
	if(CGoption==1) CG210SetADParam(hcg, AD_SOURCE, nADSource);
	
}

void CImageProperty_Source::OnRadioYc3() 
{
	// TODO: Add your control notification handler code here
	m_VideoSource=8;
	nADSource = 8 ;
	if(CGoption==1) CG210SetADParam(hcg, AD_SOURCE, nADSource);
	
}


/////////////////////
//	End of SOURCE


/////////////////////////////////////////////////////////////////////////////
// CImageProperty_Color property page

IMPLEMENT_DYNCREATE(CImageProperty_Color, CPropertyPage)

CImageProperty_Color::CImageProperty_Color() : CPropertyPage(CImageProperty_Color::IDD)
{
	//{{AFX_DATA_INIT(CImageProperty_Color)

	//}}AFX_DATA_INIT
}

CImageProperty_Color::~CImageProperty_Color()
{
}

void CImageProperty_Color::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageProperty_Color)
	DDX_Radio(pDX, IDC_RADIO_YUV422, m_ColorSpace);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImageProperty_Color, CPropertyPage)
	//{{AFX_MSG_MAP(CImageProperty_Color)
	ON_BN_CLICKED(IDC_RADIO_RGB15, OnRadioRgb15)
	ON_BN_CLICKED(IDC_RADIO_RGB16, OnRadioRgb16)
	ON_BN_CLICKED(IDC_RADIO_RGB24, OnRadioRgb24)
	ON_BN_CLICKED(IDC_RADIO_RGB32, OnRadioRgb32)
	ON_BN_CLICKED(IDC_RADIO_RGB8, OnRadioRgb8)
	ON_BN_CLICKED(IDC_RADIO_YUV422, OnRadioYuv422)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageProperty_Color message handlers

BOOL CImageProperty_Color::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ColorSpace = nADCla;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CImageProperty_Color::OnRadioYuv422() 
{
	// TODO: Add your control notification handler code here
	m_ColorSpace=0;
	nADCla = m_ColorSpace;
	if(CGoption==0) CG200SetColorSpace(hcg, m_ColorSpace);
	else CG210SetColorSpace(hcg, m_ColorSpace);
}
void CImageProperty_Color::OnRadioRgb15() 
{
	// TODO: Add your control notification handler code here
	m_ColorSpace=3;
	nADCla = m_ColorSpace;	
	if(CGoption==0) CG200SetColorSpace(hcg, m_ColorSpace);
	else CG210SetColorSpace(hcg, m_ColorSpace);
}

void CImageProperty_Color::OnRadioRgb16() 
{
	// TODO: Add your control notification handler code here
	m_ColorSpace=2;
	nADCla = m_ColorSpace;	
	if(CGoption==0) CG200SetColorSpace(hcg, m_ColorSpace);
	else CG210SetColorSpace(hcg, m_ColorSpace);
}

void CImageProperty_Color::OnRadioRgb24() 
{
	// TODO: Add your control notification handler code here
	m_ColorSpace=1;
	nADCla = m_ColorSpace;	
	if(CGoption==0) CG200SetColorSpace(hcg, m_ColorSpace);
	else CG210SetColorSpace(hcg, m_ColorSpace);
}

void CImageProperty_Color::OnRadioRgb32() 
{
	// TODO: Add your control notification handler code here
	m_ColorSpace=4;
	nADCla = m_ColorSpace;	
	if(CGoption==0) CG200SetColorSpace(hcg, m_ColorSpace);
	else CG210SetColorSpace(hcg, m_ColorSpace);
}

void CImageProperty_Color::OnRadioRgb8() 
{
	// TODO: Add your control notification handler code here
	m_ColorSpace=5;
	nADCla = m_ColorSpace;	
	if(CGoption==0) CG200SetColorSpace(hcg, m_ColorSpace);
	else CG210SetColorSpace(hcg, m_ColorSpace);
}

///////////////////////
//	End of COLOR



/////////////////////////////////////////////////////////////////////////////
// CImageProperty_Field property page

IMPLEMENT_DYNCREATE(CImageProperty_Field, CPropertyPage)

CImageProperty_Field::CImageProperty_Field() : CPropertyPage(CImageProperty_Field::IDD)
{
	//{{AFX_DATA_INIT(CImageProperty_Field)
	m_display = 0;
	m_mode = 0;
	m_Field=0;
	//}}AFX_DATA_INIT

}

CImageProperty_Field::~CImageProperty_Field()
{
}

void CImageProperty_Field::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageProperty_Field)
	DDX_Radio(pDX, IDC_RADIO_FRAME, m_Field);
	DDX_Radio(pDX, IDC_DISPLAY_CLIP, m_display);
	DDX_Radio(pDX, IDC_MODE_PAL, m_mode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImageProperty_Field, CPropertyPage)
	//{{AFX_MSG_MAP(CImageProperty_Field)
	ON_BN_CLICKED(IDC_RADIO_FRAME, OnRadioFrame)
	ON_BN_CLICKED(IDC_RADIO_FIELD, OnRadioField)
	ON_BN_CLICKED(IDC_DISPLAY_CLIP, OnDisplayClip)
	ON_BN_CLICKED(IDC_DISPLAY_SCALE, OnDisplayScale)
	ON_BN_CLICKED(IDC_MODE_NTSC, OnModeNtsc)
	ON_BN_CLICKED(IDC_MODE_PAL, OnModePal)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageProperty_Field message handlers

BOOL CImageProperty_Field::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Field = nADFld;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CImageProperty_Field::OnRadioFrame() 
{
	// TODO: Add your control notification handler code here
	m_Field=0;
	UpdateData(TRUE);
	nADFld = m_Field ;
	if(CGoption==0) CG200SetDispMode(hcg, FRAME);
	else CG210SetDispMode(hcg, FRAME);
}

void CImageProperty_Field::OnRadioField() 
{
	// TODO: Add your control notification handler code here
	m_Field=1;
	UpdateData(TRUE);
	nADFld = m_Field ;
	if(CGoption==0) CG200SetDispMode(hcg, FIELD);
	else CG210SetDispMode(hcg, FIELD);
}
void CImageProperty_Field::OnDisplayClip() 
{
	// TODO: Add your control notification handler code here
	m_display=1;
	if(CGoption==0) CG200SetInpVideoWindow(hcg,m_rcInput.left, m_rcInput.top, m_rcInput.Width(), m_rcInput.Height());
	else CG210SetInpVideoWindow(hcg,m_rcInput.left, m_rcInput.top, m_rcInput.Width(), m_rcInput.Height());

}

void CImageProperty_Field::OnDisplayScale() 
{
	// TODO: Add your control notification handler code here
	m_display=0;
	if(CGoption==0) CG200SetInpVideoWindow(hcg,m_rcDisp.left, m_rcDisp.top, m_rcDisp.Width(), m_rcDisp.Height());
	else CG210SetInpVideoWindow(hcg,m_rcDisp.left, m_rcDisp.top, m_rcDisp.Width(), m_rcDisp.Height());
}

void CImageProperty_Field::OnModeNtsc() 
{
	// TODO: Add your control notification handler code here
	m_mode=1;
}

void CImageProperty_Field::OnModePal() 
{
	// TODO: Add your control notification handler code here
	m_mode=0;
}

/////////////////////////////////////////////////////////////////////////////
// CImageProperty_Win property page

IMPLEMENT_DYNCREATE(CImageProperty_Win, CPropertyPage)

CImageProperty_Win::CImageProperty_Win() : CPropertyPage(CImageProperty_Win::IDD)
{
	//{{AFX_DATA_INIT(CImageProperty_Win)
	//}}AFX_DATA_INIT
}

CImageProperty_Win::~CImageProperty_Win()
{
}

void CImageProperty_Win::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageProperty_Win)
	DDX_Control(pDX, IDC_SPIN_WIDTH, m_width);
	DDX_Control(pDX, IDC_SPIN_HEIGHT, m_height);
	DDX_Control(pDX, IDC_SPIN_STARTY, m_starty);
	DDX_Control(pDX, IDC_SPIN_STARTX, m_startx);
	DDX_Text(pDX, IDC_STARTX, m_nStartx);
	DDX_Text(pDX, IDC_STARTY, m_nStarty);
	DDX_Text(pDX, IDC_IMAGE_HEIGHT, m_nHeight);
	DDX_Text(pDX, IDC_IMAGE_WIDTH, m_nWidth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImageProperty_Win, CPropertyPage)
	//{{AFX_MSG_MAP(CImageProperty_Win)
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageProperty_Win message handlers

BOOL CImageProperty_Win::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	UDACCEL acc;
	acc.nInc=4;
	acc.nSec=2;
	m_startx.SetRange(0,256);
	m_startx.SetPos(m_nStartx);
	m_startx.SetAccel(1,&acc);
	acc.nInc=2;
	m_starty.SetRange(0,128);
	m_starty.SetPos(m_nStarty);
	m_starty.SetAccel(1,&acc);
	acc.nInc=4;
	m_width.SetRange(100,768);
	m_width.SetPos(m_nWidth);
	m_width.SetAccel(1,&acc);
	acc.nInc=2;
	m_height.SetRange(50,576);
	m_height.SetPos(m_nHeight);
	m_height.SetAccel(1,&acc);
	UpdateData(FALSE);
	SetTimer(1,10,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CImageProperty_Win::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	CString str;
	GetDlgItemText(IDC_STARTX,str);
	m_nStartx=atoi(str);
	GetDlgItemText(IDC_STARTY,str);
	m_nStarty=atoi(str);

	GetDlgItemText(IDC_IMAGE_WIDTH,str);
	m_nWidth=atoi(str);
	//	m_width
	if((m_nWidth+m_nStartx)>768) m_nWidth=768-m_nStartx;
	if(m_nWidth%4!=0) m_nWidth=m_nWidth/4*4;
	m_width.SetPos(m_nWidth);

	GetDlgItemText(IDC_IMAGE_HEIGHT,str);
	m_nHeight=atoi(str);
	if((m_nHeight+m_nStarty)>576) m_nHeight=576-m_nStarty;
	if(m_nHeight%2) --m_nHeight;
	m_height.SetPos(m_nHeight);

	UpdateData(FALSE);
	if(CGoption==0) CG200SetInpVideoWindow(hcg, m_nStartx, m_nStarty, m_nWidth, m_nHeight);	
	else CG210SetInpVideoWindow(hcg, m_nStartx, m_nStarty, m_nWidth, m_nHeight);	
	CPropertyPage::OnVScroll(nSBCode, nPos, pScrollBar);
}
//void CImageProPerty_Win::OnTiemr(UINT nIDEvent)
//{
//	CString str;
//	GetDlgItemText(IDC_STARTX,str);
//	m_nStartx=atoi(str);
//	GetDlgItemText(IDC_STARTY,str);
//	m_nStarty=atoi(str);
//	GetDlgItemText(IDC_IMAGE_WIDTH,str);
//	m_nWidth=atoi(str);
//	if(m_nWidth%4!=0) m_nWidth=m_nWidth/4*4;
//	//	GetDlgItemText(IDC_IMAGE_HEIGHT,str);
//	//	m_nHeight=atoi(str);
//	if(m_nHeight>576) m_nHeight=576;
//	//	m_height.SetPos(m_nHeight);
//	
//	UpdateData(FALSE);
//
//	if(CGoption==0) CG200SetInpVideoWindow(hcg, m_nStartx, m_nStarty, m_nWidth, m_nHeight);	
//	else CG210SetInpVideoWindow(hcg, m_nStartx, m_nStarty, m_nWidth, m_nHeight);	
//	CPropertyPage::OnVScroll(nSBCode, nPos, pScrollBar);
//}

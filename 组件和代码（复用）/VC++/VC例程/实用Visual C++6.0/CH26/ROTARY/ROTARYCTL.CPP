// RotaryCtl.cpp : Implementation of the CRotaryCtrl ActiveX Control class.

#include "stdafx.h"
#include "Rotary.h"
#include "RotaryCtl.h"
#include "RotaryPpg.h"
#include "math.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CRotaryCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CRotaryCtrl, COleControl)
	//{{AFX_MSG_MAP(CRotaryCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CRotaryCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CRotaryCtrl)
	DISP_PROPERTY_EX(CRotaryCtrl, "TickEnable", GetTickEnable, SetTickEnable, VT_BOOL)
	DISP_PROPERTY_EX(CRotaryCtrl, "NumTicks", GetNumTicks, SetNumTicks, VT_BOOL)
	DISP_STOCKPROP_FORECOLOR()
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CRotaryCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CRotaryCtrl, COleControl)
	//{{AFX_EVENT_MAP(CRotaryCtrl)
	EVENT_CUSTOM("Repositioned", FireRepositioned, VTS_R8)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CRotaryCtrl, 2)
	PROPPAGEID(CRotaryPropPage::guid)
	PROPPAGEID(CLSID_CColorPropPage)
END_PROPPAGEIDS(CRotaryCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CRotaryCtrl, "ROTARY.RotaryCtrl.1",
	0x721757a6, 0xee5c, 0x11d2, 0xbf, 0x13, 0x44, 0x45, 0x53, 0x54, 0, 0)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CRotaryCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DRotary =
		{ 0x721757a4, 0xee5c, 0x11d2, { 0xbf, 0x13, 0x44, 0x45, 0x53, 0x54, 0, 0 } };
const IID BASED_CODE IID_DRotaryEvents =
		{ 0x721757a5, 0xee5c, 0x11d2, { 0xbf, 0x13, 0x44, 0x45, 0x53, 0x54, 0, 0 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwRotaryOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CRotaryCtrl, IDS_ROTARY, _dwRotaryOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CRotaryCtrl::CRotaryCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CRotaryCtrl

BOOL CRotaryCtrl::CRotaryCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_ROTARY,
			IDB_ROTARY,
			afxRegApartmentThreading,
			_dwRotaryOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CRotaryCtrl::CRotaryCtrl - Constructor

CRotaryCtrl::CRotaryCtrl()
{
	InitializeIIDs(&IID_DRotary, &IID_DRotaryEvents);

	// TODO: Initialize your control's instance data here.
	m_bTicks = TRUE;
	m_sNumTicks = 20;
}


/////////////////////////////////////////////////////////////////////////////
// CRotaryCtrl::~CRotaryCtrl - Destructor

CRotaryCtrl::~CRotaryCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CRotaryCtrl::OnDraw - Drawing function

void CRotaryCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	
	  CBrush brForeGnd(TranslateColor(GetForeColor( )));
      CBrush brBackGnd(TranslateColor(AmbientBackColor( )));
      
      // ** Draw the control background 
      pdc->FillRect(rcBounds, &brBackGnd);
      
      CBrush* pOldBrush = pdc->SelectObject(&brForeGnd);
 
      // ** Calculate the relative position and midpoint
      CPoint ptRelative = m_ptClicked - rcBounds.TopLeft( );
      CPoint ptMid(rcBounds.Width( )/2, rcBounds.Height( )/2);
      
      // ** Find offset from the middle
      double dRelX = ptRelative.x - ptMid.x;
      double dRelY = ptRelative.y - ptMid.y;
      
      // ** Use trig to find the angle by T=O/A
      double dAngle = atan2(dRelY, dRelX);
      double dRadX = (double)ptMid.x * 0.9;
      double dRadY = (double)ptMid.y * 0.9;
      
      // ** Find a point on the radius of the knob
      int nXPos = ptMid.x + (int)(cos(dAngle) * dRadX);
      int nYPos = ptMid.y + (int)(sin(dAngle) * dRadY);
      
      // ** Set the notch point position 
      CPoint ptKnob = CPoint(nXPos, nYPos) + rcBounds.TopLeft( );
      
      // ** Set a rect and draw the notch circle
      CRect rcPoint(ptKnob - CSize(4,4), CSize(8,8));
      pdc->Ellipse(rcPoint);
      
      // ** Draw the main rotary circle
      pdc->Ellipse(ptMid.x - (int)dRadX, ptMid.y - (int)dRadY,
                  ptMid.x + (int)dRadX, ptMid.y + (int)dRadY);
      
      // ** Draw a line from the center to the notch
      pdc->MoveTo(ptMid);
      pdc->LineTo(ptKnob);
      
      pdc->SelectObject(pOldBrush);
	  m_dCurrentPosition = dAngle * 57.2978 + 180.0;
	  if (m_bTicks)
	  {
      // Iterate in radians from -2*PI to +2*PI
      const double dPi = 3.14185;
      double r = -2.0 * dPi;
      for (int i=0; i<m_sNumTicks; i++)
      {
           // Move to a position outside the main circle
           nXPos = ptMid.x + (int)(cos(r) * dRadX * 1.05);
           nYPos = ptMid.y + (int)(sin(r) * dRadY * 1.05);
           pdc->MoveTo(CPoint(nXPos, nYPos));
      
           //  Draw a line even further out for a tick mark
           nXPos = ptMid.x + (int)(cos(r) * dRadX * 1.15);
           nYPos = ptMid.y + (int)(sin(r) * dRadY * 1.15);
           pdc->LineTo(CPoint(nXPos, nYPos));
      
           // Increment the angle
           r += dPi / (m_sNumTicks /2.0);
	  }
	  }

}


/////////////////////////////////////////////////////////////////////////////
// CRotaryCtrl::DoPropExchange - Persistence support

void CRotaryCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.
    PX_Bool(pPX, _T("TicksEnable"), m_bTicks, TRUE);
    
    // ** Serialize the Number of Ticks Option 
    PX_Short(pPX, _T("NumTicks"), m_sNumTicks, 20);

}


/////////////////////////////////////////////////////////////////////////////
// CRotaryCtrl::OnResetState - Reset control to default state

void CRotaryCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CRotaryCtrl::AboutBox - Display an "About" box to the user

void CRotaryCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_ROTARY);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CRotaryCtrl message handlers

void CRotaryCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	COleControl::OnLButtonDown(nFlags, point);
	SetCapture();
	m_ptClicked = point;
	InvalidateControl();
}

void CRotaryCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	 if (nFlags & MK_LBUTTON)
     {
           // ** Store the moved position
           m_ptClicked = point;
           
           // ** Redraw the control
           InvalidateControl( );
      }

	COleControl::OnMouseMove(nFlags, point);
}

void CRotaryCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	ReleaseCapture();
	FireRepositioned( m_dCurrentPosition);
	COleControl::OnLButtonUp(nFlags, point);
}

BOOL CRotaryCtrl::GetTickEnable() 
{
	// TODO: Add your property handler here

	return m_bTicks;
}

void CRotaryCtrl::SetTickEnable(BOOL bNewValue) 
{
	// TODO: Add your property handler here
	m_bTicks = bNewValue;
    
	SetModifiedFlag();
}

BOOL CRotaryCtrl::GetNumTicks() 
{
	// TODO: Add your property handler here

	return m_sNumTicks;
}

void CRotaryCtrl::SetNumTicks(BOOL bNewValue) 
{
	// TODO: Add your property handler here

	m_sNumTicks = bNewValue;
	SetModifiedFlag();
}

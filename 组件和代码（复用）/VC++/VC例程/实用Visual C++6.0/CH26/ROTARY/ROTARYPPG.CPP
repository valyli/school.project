// RotaryPpg.cpp : Implementation of the CRotaryPropPage property page class.

#include "stdafx.h"
#include "Rotary.h"
#include "RotaryPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CRotaryPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CRotaryPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CRotaryPropPage)
	//ON_EN_CHANGE(IDC_NUM_TICKS, OnChangeEdit2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CRotaryPropPage, "ROTARY.RotaryPropPage.1",
	0x721757a7, 0xee5c, 0x11d2, 0xbf, 0x13, 0x44, 0x45, 0x53, 0x54, 0, 0)


/////////////////////////////////////////////////////////////////////////////
// CRotaryPropPage::CRotaryPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CRotaryPropPage

BOOL CRotaryPropPage::CRotaryPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_ROTARY_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CRotaryPropPage::CRotaryPropPage - Constructor

CRotaryPropPage::CRotaryPropPage() :
	COlePropertyPage(IDD, IDS_ROTARY_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CRotaryPropPage)
	m_bTicksEnabled = FALSE;
	m_sNumTicks = 0;
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CRotaryPropPage::DoDataExchange - Moves data between page and properties

void CRotaryPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CRotaryPropPage)
	DDX_Check(pDX, IDC_TICKS_ENABLED, m_bTicksEnabled);
	DDX_Text(pDX, IDC_NUM_TICKS, m_sNumTicks);
	DDV_MinMaxInt(pDX, m_sNumTicks, 1, 100);
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CRotaryPropPage message handlers

void CRotaryPropPage::OnChangeEdit2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the COlePropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

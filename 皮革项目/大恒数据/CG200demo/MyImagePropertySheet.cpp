// MyImagePropertySheet.cpp : implementation file
//

#include "stdafx.h"

#include "MyImagePropertySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyImagePropertySheet

IMPLEMENT_DYNAMIC(CMyImagePropertySheet, CPropertySheet)

CMyImagePropertySheet::CMyImagePropertySheet(CWnd* pParentWnd )
	:CPropertySheet("ÕºœÒ…Ë÷√", pParentWnd)
{
	// Add all of the property pages here.  Note that
	// the order that they appear in here will be
	// the order they appear in on screen.  By default,
	// the first page of the set is the active one.
	// One way to make a different property page the 
	// active one is to call SetActivePage().

	m_Page1=new CImageProperty_Image();
	m_Page2=new CImageProperty_Source();
	m_Page3=new CImageProperty_Color();
	m_Page4=new CImageProperty_Field();
	m_Page5=new CImageProperty_Win();
	AddPage(m_Page1);
	AddPage(m_Page2);
	AddPage(m_Page3);
	AddPage(m_Page4);
	AddPage(m_Page5);
	//
}


CMyImagePropertySheet::~CMyImagePropertySheet()
{
	if(m_Page1) delete m_Page1;
	if(m_Page2) delete m_Page2;
	if(m_Page3) delete m_Page3;
	if(m_Page4) delete m_Page4;
	if(m_Page5) delete m_Page5;
	m_Page5=NULL;
	m_Page1=NULL;
	m_Page2=NULL;
	m_Page3=NULL;
	m_Page4=NULL;
}


BEGIN_MESSAGE_MAP(CMyImagePropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CMyImagePropertySheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyImagePropertySheet message handlers

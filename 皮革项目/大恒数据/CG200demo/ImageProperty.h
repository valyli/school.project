#if !defined(AFX_IMAGEPROPERTY_H__09C2E842_A400_11D3_AFDB_5254AB109661__INCLUDED_)
#define AFX_IMAGEPROPERTY_H__09C2E842_A400_11D3_AFDB_5254AB109661__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageProperty.h : header file
//
#include "resource.h"
#include "cg210-32.h"
#include "cg200-32.h"
#include "VideoCGPara.h"
/////////////////////////////////////////////////////////////////////////////
// CImageProperty_Image dialog

class CImageProperty_Image : public CPropertyPage
{
	DECLARE_DYNCREATE(CImageProperty_Image)

public:
	int nADBri;	//亮度
	int nADCon;	//对比度
	int nADHue;	//色度
	int nADSat;	//饱和度
	DWORD hcg;
	int CGoption;
// Construction
public:
	int nADBand;
	int nADClamp;
	//	BOOL m_bIsLive;
	CRect m_rcDisp;
	CImageProperty_Image();
	~CImageProperty_Image();

// Dialog Data
	//{{AFX_DATA(CImageProperty_Image)
	enum { IDD = IDD_PROPPAGE1_IMAGESET };
	CScrollBar	m_HSBSaturation;
	CScrollBar	m_HSBBrightness;
	CScrollBar	m_HSBContrast;
	CScrollBar	m_HSBHue;
	CScrollBar	m_HSBBandPass;
	CScrollBar	m_HSBClampLevel;
	CString	m_BriValue;
	CString	m_ConValue;
	CString	m_HueValue;
	CString	m_SatValue;
	CString	m_BandValue;
	CString	m_ClampValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CImageProperty_Image)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CImageProperty_Image)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnDefault();
	afx_msg void OnButtonLive();
	afx_msg void OnButtonFreeze();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CImageProperty_Source dialog

class CImageProperty_Source : public CPropertyPage
{
	DECLARE_DYNCREATE(CImageProperty_Source)

public:
	int nADSource;
	DWORD hcg;
	int CGoption;
// Construction
public:
	CImageProperty_Source();
	~CImageProperty_Source();

// Dialog Data
	//{{AFX_DATA(CImageProperty_Source)
	enum { IDD = IDD_PROPPAGE2_SOURCE };
	int		m_VideoSource;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CImageProperty_Source)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CImageProperty_Source)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioSource1();
	afx_msg void OnRadioSource2();
	afx_msg void OnRadioSource3();
	afx_msg void OnRadioSource4();
	afx_msg void OnRadioSource5();
	afx_msg void OnRadioSource6();
	afx_msg void OnRadioYc1();
	afx_msg void OnRadioYc2();
	afx_msg void OnRadioYc3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
/////////////////////////////////////////////////////////////////////////////
// CImageProperty_Color dialog

class CImageProperty_Color : public CPropertyPage
{
	DECLARE_DYNCREATE(CImageProperty_Color)

public:
	int nADCla;
	DWORD hcg;
	int CGoption;
// Construction
public:
	CImageProperty_Color();
	~CImageProperty_Color();

// Dialog Data
	//{{AFX_DATA(CImageProperty_Color)
	enum { IDD = IDD_PROPPAGE3_COLOR };
	int		m_ColorSpace;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CImageProperty_Color)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CImageProperty_Color)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioRgb15();
	afx_msg void OnRadioRgb16();
	afx_msg void OnRadioRgb24();
	afx_msg void OnRadioRgb32();
	afx_msg void OnRadioRgb8();
	afx_msg void OnRadioYuv422();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
/////////////////////////////////////////////////////////////////////////////
// CImageProperty_Field dialog

class CImageProperty_Field : public CPropertyPage
{
	DECLARE_DYNCREATE(CImageProperty_Field)

public:
	DWORD hcg;
	int CGoption;
	CRect m_rcInput,m_rcDisp;
// Construction
public:
	CImageProperty_Field();
	~CImageProperty_Field();

// Dialog Data
	//{{AFX_DATA(CImageProperty_Field)
	enum { IDD = IDD_PROPPAGE4_FIELD };
	int		m_Field;
	int		m_display;
	int		m_mode;
	//}}AFX_DATA

	int nADFld;
// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CImageProperty_Field)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CImageProperty_Field)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioFrame();
	afx_msg void OnRadioField();
	afx_msg void OnDisplayClip();
	afx_msg void OnDisplayScale();
	afx_msg void OnModeNtsc();
	afx_msg void OnModePal();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CImageProperty_Win dialog

class CImageProperty_Win : public CPropertyPage
{
	DECLARE_DYNCREATE(CImageProperty_Win)

// Construction
public:
	CImageProperty_Win();
	~CImageProperty_Win();
	DWORD hcg;
	int CGoption;
// Dialog Data
	//{{AFX_DATA(CImageProperty_Win)
	enum { IDD = IDD_PROPPAGE5_WINDOWS };
	CSpinButtonCtrl	m_width;
	CSpinButtonCtrl	m_height;
	CSpinButtonCtrl	m_starty;
	CSpinButtonCtrl	m_startx;
	int		m_nStartx;
	int		m_nStarty;
	int		m_nHeight;
	int		m_nWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CImageProperty_Win)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CImageProperty_Win)
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEPROPERTY_H__09C2E842_A400_11D3_AFDB_5254AB109661__INCLUDED_)

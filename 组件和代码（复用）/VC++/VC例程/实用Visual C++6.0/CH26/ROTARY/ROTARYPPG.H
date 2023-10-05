#if !defined(AFX_ROTARYPPG_H__721757B6_EE5C_11D2_BF13_444553540000__INCLUDED_)
#define AFX_ROTARYPPG_H__721757B6_EE5C_11D2_BF13_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// RotaryPpg.h : Declaration of the CRotaryPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CRotaryPropPage : See RotaryPpg.cpp.cpp for implementation.

class CRotaryPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CRotaryPropPage)
	DECLARE_OLECREATE_EX(CRotaryPropPage)

// Constructor
public:
	CRotaryPropPage();

// Dialog Data
	//{{AFX_DATA(CRotaryPropPage)
	enum { IDD = IDD_PROPPAGE_ROTARY };
	BOOL	m_bTicksEnabled;
	short	m_sNumTicks;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CRotaryPropPage)
	afx_msg void OnChangeEdit2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROTARYPPG_H__721757B6_EE5C_11D2_BF13_444553540000__INCLUDED)

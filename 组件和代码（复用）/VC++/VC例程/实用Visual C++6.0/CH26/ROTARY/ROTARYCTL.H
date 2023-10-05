#if !defined(AFX_ROTARYCTL_H__721757B4_EE5C_11D2_BF13_444553540000__INCLUDED_)
#define AFX_ROTARYCTL_H__721757B4_EE5C_11D2_BF13_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// RotaryCtl.h : Declaration of the CRotaryCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CRotaryCtrl : See RotaryCtl.cpp for implementation.

class CRotaryCtrl : public COleControl
{
	DECLARE_DYNCREATE(CRotaryCtrl)

// Constructor
public:
	CRotaryCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRotaryCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CRotaryCtrl();

	DECLARE_OLECREATE_EX(CRotaryCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CRotaryCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CRotaryCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CRotaryCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CRotaryCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CRotaryCtrl)
	afx_msg BOOL GetTickEnable();
	afx_msg void SetTickEnable(BOOL bNewValue);
	afx_msg BOOL GetNumTicks();
	afx_msg void SetNumTicks(BOOL bNewValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CRotaryCtrl)
	void FireRepositioned(double dNewPosition)
		{FireEvent(eventidRepositioned,EVENT_PARAM(VTS_R8), dNewPosition);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	BOOL m_bTicks;
	short m_sNumTicks;
	double m_dCurrentPosition;
	double dCurrentPosition;
	CPoint m_ptClicked;
	enum {
	//{{AFX_DISP_ID(CRotaryCtrl)
	dispidTickEnable = 1L,
	dispidNumTicks = 2L,
	eventidRepositioned = 1L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROTARYCTL_H__721757B4_EE5C_11D2_BF13_444553540000__INCLUDED)

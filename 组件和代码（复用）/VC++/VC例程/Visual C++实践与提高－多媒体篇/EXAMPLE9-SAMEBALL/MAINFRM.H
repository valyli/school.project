// MainFrm.h : interface of the CMainFrame class
// 编码: Leezy
// 最后修改日期：5.1
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__94E17C69_1EE0_11D4_A0AA_0080AD76C3BA__INCLUDED_)
#define AFX_MAINFRM_H__94E17C69_1EE0_11D4_A0AA_0080AD76C3BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Ball.h"
#include "MapNode.h"
#include "SameBallMap.h"
#include "ChildView.h"

class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL m_bMinSize;
	BOOL m_bMaxSize;
	void ShowStatus(UINT nIndex,CString ndS);
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
//	CToolBar    m_wndToolBar;
	CChildView    m_wndView;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnActivateApp(BOOL bActive, HTASK hTask);
	afx_msg void OnHelp();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnRegender();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CRect SetWinSize(int ni);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__94E17C69_1EE0_11D4_A0AA_0080AD76C3BA__INCLUDED_)

// SameBall.h : main header file for the SAMEBALL application
// 编码: Leezy
// 最后修改日期：5.1
//

#if !defined(AFX_SAMEBALL_H__94E17C65_1EE0_11D4_A0AA_0080AD76C3BA__INCLUDED_)
#define AFX_SAMEBALL_H__94E17C65_1EE0_11D4_A0AA_0080AD76C3BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSameBallApp:
// See SameBall.cpp for the implementation of this class
//

class CSameBallApp : public CWinApp
{
public:
	CSameBallApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSameBallApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	BOOL m_bNeedSave;//
	CString m_sAppDir;//
	CString m_sWindow;//
	CString m_s5;//
	CString m_s4;//
	CString m_s3;//
	CString m_s2;//
	CString m_s1;//
	CString m_s0;//
	BOOL SaveReg();//
	BOOL GetReg();//
	BOOL SetScoreListItem(int Index,CString nsName,int ndScore);
	BOOL GetScoreListItem(int Index,CString& rsName,int& rdScore);
	//{{AFX_MSG(CSameBallApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAMEBALL_H__94E17C65_1EE0_11D4_A0AA_0080AD76C3BA__INCLUDED_)

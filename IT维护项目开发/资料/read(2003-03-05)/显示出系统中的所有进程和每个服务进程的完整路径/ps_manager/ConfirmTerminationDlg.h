/////////////////////////////////////////////////////////////////////////////
//
// File        : ConfirmTerminationDlg.h
// Project     : TERMINATOR
// Component   : Terminator
//---------------------------------------------------------------------------
// Description : 
//
/////////////////////////////////////////////////////////////////////////////
//
// SourceSafe Strings. Do not change.
//---------------------------------------------------------------------------
// $Author: Jeskes $
// $Date: 20.04.98 10:00 $
// $Revision: 1 $
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef CONFIRMTERMINATIONDLG_H
#define CONFIRMTERMINATIONDLG_H

/////////////////////////////////////////////////////////////////////////////
// CConfirmTerminationDlg
/////////////////////////////////////////////////////////////////////////////

class CConfirmTerminationDlg : public CDialog
{
//---------------------------------------------------------------------------
// construction
//---------------------------------------------------------------------------
public:
	CConfirmTerminationDlg( CWnd* pParent = NULL );

//---------------------------------------------------------------------------
// dialog data
//---------------------------------------------------------------------------
public:
	//{{AFX_DATA(CConfirmTerminationDlg)
	enum { IDD = IDD_CONFIRM_TERMINATION };
	DWORD	m_idProcess;
	CString	m_sProcessPath;
	//}}AFX_DATA

//---------------------------------------------------------------------------
// overrides
//---------------------------------------------------------------------------
public:
	//{{AFX_VIRTUAL(CConfirmTerminationDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

//---------------------------------------------------------------------------
// message map
//---------------------------------------------------------------------------
protected:
	//{{AFX_MSG(CConfirmTerminationDlg)
	afx_msg void OnNo();
	afx_msg void OnYes();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif

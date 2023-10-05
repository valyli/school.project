#if !defined(AFX_RECORDSETEMPLOYEES_H__0D58C975_B6C1_11D3_BB5A_0080C8EE1D0D__INCLUDED_)
#define AFX_RECORDSETEMPLOYEES_H__0D58C975_B6C1_11D3_BB5A_0080C8EE1D0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RecordsetEmployees.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRecordsetEmployees recordset
#include "afxdb.h"
class CRecordsetEmployees : public CRecordset
{
public:
	CRecordsetEmployees(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRecordsetEmployees)

// Field/Param Data
	//{{AFX_FIELD(CRecordsetEmployees, CRecordset)
	double	m_SSN;
	CString	m_NAME;
	CString	m_ADDRESS;
	CString	m_TITLE;
	CTime	m_HIRE_DATE;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecordsetEmployees)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECORDSETEMPLOYEES_H__0D58C975_B6C1_11D3_BB5A_0080C8EE1D0D__INCLUDED_)

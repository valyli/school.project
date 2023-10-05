#if !defined(AFX_DAORECORDSETEMPLOYEES_H__2E19D160_4752_11D2_953B_97EA2B04013B__INCLUDED_)
#define AFX_DAORECORDSETEMPLOYEES_H__2E19D160_4752_11D2_953B_97EA2B04013B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DaoRecordsetEmployees.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDaoRecordsetEmployees DAO recordset

class CDaoRecordsetEmployees : public CDaoRecordset
{
public:
	CDaoRecordsetEmployees(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDaoRecordsetEmployees)

// Field/Param Data
	//{{AFX_FIELD(CDaoRecordsetEmployees, CDaoRecordset)
	double	m_SSN;
	CString	m_NAME;
	CString	m_ADDRESS;
	CString	m_TITLE;
	COleDateTime	m_HIRE_DATE;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDaoRecordsetEmployees)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DAORECORDSETEMPLOYEES_H__2E19D160_4752_11D2_953B_97EA2B04013B__INCLUDED_)

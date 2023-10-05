// UsingDBSet.h : interface of the CUsingDBSet class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_USINGDBSET_H__B82F4AB1_A5E3_11CF_BC51_C38562E5D356__INCLUDED_)
#define AFX_USINGDBSET_H__B82F4AB1_A5E3_11CF_BC51_C38562E5D356__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CUsingDBSet : public CRecordset
{
public:
	CUsingDBSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CUsingDBSet)

// Field/Param Data
	//{{AFX_FIELD(CUsingDBSet, CRecordset)
	CString	m_Remote_Host;
	CString	m_Path_Info;
	CString	m_HTTP_User_Agent;
	long	m_ID;
	CString	m_CustomerID;
	CString	m_CompanyName;
	CString	m_ContactName;
	CString	m_ContactTitle;
	CString	m_Address;
	CString	m_City;
	CString	m_Region;
	CString	m_PostalCode;
	CString	m_Country;
	CString	m_Phone;
	CString	m_Fax;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUsingDBSet)
	public:
	virtual CString GetDefaultConnect();	// Default connection string
	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USINGDBSET_H__B82F4AB1_A5E3_11CF_BC51_C38562E5D356__INCLUDED_)

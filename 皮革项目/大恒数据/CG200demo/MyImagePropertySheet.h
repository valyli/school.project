#if !defined(AFX_MYIMAGEPROPERTYSHEET_H__09C2E841_A400_11D3_AFDB_5254AB109661__INCLUDED_)
#define AFX_MYIMAGEPROPERTYSHEET_H__09C2E841_A400_11D3_AFDB_5254AB109661__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyImagePropertySheet.h : header file
//

#include "ImageProperty.h"

/////////////////////////////////////////////////////////////////////////////
// CMyImagePropertySheet

class CMyImagePropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CMyImagePropertySheet)

// Construction
public:
	CMyImagePropertySheet(CWnd* pParentWnd = NULL);
//	CMyImagePropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
//	CMyImagePropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	CImageProperty_Image *m_Page1;
	CImageProperty_Source *m_Page2;
	CImageProperty_Color *m_Page3;
	CImageProperty_Field *m_Page4;
	CImageProperty_Win *m_Page5;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyImagePropertySheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyImagePropertySheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyImagePropertySheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYIMAGEPROPERTYSHEET_H__09C2E841_A400_11D3_AFDB_5254AB109661__INCLUDED_)

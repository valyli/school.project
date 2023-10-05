#if !defined(AFX_XMLTREEVIEWCTRL_H__BDFBA27F_718D_4865_80E0_388CB0CE7D05__INCLUDED_)
#define AFX_XMLTREEVIEWCTRL_H__BDFBA27F_718D_4865_80E0_388CB0CE7D05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XmlTreeViewCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXmlTreeViewCtrl window

#include "XmlMemMapping.h"



class CXmlTreeViewCtrl : public CTreeCtrl
{
// Construction
public:
	CXmlTreeViewCtrl();

// Attributes
public:

// Operations
public:
	bool SearchChild(IXMLDOMNodePtr pChild);
	bool SearchChildren(IXMLDOMNodePtr pParent);
	bool SetXml2View(CString strFileName);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXmlTreeViewCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	CXmlMemMapping m_XmlMemMapping;
	virtual ~CXmlTreeViewCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CXmlTreeViewCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XMLTREEVIEWCTRL_H__BDFBA27F_718D_4865_80E0_388CB0CE7D05__INCLUDED_)

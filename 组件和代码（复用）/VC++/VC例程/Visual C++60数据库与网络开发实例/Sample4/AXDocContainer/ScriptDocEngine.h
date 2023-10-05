#if !defined(AFX_SCRIPTDOCENGINE_H__18990D65_3474_11D2_8F0B_F54176DCF130__INCLUDED_)
#define AFX_SCRIPTDOCENGINE_H__18990D65_3474_11D2_8F0B_F54176DCF130__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ScriptDocEngine.h : header file
//

#include "ScriptEngine.h"

class CScriptDocument;

/////////////////////////////////////////////////////////////////////////////
// CScriptDocEngine command target

class CScriptDocEngine : public CScriptEngine 
{
	DECLARE_DYNAMIC(CScriptDocEngine)

public:
	CScriptDocEngine();           
	virtual ~CScriptDocEngine();

// Attributes
public:

	CScriptDocument* GetDocument() const
	{
		return m_pDoc;
	}

	void SetDocument(CScriptDocument* pDoc)
	{
		m_pDoc=pDoc;
	}

// Operations
public:
	virtual HRESULT OnGetItemInfo(
		/* [in] */ LPCOLESTR   pstrName,
		/* [in] */ DWORD       dwReturnMask,
		/* [out]*/ IUnknown**  ppUnknownItem,
		/* [out]*/ ITypeInfo** ppTypeInfo);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptDocEngine)
	//}}AFX_VIRTUAL

// Implementation
protected:
	

	// Generated message map functions
	//{{AFX_MSG(CScriptDocEngine)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	CScriptDocument*	m_pDoc;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCRIPTDOCENGINE_H__18990D65_3474_11D2_8F0B_F54176DCF130__INCLUDED_)

// AutoATLDoc.h : interface of the CAutoATLDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUTOATLDOC_H__8BE6902F_68EF_11D2_9AE7_00A0C9E52DCB__INCLUDED_)
#define AFX_AUTOATLDOC_H__8BE6902F_68EF_11D2_9AE7_00A0C9E52DCB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CAutoATLDoc : public CDocument,
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAutoATLDoc, &CLSID_Document>,
	public IConnectionPointContainerImpl<CAutoATLDoc>,
	public IDispatchImpl<IDocument, &IID_IDocument, &LIBID_AutoATLLib>
{
protected: // create from serialization only
	CAutoATLDoc();
	DECLARE_DYNCREATE_ATL(CAutoATLDoc)

public:

	DECLARE_REGISTRY_RESOURCEID(IDR_DOCUMENT)
DECLARE_NOT_AGGREGATABLE(CAutoATLDoc)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAutoATLDoc)
	COM_INTERFACE_ENTRY(IDocument)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CAutoATLDoc)
END_CONNECTION_POINT_MAP()

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoATLDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	STDMETHOD(Hello)();
	virtual ~CAutoATLDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAutoATLDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOATLDOC_H__8BE6902F_68EF_11D2_9AE7_00A0C9E52DCB__INCLUDED_)

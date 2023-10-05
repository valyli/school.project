// ScriptEngine.h : interface of the CScriptEngine class
//

#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

#include <activscp.h>

class CScriptEngine : public CCmdTarget
{
	DECLARE_DYNAMIC(CScriptEngine)

public:
	// use this method to create an instance of an ActiveX Scripting engine
	HRESULT Create(/* [in] */ REFCLSID clsidScriptEngine);

	// use this method to determine the scripting engine's state
	SCRIPTSTATE GetScriptState();

	// use this method to add a new to the script's namespace
	HRESULT AddNamedItem(
		/* [in] */ LPCOLESTR pstrName,
		/* [in] */ DWORD dwFlags = SCRIPTITEM_ISSOURCE	| SCRIPTITEM_ISVISIBLE);

	// use this method to add an entire typelib to the script's namespace
	HRESULT AddTypeLib(
		/* [in] */ REFGUID guidTypeLib,
		/* [in] */ DWORD dwMaj,
		/* [in] */ DWORD dwMin,
		/* [in] */ DWORD dwFlags);

	// use this method to get the scripting engine's automation interface
	IDispatch* GetScriptDispatch(LPCOLESTR pstrItemName);

	// use this method to give the scripting engine the script
	HRESULT ParseScriptText(
		/* [in] */ LPCOLESTR  pstrCode,
		/* [in] */ LPCOLESTR  pstrItemName = NULL,
		/* [in] */ IUnknown*  punkContext = NULL,
		/* [in] */ LPCOLESTR  pstrEndDelimiter = NULL,
		/* [in] */ DWORD      dwSourceContextCookie = 0,
    /* [in] */ ULONG      ulStartingLineNumber = 0,
		/* [in] */ DWORD      dwFlags = 0,
		/* [out]*/ VARIANT*   pvarResult = NULL,
		/* [out]*/ EXCEPINFO* pexcepinfo = NULL);

	// use this method to run the script (and connect it to event sources)
	HRESULT Run() { return Connect(); }
	HRESULT Connect();

	// use this method to pause the script (disconnect it from event sources)
	HRESULT Pause() { return Disconnect(); }
	HRESULT Disconnect();

	// use this method to return the scripting engine to the state it was in just
	// after it was created via Create()
	HRESULT Close();

	// use this method to release the scripting engine created by Create()
	void ReleaseEngine();

	BOOL IsCreated() const
	{
		return m_pActiveScript!=0;
	}

public:
	// IActiveScriptSite overridables
  virtual HRESULT OnGetLCID(LCID* pLCID);
	
	virtual HRESULT OnGetItemInfo(
		/* [in] */ LPCOLESTR   pstrName,
		/* [in] */ DWORD       dwReturnMask,
		/* [out]*/ IUnknown**  ppUnknownItem,
		/* [out]*/ ITypeInfo** ppTypeInfo);
	
	virtual BSTR OnGetDocVersionString();

	virtual void OnScriptTerminate(
		/* [in] */ const VARIANT* pvarResult,
		/* [in] */ const EXCEPINFO* pexcepinfo);
	
	virtual void OnStateChange(
	  /* [in] */ SCRIPTSTATE ssScriptState);
  
	virtual void OnScriptError(/* [in] */ IActiveScriptError* pASE);
	
	virtual void OnEnterScript();
	
	virtual void OnLeaveScript();

	// IActiveScriptSiteWindow overridables
	virtual HRESULT OnGetWindow(HWND* phwnd);
	
	virtual HRESULT OnEnableModeless(/* [in] */ BOOL bEnable);

// Implementation
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	// constructors
	CScriptEngine();
	CScriptEngine(/* [in] */ REFCLSID clsidScriptEngine);

	// serialization
	void Serialize(CArchive& ar);

	// destructor
	virtual ~CScriptEngine();

// Interface Maps
	DECLARE_INTERFACE_MAP()
		
	// IActiveScriptSite
	BEGIN_INTERFACE_PART(ActiveScriptSite, IActiveScriptSite)
		INIT_INTERFACE_PART(CActiveScriptSite, ActiveScriptSite)
		STDMETHOD (GetLCID) (/* [out] */ LCID *plcid);
	  STDMETHOD (GetItemInfo) (
      /* [in]  */ LPCOLESTR   pstrName,
      /* [in]  */ DWORD       dwReturnMask,
      /* [out] */ IUnknown**  ppunkItem, 
      /* [out] */ ITypeInfo** ppTypeInfo);
		STDMETHOD (GetDocVersionString) (/* [out] */ BSTR *pstrVersionString);
		STDMETHOD (OnScriptTerminate) (
			/* [in] */ const VARIANT *pvarResult,
			/* [in] */ const EXCEPINFO *pexcepinfo);
		STDMETHOD (OnStateChange) (/* [in] */ SCRIPTSTATE ssScriptState);
		STDMETHOD (OnScriptError) (/* [in] */ IActiveScriptError *pase);
    STDMETHOD (OnEnterScript) ();
		STDMETHOD (OnLeaveScript) ();
	END_INTERFACE_PART(ActiveScriptSite)

	// IActiveScriptSiteWindow
	BEGIN_INTERFACE_PART(ActiveScriptSiteWindow, IActiveScriptSiteWindow)
		INIT_INTERFACE_PART(CActiveScriptSiteWindow, ActiveScriptSiteWindow)
		STDMETHOD (GetWindow) (/* [out] */ HWND *phwnd);
		STDMETHOD (EnableModeless)(/* [in] */ BOOL fEnable);
	END_INTERFACE_PART(ActiveScriptSiteWindow)

private:
	HRESULT m_hrScriptError;
	// script engine's interface pointers
	IActiveScript* m_pActiveScript;
	IActiveScriptParse* m_pActiveScriptParse;
};

#endif
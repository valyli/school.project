#include "stdafx.h"
#include "ScriptEngine.h"
#include "Utils.h"

IMPLEMENT_DYNAMIC(CScriptEngine, CCmdTarget)

/////////////////////////////////////////////////////////////////////////////
// CScriptEngine interface maps

BEGIN_INTERFACE_MAP(CScriptEngine, CCmdTarget)
  INTERFACE_PART(CScriptEngine, IID_IActiveScriptSite, ActiveScriptSite)
  INTERFACE_PART(CScriptEngine, IID_IActiveScriptSiteWindow, ActiveScriptSiteWindow)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptEngine methods

CScriptEngine::CScriptEngine() :
  m_hrScriptError(S_OK),
  m_pActiveScript(NULL),
	m_pActiveScriptParse(NULL)
{
	TRACE_IN("CScriptEngine::CScriptEngine");
}

CScriptEngine::CScriptEngine(REFCLSID clsidScriptEngine) :
  m_hrScriptError(S_OK),
  m_pActiveScript(NULL),
	m_pActiveScriptParse(NULL)
{
	TRACE_IN("CScriptEngine::CScriptEngine");

	// create the engine
	Create(clsidScriptEngine);
}

void CScriptEngine::ReleaseEngine()
{
	TRACE_IN("CScriptEngine::ReleaseEngine");

	// release engine interfaces
	RELEASE(m_pActiveScriptParse);

	if(m_pActiveScript)
		m_pActiveScript->Close();

	RELEASE(m_pActiveScript);
}

CScriptEngine::~CScriptEngine()
{
	TRACE_IN("CScriptEngine::~CScriptEngine");

	ReleaseEngine();
}

HRESULT CScriptEngine::Create(REFCLSID clsidScriptEngine)
{
	TRACE_IN("CScriptEngine::Create");

	// release the current engine (if any)
	ReleaseEngine();

	// create script engine
	HRESULT hr = CoCreateInstance(clsidScriptEngine,
    NULL, // no aggregation
    CLSCTX_INPROC_SERVER,
		IID_IActiveScript,
    (LPVOID*)&m_pActiveScript);

	// if success ...
	if (SUCCEEDED(hr)) {
		// set the script engine's script site
		hr = STDCOMCALL(m_pActiveScript, SetScriptSite(&m_xActiveScriptSite));

		// if success ...
		if (SUCCEEDED(hr)) {
			// get the engine's IActiveScriptParse interface
			hr = STDCOMCALL(m_pActiveScript, QueryInterface(IID_IActiveScriptParse,
				(void**)&m_pActiveScriptParse));
			
			// if success ...
			if (SUCCEEDED(hr)) {
				// initialize the engine
				hr = STDCOMCALL(m_pActiveScriptParse, InitNew());

				// if failure ..
				if (FAILED(hr)) {
					AfxMessageBox("Failed to initialize script engine.");
					ASSERT(FALSE);
					ReleaseEngine();
				}
			} else {
				AfxMessageBox("Failed to obtain script engine's IActiveScriptParse interface.");
				ASSERT(FALSE);
				ReleaseEngine();
			}
		} else {
			AfxMessageBox("Failed to set script engine's site.");
			ASSERT(FALSE);
			ReleaseEngine();
		}
	} else {
		AfxMessageBox("Failed to create script engine.");
		ASSERT(FALSE);
	}

	return SUCCEEDED(hr);
}

SCRIPTSTATE CScriptEngine::GetScriptState()
{
	TRACE_IN("CScriptEngine::GetScriptState");

	// this is what we'll return
	SCRIPTSTATE ss = SCRIPTSTATE_UNINITIALIZED;

	// call the script's method
	HRESULT hr = STDCOMCALL(m_pActiveScript, GetScriptState(&ss));
	ASSERT(SUCCEEDED(hr));

	return ss;
}

HRESULT CScriptEngine::AddNamedItem(
		/* [in] */ LPCOLESTR pstrName,
		/* [in] */ DWORD     dwFlags)
{
	TRACE_IN("CScriptEngine::AddNamedItem");

	ASSERT(pstrName != NULL);

	// call the engine's method
	HRESULT hr = STDCOMCALL(m_pActiveScript, AddNamedItem(pstrName, dwFlags));
	ASSERT(SUCCEEDED(hr));

	return hr;
}

HRESULT CScriptEngine::AddTypeLib(
	/* [in] */ REFGUID guidTypeLib,
	/* [in] */ DWORD   dwMaj,
	/* [in] */ DWORD   dwMin,
	/* [in] */ DWORD   dwFlags)
{
	TRACE_IN("CScriptEngine::AddTypeLib");

	// call the engine's method
	HRESULT hr = STDCOMCALL(m_pActiveScript, AddTypeLib(guidTypeLib, dwMaj, dwMin, dwFlags));
	ASSERT(SUCCEEDED(hr));

	return hr;
}

IDispatch* CScriptEngine::GetScriptDispatch(LPCOLESTR pstrItemName)
{
	TRACE_IN("CScriptEngine::GetScriptDispatch");

	ASSERT(pstrItemName != NULL);

	// this is what we'll return
	IDispatch* pDispatch = NULL;

	// call the engine's method
	HRESULT hr = STDCOMCALL(m_pActiveScript, GetScriptDispatch(pstrItemName, &pDispatch));
	ASSERT(SUCCEEDED(hr));
	ASSERT(pDispatch != NULL);

	return pDispatch;
}

HRESULT CScriptEngine::ParseScriptText(
		/* [in] */ LPCOLESTR pstrCode,
		/* [in] */ LPCOLESTR pstrItemName,
		/* [in] */ IUnknown* punkContext,
		/* [in] */ LPCOLESTR pstrEndDelimiter,
		/* [in] */ DWORD dwSourceContextCookie,
    /* [in] */ ULONG ulStartingLineNumber,
		/* [in] */ DWORD dwFlags,
		/* [out]*/ VARIANT* pvarResult,
		/* [out]*/ EXCEPINFO* pexcepinfo)
{
	TRACE_IN("CScriptEngine::ParseScriptText");

	ASSERT(pstrCode != NULL);

	HRESULT hr = STDCOMCALL(m_pActiveScriptParse, ParseScriptText(
		pstrCode,
		pstrItemName,
		punkContext,
		pstrEndDelimiter,
		dwSourceContextCookie,
		ulStartingLineNumber,
		dwFlags,
		pvarResult,
		pexcepinfo));

	return hr;
}

HRESULT CScriptEngine::Connect()
{
	TRACE_IN("CScriptEngine::Connect");

	// reset the HRESULT used in OnScriptError
	m_hrScriptError = S_OK;

	// call the script's method
	HRESULT hr = STDCOMCALL(m_pActiveScript, SetScriptState(SCRIPTSTATE_CONNECTED));
	ASSERT(SUCCEEDED(hr));

	// if success ...
	if (SUCCEEDED(hr)) {
		// return any script error caught by OnScriptError()
		hr = m_hrScriptError;
	}

	return hr;
}

HRESULT CScriptEngine::Disconnect()
{
	TRACE_IN("CScriptEngine::Disconnect");

	// call the script's method
	HRESULT hr = STDCOMCALL(m_pActiveScript, SetScriptState(SCRIPTSTATE_DISCONNECTED));
	ASSERT(SUCCEEDED(hr));

	return hr;
}

HRESULT CScriptEngine::Close()
{
	TRACE_IN("CScriptEngine::Close");

	// call the script's method
	HRESULT hr = STDCOMCALL(m_pActiveScript, Close());
	ASSERT(SUCCEEDED(hr));

	return hr;
}

HRESULT CScriptEngine::OnGetLCID(LCID* pLCID)
{
	TRACE_IN("CScriptEngine::OnGetLCID");
	return E_NOTIMPL;
}

HRESULT CScriptEngine::OnGetItemInfo(
		/* [in] */ LPCOLESTR   pstrName,
		/* [in] */ DWORD       dwReturnMask,
		/* [out]*/ IUnknown**  ppUnknownItem,
		/* [out]*/ ITypeInfo** ppTypeInfo)
{
	TRACE_IN("CScriptEngine::OnGetItemInfo");
	return E_NOTIMPL;
}

BSTR CScriptEngine::OnGetDocVersionString()
{
	TRACE_IN("CScriptEngine::OnGetDocVersionString");
	return NULL;
}

void CScriptEngine::OnScriptTerminate(
		/* [in] */ const VARIANT*   pvarResult,
		/* [in] */ const EXCEPINFO* pexcepinfo)
{
	TRACE_IN("CScriptEngine::OnScriptTerminate");
}

void CScriptEngine::OnStateChange(/* [in] */ SCRIPTSTATE ss)
{
	TRACE_IN("CScriptEngine::OnStateChange");

	switch (ss) {
		case SCRIPTSTATE_UNINITIALIZED:
			TRACE_MSG(("State -> Uninitialized"));
			break;
		case SCRIPTSTATE_INITIALIZED:
			TRACE_MSG(("State -> Initialized"));
			break;
		case SCRIPTSTATE_STARTED:
			TRACE_MSG(("State -> Started"));
			break;
    case SCRIPTSTATE_CONNECTED:
			TRACE_MSG(("State -> Connected"));
			break;
    case SCRIPTSTATE_DISCONNECTED:
			TRACE_MSG(("State -> Disonnected"));
			break;
    case SCRIPTSTATE_CLOSED:
			TRACE_MSG(("State -> Closed"));
			break;
		default:
			TRACE_ERR(("State -> Invalid"));
			ASSERT(FALSE);
			break;
	}
}

void CScriptEngine::OnScriptError(/* [in] */ IActiveScriptError* pASE)
{
	TRACE_IN("CScriptEngine::OnScriptError");

	DWORD dwSourceContext = 0;
	ULONG nLineNumber = 0;
	LONG  nCharPosition = 0;

	// get source line info
	HRESULT hr = STDCOMCALL(pASE, GetSourcePosition(
    &dwSourceContext,
    &nLineNumber,
    &nCharPosition));
	ASSERT(SUCCEEDED(hr));

	
	// get the exception info
	EXCEPINFO excepinfo;
	memset(&excepinfo, 0, sizeof(excepinfo));
	hr = STDCOMCALL(pASE, GetExceptionInfo(&excepinfo));
	ASSERT(SUCCEEDED(hr));

	// format error message
	CString strMsg;
	strMsg.Format("Script error detected at line %d.", nLineNumber);

	// get the source line
	BSTR bstrSourceLine;
	hr = STDCOMCALL(pASE, GetSourceLineText(&bstrSourceLine));
	

	if (SUCCEEDED(hr) && bstrSourceLine != NULL) {
		strMsg += "\nSource line: ";
		strMsg += CString(bstrSourceLine);
		::SysFreeString(bstrSourceLine);
	}

	if (excepinfo.bstrDescription != NULL) {
		strMsg += "\nDescription: ";
		strMsg += CString(excepinfo.bstrDescription);
	}

	// issue error message
	AfxMessageBox(strMsg, MB_OK | MB_ICONEXCLAMATION);

	// script failed
	m_hrScriptError = E_FAIL;
}

void CScriptEngine::OnEnterScript()
{
	TRACE_IN("CScriptEngine::OnEnterScript");
}

void CScriptEngine::OnLeaveScript()
{
	TRACE_IN("CScriptEngine::OnLeaveScript");
}

HRESULT CScriptEngine::OnGetWindow(HWND* phwnd)
{
	TRACE_IN("CScriptEngine::OnGetWindow");

	// get the app's main window
	*phwnd = AfxGetApp()->m_pMainWnd->m_hWnd;
	
	return S_OK;
}

HRESULT CScriptEngine::OnEnableModeless(/* [in] */ BOOL bEnable)
{	
	TRACE_IN("CScriptEngine::OnEnableModeless");
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CScriptEngine::XActiveScriptSite methods

STDMETHODIMP_(ULONG) CScriptEngine::XActiveScriptSite::AddRef()
{
	TRACE_IN("CScriptEngine::XActiveScriptSite::AddRef");

	METHOD_PROLOGUE(CScriptEngine, ActiveScriptSite)

	ULONG nResult = (ULONG)pThis->ExternalAddRef();

	return nResult;
}

STDMETHODIMP_(ULONG) CScriptEngine::XActiveScriptSite::Release()
{
	TRACE_IN("CScriptEngine::XActiveScriptSite::Release");

	METHOD_PROLOGUE(CScriptEngine, ActiveScriptSite)

	ULONG nResult = (ULONG)pThis->ExternalRelease();

	return nResult;
}

STDMETHODIMP CScriptEngine::XActiveScriptSite::QueryInterface(
	REFIID iid, LPVOID* ppvObj)
{
	TRACE_IN("CScriptEngine::XActiveScriptSite::QueryInterface");

	METHOD_PROLOGUE(CScriptEngine, ActiveScriptSite)

	HRESULT hr = (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);

	return hr;
}

STDMETHODIMP CScriptEngine::XActiveScriptSite::GetLCID(LCID* pLCID)
{
	TRACE_IN("CScriptEngine::XActiveScriptSite::GetLCID");

	METHOD_PROLOGUE(CScriptEngine, ActiveScriptSite)
	
	HRESULT hr = pThis->OnGetLCID(pLCID);

	return hr;
}

STDMETHODIMP CScriptEngine::XActiveScriptSite::GetItemInfo(
      /* [in]  */ LPCOLESTR   pstrName,
      /* [in]  */ DWORD       dwReturnMask,
      /* [out] */ IUnknown  **ppunkItem, 
      /* [out] */ ITypeInfo **ppTypeInfo)
{
	TRACE_IN("CScriptEngine::XActiveScriptSite::GetItemInfo");

	METHOD_PROLOGUE(CScriptEngine, ActiveScriptSite)
	
	HRESULT hr = pThis->OnGetItemInfo(pstrName, dwReturnMask, ppunkItem, ppTypeInfo);

	return hr;
}

STDMETHODIMP CScriptEngine::XActiveScriptSite::GetDocVersionString(BSTR* pbstr)
{
	TRACE_IN("CScriptEngine::XActiveScriptSite::GetDocVersionString");

	ASSERT(pbstr != NULL);

	METHOD_PROLOGUE(CScriptEngine, ActiveScriptSite)
	
	*pbstr = pThis->OnGetDocVersionString();

	return S_OK;
}

STDMETHODIMP CScriptEngine::XActiveScriptSite::OnScriptTerminate(
	/* [in] */ const VARIANT* pvarResult,
	/* [in] */ const EXCEPINFO* pexcepinfo)
{
	TRACE_IN("CScriptEngine::XActiveScriptSite::OnScriptTerminate");

	METHOD_PROLOGUE(CScriptEngine, ActiveScriptSite)
	
	pThis->OnScriptTerminate(pvarResult, pexcepinfo);

	return S_OK;
}

STDMETHODIMP CScriptEngine::XActiveScriptSite::OnStateChange(/* [in] */ SCRIPTSTATE ssScriptState)
{
	TRACE_IN("CScriptEngine::XActiveScriptSite::OnStateChange");

	METHOD_PROLOGUE(CScriptEngine, ActiveScriptSite)
	
	pThis->OnStateChange(ssScriptState);

	return S_OK;
}

STDMETHODIMP CScriptEngine::XActiveScriptSite::OnScriptError(/* [in] */ IActiveScriptError *pASE)
{
	TRACE_IN("CScriptEngine::XActiveScriptSite::OnScriptError");

	METHOD_PROLOGUE(CScriptEngine, ActiveScriptSite)
	
	pThis->OnScriptError(pASE);

	return S_OK;
}

STDMETHODIMP CScriptEngine::XActiveScriptSite::OnEnterScript()
{
	TRACE_IN("CScriptEngine::XActiveScriptSite::OnEnterScript");

	METHOD_PROLOGUE(CScriptEngine, ActiveScriptSite)
	
	pThis->OnEnterScript();

	return S_OK;
}

STDMETHODIMP CScriptEngine::XActiveScriptSite::OnLeaveScript()
{
	TRACE_IN("CScriptEngine::XActiveScriptSite::OnLeaveScript");

	METHOD_PROLOGUE(CScriptEngine, ActiveScriptSite)
	
	pThis->OnLeaveScript();

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CScriptEngine::XActiveScriptSiteWindow methods

STDMETHODIMP_(ULONG) CScriptEngine::XActiveScriptSiteWindow::AddRef()
{
	TRACE_IN("CScriptEngine::XActiveScriptSiteWindow::AddRef");

	METHOD_PROLOGUE(CScriptEngine, ActiveScriptSiteWindow)

	ULONG nResult = (ULONG)pThis->ExternalAddRef();

	return nResult;
}

STDMETHODIMP_(ULONG) CScriptEngine::XActiveScriptSiteWindow::Release()
{
	TRACE_IN("CScriptEngine::XActiveScriptSiteWindow::Release");

	METHOD_PROLOGUE(CScriptEngine, ActiveScriptSiteWindow)

	ULONG nResult = (ULONG)pThis->ExternalRelease();

	return nResult;
}

STDMETHODIMP CScriptEngine::XActiveScriptSiteWindow::QueryInterface(
	REFIID iid, LPVOID* ppvObj)
{
	TRACE_IN("CScriptEngine::XActiveScriptSiteWindow::QueryInterface");

	METHOD_PROLOGUE(CScriptEngine, ActiveScriptSiteWindow)

	HRESULT hr = (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);

	return hr;
}

STDMETHODIMP CScriptEngine::XActiveScriptSiteWindow::GetWindow(/* [out] */ HWND *phwnd)
{
	TRACE_IN("CScriptEngine::XActiveScriptSiteWindow::GetWindow");

	METHOD_PROLOGUE(CScriptEngine, ActiveScriptSiteWindow)
	
	HRESULT hr = pThis->OnGetWindow(phwnd);

	return hr;
}

STDMETHODIMP CScriptEngine::XActiveScriptSiteWindow::EnableModeless(/* [in] */ BOOL bEnable)
{
	TRACE_IN("CScriptEngine::XActiveScriptSiteWindow::EnableModeless");

	METHOD_PROLOGUE(CScriptEngine, ActiveScriptSiteWindow)
	
	HRESULT hr = pThis->OnEnableModeless(bEnable);

	return hr;
}

/////////////////////////////////////////////////////////////////////////////
// CScriptEngine diagnostics

#ifdef _DEBUG
void CScriptEngine::AssertValid() const
{
	CCmdTarget::AssertValid();
}

void CScriptEngine::Dump(CDumpContext& dc) const
{
	CCmdTarget::Dump(dc);

	dc << "IActiveScript pointer = " << m_pActiveScript << "\n";
	dc << "IActiveScriptParse pointer = " << m_pActiveScriptParse;
}
#endif //_DEBUG

void CScriptEngine::Serialize(CArchive& ar)
{
	CCmdTarget::Serialize(ar);

	// TODO:  Need to QI for one of the script engine's IPersist* interfaces
	// and then call that interface to serialize the engine's peristent data.

  if (ar.IsStoring()) {
    // TODO:  add storing code here
  } else {
		// TODO:  add loading code here
  }
}

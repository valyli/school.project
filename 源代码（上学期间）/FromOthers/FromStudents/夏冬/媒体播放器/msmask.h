#if !defined(AFX_MSMASK_H__E360BDF1_E72B_4D60_8BC4_0904FC2C2851__INCLUDED_)
#define AFX_MSMASK_H__E360BDF1_E72B_4D60_8BC4_0904FC2C2851__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CPicture;
class COleFont;

/////////////////////////////////////////////////////////////////////////////
// CMSMask wrapper class

class CMSMask : public CWnd
{
protected:
	DECLARE_DYNCREATE(CMSMask)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xc932ba85, 0x4374, 0x101b, { 0xa5, 0x6c, 0x0, 0xaa, 0x0, 0x36, 0x68, 0xdc } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

// Attributes
public:

// Operations
public:
	long GetClipMode();
	void SetClipMode(long nNewValue);
	BOOL GetPromptInclude();
	void SetPromptInclude(BOOL bNewValue);
	BOOL GetAllowPrompt();
	void SetAllowPrompt(BOOL bNewValue);
	BOOL GetAutoTab();
	void SetAutoTab(BOOL bNewValue);
	long GetMousePointer();
	void SetMousePointer(long nNewValue);
	BOOL GetHideSelection();
	void SetHideSelection(BOOL bNewValue);
	short GetMaxLength();
	void SetMaxLength(short nNewValue);
	CString GetFormat();
	void SetFormat(LPCTSTR lpszNewValue);
	CString GetMask();
	void SetMask(LPCTSTR lpszNewValue);
	CString GetFormattedText();
	void SetFormattedText(LPCTSTR lpszNewValue);
	long GetSelLength();
	void SetSelLength(long nNewValue);
	long GetSelStart();
	void SetSelStart(long nNewValue);
	CString GetSelText();
	void SetSelText(LPCTSTR lpszNewValue);
	CString GetClipText();
	void SetClipText(LPCTSTR lpszNewValue);
	CString GetPromptChar();
	void SetPromptChar(LPCTSTR lpszNewValue);
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	CPicture GetMouseIcon();
	void SetMouseIcon(LPDISPATCH newValue);
	void SetRefMouseIcon(LPDISPATCH newValue);
	long GetAppearance();
	void SetAppearance(long nNewValue);
	unsigned long GetBackColor();
	void SetBackColor(unsigned long newValue);
	COleFont GetFont();
	void SetRefFont(LPDISPATCH newValue);
	unsigned long GetForeColor();
	void SetForeColor(unsigned long newValue);
	BOOL GetEnabled();
	void SetEnabled(BOOL bNewValue);
	long GetHWnd();
	void SetHWnd(long nNewValue);
	long GetBorderStyle();
	void SetBorderStyle(long nNewValue);
	long GetOLEDragMode();
	void SetOLEDragMode(long nNewValue);
	long GetOLEDropMode();
	void SetOLEDropMode(long nNewValue);
	void Refresh();
	void OLEDrag();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSMASK_H__E360BDF1_E72B_4D60_8BC4_0904FC2C2851__INCLUDED_)

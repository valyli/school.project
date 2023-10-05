#if !defined(AFX_ISAM_H__75D383B7_046A_11D2_8A44_0000E81D3D27__INCLUDED_)
#define AFX_ISAM_H__75D383B7_046A_11D2_8A44_0000E81D3D27__INCLUDED_

// ISAM.H - Header file for your Internet Server
//    ISAM Extension

#include "resource.h"

// put your connect string here, or load from registry to avoid recompiling
static const TCHAR szConnectString[] = _T("DSN=Images;UID=;PWD=;");

class CISAMExtension : public CHttpServer
{
public:
	CISAMExtension();
	~CISAMExtension();

// Overrides
	// ClassWizard generated virtual function overrides
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//{{AFX_VIRTUAL(CISAMExtension)
	public:
	virtual BOOL GetExtensionVersion(HSE_VERSION_INFO* pVer);
	//}}AFX_VIRTUAL

//implementation
protected:
	BOOL LoadLongResource(CString& str, UINT nID);

	// TODO: Add handlers for your commands here.
	// For example:

	void Default(CHttpServerContext* pCtxt);
	void GetImage(CHttpServerContext* pCtxt, long nId);
	void GetListFrame(CHttpServerContext* pCtxt);
	void GetDataFrame(CHttpServerContext* pCtxt, long nRecordId);

	DECLARE_PARSE_MAP()

	//{{AFX_MSG(CISAMExtension)
	//}}AFX_MSG
private:
	void OutputJpeg(CHttpServerContext* pCtxt, const CByteArray& data);
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ISAM_H__75D383B7_046A_11D2_8A44_0000E81D3D27__INCLUDED)

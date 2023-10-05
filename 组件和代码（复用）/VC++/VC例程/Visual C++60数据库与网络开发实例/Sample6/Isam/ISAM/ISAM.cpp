// ISAM.CPP - Implementation file for your Internet Server
//    ISAM Extension

#include "stdafx.h"
#include "ImagesRS.h"
#include "binhtmstream.h"
#include "ISAM.h"

///////////////////////////////////////////////////////////////////////
// The one and only CWinApp object
// NOTE: You may remove this object if you alter your project to no
// longer use MFC in a DLL.

CWinApp theApp;

///////////////////////////////////////////////////////////////////////
// command-parsing map

BEGIN_PARSE_MAP(CISAMExtension, CHttpServer)
	// TODO: insert your ON_PARSE_COMMAND() and 
	// ON_PARSE_COMMAND_PARAMS() here to hook up your commands.
	// For example:

	ON_PARSE_COMMAND(Default, CISAMExtension, ITS_EMPTY)
	DEFAULT_PARSE_COMMAND(Default, CISAMExtension)
	ON_PARSE_COMMAND(GetListFrame, CISAMExtension, ITS_EMPTY)
	ON_PARSE_COMMAND(GetDataFrame, CISAMExtension, ITS_I4)
	ON_PARSE_COMMAND_PARAMS("nRecordId")
	ON_PARSE_COMMAND(GetImage, CISAMExtension, ITS_I4)
	ON_PARSE_COMMAND_PARAMS("nId")
END_PARSE_MAP(CISAMExtension)


///////////////////////////////////////////////////////////////////////
// The one and only CISAMExtension object

CISAMExtension theExtension;

static const UINT nIDHTMLType = 23;
// put your location here, or load from registry to avoid recompiling
static const TCHAR szLocation[] = _T("http://httpserver.foo.com/isapitest/isam.dll");

///////////////////////////////////////////////////////////////////////
// CISAMExtension implementation

CISAMExtension::CISAMExtension()
{
}

CISAMExtension::~CISAMExtension()
{
}

BOOL CISAMExtension::GetExtensionVersion(HSE_VERSION_INFO* pVer)
{
	// Call default implementation for initialization
	CHttpServer::GetExtensionVersion(pVer);

	// Load description string
	TCHAR sz[HSE_MAX_EXT_DLL_NAME_LEN+1];
	ISAPIVERIFY(::LoadString(AfxGetResourceHandle(), IDS_SERVER, sz, HSE_MAX_EXT_DLL_NAME_LEN));
	_tcscpy(pVer->lpszExtensionDesc, sz);
	return TRUE;
}

BOOL CISAMExtension::LoadLongResource(CString& str, UINT nID)
{
	HRSRC hRes;
	HINSTANCE hInst = AfxGetResourceHandle();
	BOOL bResult = FALSE;
	
	hRes = FindResource(hInst, MAKEINTRESOURCE(nID), (LPCTSTR)nIDHTMLType);
	if (hRes == NULL)
		ISAPITRACE1("Error: Resource %d could not be found\r\n", nID);
	else
	{
		DWORD dwSize = SizeofResource(hInst, hRes);
		if (dwSize == 0)
		{
			str.Empty();
			bResult = TRUE;
		}
		else
		{
			LPTSTR pszStorage = str.GetBufferSetLength(dwSize);

			HGLOBAL hGlob = LoadResource(hInst, hRes);
			if (hGlob != NULL)
			{
				LPVOID lpData = LockResource(hGlob);

				if (lpData != NULL)
				{
					memcpy(pszStorage, lpData, dwSize);
					bResult = TRUE;
				}

				FreeResource(hGlob);
			}
		}
	}

#ifdef _DEBUG
	if (!bResult)
		str.Format(_T("<b>Could not find string %d</b>"), nID);
#endif

	return bResult;
}

void CISAMExtension::OutputJpeg(CHttpServerContext* pCtxt, const CByteArray& data)
{
	// Start by writing the proper content type to the client
	AddHeader(pCtxt, _T("Content-Type: image/jpeg\r\n"));
	char szBuff[50];
	int nSize = data.GetSize();
	wsprintf(szBuff, "Content-length: %ld\r\n", nSize);
	AddHeader(pCtxt, szBuff);

	CBinaryHtmlStream* pStream = new CBinaryHtmlStream;
	ISAPIVERIFY(pStream != NULL);

	for (int nCount = 0; nCount<nSize; nCount++)
		*pStream << data[nCount];

	*pCtxt << *pStream;

	delete pStream;
}

///////////////////////////////////////////////////////////////////////
// CISAMExtension command handlers

void CISAMExtension::Default(CHttpServerContext* pCtxt)
{
	GetListFrame(pCtxt);
}

void CISAMExtension::GetImage(CHttpServerContext* pCtxt, long nId)
{
	try
	{
		CDatabase db;
		db.OpenEx(szConnectString, CDatabase::noOdbcDialog | CDatabase::openReadOnly);

		CImagesRS ImageRS(&db);
		ImageRS.m_strFilter = _T("image_id=?");
		ImageRS.m_image_id_param = nId;

		if (ImageRS.Open())
		{
			if (ImageRS.IsBOF())
				*pCtxt << _T("Sorry, the record was deleted while you were browsing.\r\n");
			else
			{
				try
				{
					CFile imageFile(ImageRS.m_image_filename, CFile::modeRead);
					DWORD dwLength = imageFile.GetLength();
					CByteArray data;
					data.SetSize(dwLength);
					imageFile.Read(data.GetData(), dwLength);
					OutputJpeg(pCtxt, data);
				}
				catch (CFileException* e)
				{
					*pCtxt << _T("Sorry, the record was deleted while you were browsing.\r\n");
					e->Delete();
				}
				catch (CMemoryException* e)
				{
					*pCtxt << _T("Sorry, there was a memory error loading the image.\r\n");
					 e->Delete();
				}
			}
			ImageRS.Close();
		}
		else
			*pCtxt << _T("Couldn't open database\r\n");

		db.Close();
	}
	catch (CDBException* pEx)
	{
		*pCtxt << _T("Browser Failed: Couldn't open image data source\r\n");

		TCHAR szError[1024];
		if (pEx->GetErrorMessage(szError, sizeof(szError)))
		{
			*pCtxt << szError;
			*pCtxt << _T("\r\n");
		}
		pEx->Delete(); 
	}
}

void CISAMExtension::GetListFrame(CHttpServerContext* pCtxt)
{
	try
	{
		CDatabase db;
		db.OpenEx(szConnectString, CDatabase::noOdbcDialog | CDatabase::openReadOnly);

		CImagesRS ImagesRS(&db);

		if (ImagesRS.Open())
		{
			if (ImagesRS.IsBOF())
				*pCtxt << _T("Sorry, no records are available at this time.\r\n");
			else
			{
				CString strRecords;
				CString strItem;
				LoadLongResource(strItem, IDR_LISTITEM);
				while (!ImagesRS.IsEOF())
				{
					CString szId;
					itoa(ImagesRS.m_image_id, szId.GetBuffer(10), 10);
					szId.ReleaseBuffer();
					CString strHREF = CString(szLocation) + CString(_T("?")) + CString(_T("GetDataFrame?")) + szId;
					CString strTmpOutput;
					strTmpOutput.Format(strItem, strHREF, ImagesRS.m_image_title);
					strRecords += strTmpOutput;
					ImagesRS.MoveNext();
				}
				CString strOutput;
				CString strResource;
				LoadLongResource(strResource, IDR_LIST);
				strOutput.Format(strResource, strRecords);
				*pCtxt << strOutput;
			}
			ImagesRS.Close();
		}
		else
			*pCtxt << _T("Couldn't open the record set\r\n");

		db.Close();
	}
	catch (CDBException* pEx)
	{
		*pCtxt << _T("Browser Failed: Couldn't open image data source\r\n");

		TCHAR szError[1024];
		if (pEx->GetErrorMessage(szError, sizeof(szError)))
		{
			*pCtxt << szError;
			*pCtxt << _T("\r\n");
		}
		pEx->Delete();
	}
}

void CISAMExtension::GetDataFrame(CHttpServerContext* pCtxt, long nRecordId)
{
	try
	{
		CDatabase db;
		db.OpenEx(szConnectString, CDatabase::noOdbcDialog | CDatabase::openReadOnly);

		CImagesRS ImagesRS(&db);
		ImagesRS.m_strFilter = _T("image_id=?");
		ImagesRS.m_image_id_param = nRecordId;

		if (ImagesRS.Open())
		{
			if (ImagesRS.IsBOF())
				*pCtxt << _T("Sorry, the record was deleted while you were browsing.\r\n");
			else
			{
				CString szId;
				itoa(nRecordId, szId.GetBuffer(10), 10);
				szId.ReleaseBuffer();
				CString strImageRef = CString(szLocation) + CString(_T("?")) + CString(_T("GetImage?")) + szId;
				CString strListRef = CString(szLocation) + CString(_T("?")) + CString(_T("GetListFrame"));
				
				CString strOutput;
				CString strResource;
				LoadLongResource(strResource, IDR_DATA);
				strOutput.Format(strResource, strImageRef, ImagesRS.m_image_title, strListRef);
				*pCtxt << strOutput;
			}
			ImagesRS.Close();
		}
		else
			*pCtxt << _T("Couldn't open the record set\r\n");

		db.Close();
	}
	catch (CDBException* pEx)
	{
		*pCtxt << _T("Browser Failed: Couldn't open image data source\r\n");

		TCHAR szError[1024];
		if (pEx->GetErrorMessage(szError, sizeof(szError)))
		{
			*pCtxt << szError;
			*pCtxt << _T("\r\n");
		}
		pEx->Delete();
	}
}

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CISAMExtension, CHttpServer)
	//{{AFX_MSG_MAP(CISAMExtension)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0



///////////////////////////////////////////////////////////////////////
// If your extension will not use MFC, you'll need this code to make
// sure the extension objects can find the resource handle for the
// module.  If you convert your extension to not be dependent on MFC,
// remove the comments arounn the following AfxGetResourceHandle()
// and DllMain() functions, as well as the g_hInstance global.

/****

static HINSTANCE g_hInstance;

HINSTANCE AFXISAPI AfxGetResourceHandle()
{
	return g_hInstance;
}

BOOL WINAPI DllMain(HINSTANCE hInst, ULONG ulReason,
					LPVOID lpReserved)
{
	if (ulReason == DLL_PROCESS_ATTACH)
	{
		g_hInstance = hInst;
	}

	return TRUE;
}

****/

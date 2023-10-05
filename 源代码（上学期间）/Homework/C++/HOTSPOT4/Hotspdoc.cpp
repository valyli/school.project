// hotspdoc.cpp : implementation of the CHotspot4Doc class
//

#include "stdafx.h"
#include "hotspot4.h"
#include "hotspdoc.h"
#include "dibapi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHotspot4Doc

IMPLEMENT_DYNCREATE(CHotspot4Doc, CDocument)

BEGIN_MESSAGE_MAP(CHotspot4Doc, CDocument)
	//{{AFX_MSG_MAP(CHotspot4Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHotspot4Doc construction/destruction

CHotspot4Doc::CHotspot4Doc()
{
	m_hDIB = NULL;
	m_palette = NULL;
	m_regionDefined = FALSE;
	m_mode = NULL;
	m_record.num_points = 0;
	m_bitmapLoaded = FALSE;
	m_region = NULL;
	m_editRecord = 0;
	//Open the hotspot data file.
	CFileStatus status;
	if (CFile::GetStatus(LINKFILENAME, status))
		//File exists - open it.
		m_datafile.Open(LINKFILENAME, CFile::modeReadWrite);
	else
		//File does not exist - create it.
		m_datafile.Open(LINKFILENAME, CFile::modeCreate | CFile::modeReadWrite);
}

CHotspot4Doc::~CHotspot4Doc()
{
	//Clean up memory.
	if (m_hDIB != NULL)
		::GlobalFree((HGLOBAL) m_hDIB);

	if (m_palette != NULL)
		delete m_palette;

	if (m_region != NULL)
		delete m_region;

	//Close the data file.
	m_datafile.Close();
}

BOOL CHotspot4Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

void CHotspot4Doc::InitBitmapData()
{
	//Delete any existing palette.
	if (m_palette != NULL)
		{
		delete m_palette;
		m_palette = NULL;
		}

	//If there is no bitmap loaded, return.
	if (m_hDIB == NULL)
		return;

	//Determine bitmap size.
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) m_hDIB);
	m_DocSize = CSize((int) ::DIBWidth(lpDIB), (int) ::DIBHeight(lpDIB));
	::GlobalUnlock((HGLOBAL) m_hDIB);

	//Get the bitmap's palette.
	m_palette = new CPalette;
	if (m_palette == NULL)		//Low on memory!
		{
		::GlobalFree((HGLOBAL) m_hDIB);
		m_hDIB = NULL;
		return;
		}

	if (::CreateDIBPalette(m_hDIB, m_palette) == NULL)
		{
		//DIB may not have a palette.
		delete m_palette;
		m_palette = NULL;
		}
}

/////////////////////////////////////////////////////////////////////////////
// CHotspot4Doc serialization

void CHotspot4Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CHotspot4Doc diagnostics

#ifdef _DEBUG
void CHotspot4Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHotspot4Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHotspot4Doc commands

BOOL CHotspot4Doc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	CFile file;
	CFileException fe;
	if (!file.Open(lpszPathName, CFile::modeRead | CFile::shareDenyWrite, &fe))
		{
		ReportSaveLoadException(lpszPathName, &fe, FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
		return FALSE;
		}

	DeleteContents();
	BeginWaitCursor();

	TRY
		{
		m_hDIB = ::ReadDIBFile(file);
		}
	CATCH (CFileException, eLoad)
		{
		file.Abort();
		EndWaitCursor();
		ReportSaveLoadException(lpszPathName, eLoad, FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
		m_hDIB= NULL;
		return FALSE;
		}
	END_CATCH;

	InitBitmapData();
	EndWaitCursor();

	if (m_hDIB == NULL)
		{
		CString strMsg;
		strMsg = "Cannot load bitmap";
		MessageBox(NULL, strMsg, NULL, MB_ICONINFORMATION | MB_OK);
		return FALSE;
		}

	SetPathName(lpszPathName);
	SetModifiedFlag(FALSE);
	m_record.num_points = 0;
	m_mode = NULL;
	m_regionDefined = FALSE;
	m_bitmapLoaded = TRUE;
	m_drawing = FALSE;
	BlankCurrentHS();
	return TRUE;
}

void CHotspot4Doc::SaveHotspot(void)
{
	//Saves the current hot spot record to disk. If the member
	//variable m_editRecord is 0, uses the first free slot in the file.
	//Otherwise uses the slot specified by m_editRecord.
	
	strcpy(m_record.image, GetTitle());

	if (m_editRecord == 0)
		{
		//Look for an empty record, which will have
		//a blank image field.
		char buf[8];
		long fileLength = m_datafile.SeekToEnd();
		m_datafile.SeekToBegin();
		for (long pos = 0; pos < fileLength; pos += sizeof(HotSpotRecord))
			{
			m_datafile.Read(buf, 8);
			if (strlen(buf) == 0)	//Found an empty record.
				{
				//Go back to start of record and write data.
				m_datafile.Seek(pos, CFile::begin);
				m_datafile.Write(&m_record, sizeof(HotSpotRecord));
				BlankCurrentHS();
				m_datafile.Flush();
				return;
				}
			}
		//We reach here only if no empty records were found.
		//Write data at end of file.
		m_datafile.SeekToEnd();
		m_datafile.Write(&m_record, sizeof(HotSpotRecord));
		}
	else		//Writing an edited record to an existing record position.
		{
		m_datafile.Seek(m_editRecord * sizeof(HotSpotRecord), CFile::begin);
		m_datafile.Write(&m_record, sizeof(HotSpotRecord));
		m_editRecord = 0;
		}
	BlankCurrentHS();
	m_mode = NULL;
	m_datafile.Flush();
}

void CHotspot4Doc::BlankCurrentHS(void)
{
	//Blanks the current hot spot record.
	m_record.num_points = 0;
	m_regionDefined = FALSE;
	strcpy (m_record.image, "");
	strcpy (m_record.target, "");
}


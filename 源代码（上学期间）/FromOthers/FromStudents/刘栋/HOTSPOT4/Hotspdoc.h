// hotspdoc.h : interface of the CHotspot4Doc class
//
/////////////////////////////////////////////////////////////////////////////

//Maximum number of polygon vertices.
#define MAX_POINTS 100

#include "dibapi.h"

class CHotspot4Doc : public CDocument
{
protected: // create from serialization only
	CHotspot4Doc();
	DECLARE_DYNCREATE(CHotspot4Doc)

// Attributes
public:

// Operations
public:
	HDIB GetHDIB() const {return m_hDIB;}
	CPalette* GetDIBPalette() const {return m_palette;}
	CSize* GetDocSize() {return &m_DocSize;}
	void InitBitmapData(void);
	void SaveHotspot(void);
	void 	BlankCurrentHS(void);
	CFile m_datafile;
	HDIB m_hDIB;
	CPalette* m_palette;
	CSize m_DocSize;
	CRgn* m_region;			//Current hotspot region.
	HotSpotRecord m_record;	//Current hotspot record.
	BOOL m_regionDefined;	//TRUE if a hot spot is defined.
	int m_mode;				//Set to TEST if testing, DEFINE if defining,
							//NULL otherwise.
	BOOL m_drawing;			//TRUE if drawing a polygon.
	BOOL m_bitmapLoaded;	//TRUE if a bitmap is loaded.
	int m_editRecord;		//File record number of hotspot beijg edited,
							//or 0 if record not being edited.
	int m_recordNum[128];	//Holds record numbers of hotspot
							//records read in for editing. We
							//assume no image will have more than
							//128 defined hotspots.

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHotspot4Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHotspot4Doc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHotspot4Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

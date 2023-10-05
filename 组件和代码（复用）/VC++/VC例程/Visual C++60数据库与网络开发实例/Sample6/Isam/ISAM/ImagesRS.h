#if !defined(AFX_IMAGESRS_H__75D383BF_046A_11D2_8A44_0000E81D3D27__INCLUDED_)
#define AFX_IMAGESRS_H__75D383BF_046A_11D2_8A44_0000E81D3D27__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ImagesRS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImagesRS recordset

class CImagesRS : public CRecordset
{
public:
	CImagesRS(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CImagesRS)

// Field/Param Data
	//{{AFX_FIELD(CImagesRS, CRecordset)
	CString	m_image_filename;
	CString	m_image_title;
	long	m_image_id;
	//}}AFX_FIELD

	long	m_image_id_param;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImagesRS)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGESRS_H__75D383BF_046A_11D2_8A44_0000E81D3D27__INCLUDED_)

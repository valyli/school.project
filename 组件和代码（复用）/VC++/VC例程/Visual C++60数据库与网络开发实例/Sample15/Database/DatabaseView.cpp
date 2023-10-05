// DatabaseView.cpp : implementation of the CDatabaseView class
//

#include "stdafx.h"
#include "Database.h"

#include "DatabaseDoc.h"
#include "DatabaseView.h"

#include "DialogData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDatabaseView

IMPLEMENT_DYNCREATE(CDatabaseView, CFormView)

BEGIN_MESSAGE_MAP(CDatabaseView, CFormView)
	//{{AFX_MSG_MAP(CDatabaseView)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnButtonFind)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseView construction/destruction

CDatabaseView::CDatabaseView()
	: CFormView(CDatabaseView::IDD)
{
	//{{AFX_DATA_INIT(CDatabaseView)
	m_ssn = 0.0;
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CDatabaseView::~CDatabaseView()
{
}

void CDatabaseView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatabaseView)
	DDX_Text(pDX, IDC_EDIT_SSN, m_ssn);
	//}}AFX_DATA_MAP
}

BOOL CDatabaseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDatabaseView diagnostics

#ifdef _DEBUG
void CDatabaseView::AssertValid() const
{
	CFormView::AssertValid();
}

void CDatabaseView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CDatabaseDoc* CDatabaseView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDatabaseDoc)));
	return (CDatabaseDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDatabaseView message handlers

void CDatabaseView::OnButtonFind() 
{
	CDatabaseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// If the database file has been opened view the data
	if ( pDoc->IsFileOpen() )
	{
		// record ssn user entered
		UpdateData(TRUE);

		// create the data dialog object
		CDialogData dlg;
		ASSERT(&dlg != NULL);

		// set the ptr to the open database set
		dlg.m_pSet = pDoc->GetRecSet();

		// create search string
		dlg.m_pSet->m_strFilter.Format("[SSN] = %9.0f", m_ssn);

		// requery the database
		dlg.m_pSet->Requery();

		// allow editing of database fields
		dlg.m_pSet->Edit();

		// if user edited data, update the database
		if (dlg.DoModal() == IDOK)
			dlg.m_pSet->Update();
	}
	else
		AfxMessageBox("Please open the database file first",
			MB_OK | MB_ICONEXCLAMATION);
}

void CDatabaseView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	
}

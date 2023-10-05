// Example5FView.cpp : implementation of the CExample5FView class
//

#include "stdafx.h"
#include "Example5F.h"

#include "Example5FDoc.h"
#include "Example5FView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExample5FView

IMPLEMENT_DYNCREATE(CExample5FView, CView)

BEGIN_MESSAGE_MAP(CExample5FView, CView)
	//{{AFX_MSG_MAP(CExample5FView)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExample5FView construction/destruction

CExample5FView::CExample5FView()
{
	// TODO: add construction code here
	m_pMci=new Cmci;
}

CExample5FView::~CExample5FView()
{
}

BOOL CExample5FView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CExample5FView drawing

void CExample5FView::OnDraw(CDC* pDC)
{
	CExample5FDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CExample5FView printing

BOOL CExample5FView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CExample5FView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CExample5FView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CExample5FView diagnostics

#ifdef _DEBUG
void CExample5FView::AssertValid() const
{
	CView::AssertValid();
}

void CExample5FView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExample5FDoc* CExample5FView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExample5FDoc)));
	return (CExample5FDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExample5FView message handlers

void CExample5FView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CView::OnPaint() for painting messages
}

int CExample5FView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	if(m_pMci->Create(NULL,WS_BORDER|WS_CHILD,CRect(0,0,300,50),this,IDC_MMCONTROL1,NULL,FALSE))
	{
		m_pMci->ShowWindow(SW_SHOWNORMAL);

		
		m_pMci->SetCommand("close");
		m_pMci->SetNotify(FALSE);

		m_pMci->SetWait(TRUE);
		m_pMci->SetShareable(FALSE);

		m_pMci->SetDeviceType("waveaudio");
		m_pMci->SetFileName("TADA.WAV");
		
		m_pMci->SetCommand("open");
		m_pMci->SetPlayEnabled(true);
		m_pMci->SetCommand("play");
	}
	else
		AfxMessageBox("Can not create!",NULL,MB_OK);
	return 0;
}

void CExample5FView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CString str,strExt;
	CString sFilter="Multimedia files(*.*)|*.*||";
	CFileDialog m_Dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,(LPCTSTR)sFilter,NULL);
	m_Dlg.DoModal();

	str=m_Dlg.GetPathName();
	strExt=m_Dlg.GetFileExt();

	m_pMci->SetCommand("close");
	m_pMci->SetNotify(FALSE);

	m_pMci->SetWait(TRUE);
	m_pMci->SetShareable(FALSE);
	m_pMci->SetFileName((LPCTSTR)str);

	m_pMci->SetDeviceType("MPEGVideo");

	if((strExt=="avi")||(strExt=="AVI"))
		m_pMci->SetDeviceType("AVIVideo");

	if((strExt=="wav")||(strExt=="WAV"))
		m_pMci->SetDeviceType("waveaudio");

	if((strExt=="cda")||(strExt=="CDA"))
		m_pMci->SetDeviceType("CDAudio");

	m_pMci->SetCommand("open");
	m_pMci->SetPlayEnabled(true);
	m_pMci->SetNotify(TRUE);
	m_pMci->SetFrom(0);
	m_pMci->SetTo(10);
	m_pMci->SetWait(FALSE);
	m_pMci->SetCommand("play");

	CView::OnLButtonDown(nFlags, point);
}

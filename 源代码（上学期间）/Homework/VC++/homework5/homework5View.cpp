// homework5View.cpp : implementation of the CHomework5View class
//

#include "stdafx.h"
#include "homework5.h"

#include "homework5Doc.h"
#include "homework5View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHomework5View

IMPLEMENT_DYNCREATE(CHomework5View, CView)

BEGIN_MESSAGE_MAP(CHomework5View, CView)
	//{{AFX_MSG_MAP(CHomework5View)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHomework5View construction/destruction

CHomework5View::CHomework5View()
{
	m_isdraw = FALSE;
}

CHomework5View::~CHomework5View()
{
}

BOOL CHomework5View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CHomework5View drawing

void CHomework5View::OnDraw(CDC* pDC)
{
	CHomework5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(pDoc->m_count > 0)
		DrawResult(pDoc->m_apt, pDoc->m_count);

}

/////////////////////////////////////////////////////////////////////////////
// CHomework5View printing

BOOL CHomework5View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CHomework5View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CHomework5View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CHomework5View diagnostics

#ifdef _DEBUG
void CHomework5View::AssertValid() const
{
	CView::AssertValid();
}

void CHomework5View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHomework5Doc* CHomework5View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHomework5Doc)));
	return (CHomework5Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHomework5View message handlers

void CHomework5View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// Get the pointer to document
	CHomework5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// Capture the mouse, so no other application can grab
	// it if the mouse leaves the window area.
//	m_isdraw = TRUE;
	//modify TRUE
	pDoc->SetModifiedFlag(TRUE);
	//first click in program
	if(pDoc->m_count == 0 && m_isdraw == FALSE)//pDoc->m_apt == 0)
	{
		pDoc->m_apt = (PointQueue*)malloc(sizeof(PointQueue));
		pDoc->m_apt->apt = (POINT*)malloc(sizeof(POINT));
		pDoc->m_apt->count = 0;
		pDoc->m_count = 1;
		if(pDoc->m_apt == 0 || pDoc->m_apt->apt == 0)
			MessageBox("Alloc is wrong(1)");
		m_isdraw = TRUE;
	}
	//draw new bezier
	else if(pDoc->m_count > 0 && m_isdraw == FALSE)
	{
		pDoc->m_apt = (PointQueue*)realloc(pDoc->m_apt, (pDoc->m_count + 1) * sizeof(PointQueue));
		pDoc->m_apt[pDoc->m_count].apt = (POINT*)malloc(sizeof(POINT));
		pDoc->m_apt[pDoc->m_count].count = 0;
		pDoc->m_count++;
		if(pDoc->m_apt == 0 || pDoc->m_apt[pDoc->m_count - 1].apt == 0)////////////????different in debug and release
			MessageBox("Alloc is wrong(2)");
		m_isdraw = TRUE;
	}
	else if(m_isdraw == TRUE)
	{
		pDoc->m_apt[pDoc->m_count - 1].apt
			= (POINT*)realloc(pDoc->m_apt[pDoc->m_count - 1].apt,
			(pDoc->m_apt[pDoc->m_count - 1].count + 1) * sizeof(POINT));
		if(pDoc->m_apt[pDoc->m_count - 1].apt == 0)
			MessageBox("Re. Alloc is wrong");
	}
	pDoc->m_apt[pDoc->m_count - 1].count++;
	pDoc->m_apt[pDoc->m_count - 1].apt[pDoc->m_apt[pDoc->m_count - 1].count - 1] = point;
	m_lastPoint = point;
	Drawing(pDoc->m_apt, pDoc->m_count);

	CView::OnLButtonDown(nFlags, point);
}

void CHomework5View::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnLButtonUp(nFlags, point);
}

void CHomework5View::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(m_isdraw == TRUE)
	{
		CHomework5Doc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		CDC* pDC = this->GetWindowDC();
		CPen  *pOldPen, pPen;
		COLORREF color= RGB(0, 0, 255);
		pPen.CreatePen(PS_DOT, 1, color);
		pOldPen = pDC->SelectObject(&pPen);
		// Set new drawing mode
		pDC->SetROP2(R2_XORPEN);
		// Erase previous line
		pDC->MoveTo(pDoc->m_apt[pDoc->m_count-1].apt[pDoc->m_apt[pDoc->m_count-1].count - 1]);
		pDC->LineTo(m_lastPoint);
		// Draw current line
		m_lastPoint = point;
		pDC->MoveTo(pDoc->m_apt[pDoc->m_count-1].apt[pDoc->m_apt[pDoc->m_count-1].count - 1]);
		pDC->LineTo(m_lastPoint);
		// Restore the original pen and brush in device context
		pDC->SelectObject(pOldPen);
	}
	CView::OnMouseMove(nFlags, point);
}

void CHomework5View::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CHomework5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(m_isdraw == FALSE || pDoc->m_apt[pDoc->m_count-1].count%3 != 1)
		return;
	else
		m_isdraw = FALSE;
	Invalidate();

	CView::OnLButtonDblClk(nFlags, point);
}

BOOL CHomework5View::DestroyWindow() 
{
	CHomework5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	for(int i = 0; i < pDoc->m_count; i++)
	{
		delete[] pDoc->m_apt[i].apt;
	}
	delete[] pDoc->m_apt;

	return CView::DestroyWindow();
}

void CHomework5View::Drawing(PointQueue *m_apt, int m_count)
{
	CDC* pDC = this->GetWindowDC();
	CPen  *pOldPen, pPenLine, pPenBizer;
	COLORREF color = RGB(0, 0, 255);
	pPenLine.CreatePen(PS_DOT, 1, color);
	color = RGB(255, 0, 0);
	pPenBizer.CreatePen(PS_SOLID, 1, color);
	pOldPen = pDC->SelectObject(&pPenLine);
	pDC->SetROP2(R2_COPYPEN);
	//move to first point
	pDC->MoveTo(m_apt[m_count - 1].apt[0]);
	pDC->SelectObject(&pPenLine);
	for(int i = 0; i < m_apt[m_count-1].count; i++)
	{
		pDC->LineTo(m_apt[m_count-1].apt[i]);
		pDC->Ellipse(m_apt[m_count-1].apt[i].x - 2, m_apt[m_count-1].apt[i].y - 2,
					m_apt[m_count-1].apt[i].x + 2, m_apt[m_count-1].apt[i].y + 2);
	}
	pDC->SelectObject(&pPenBizer);
	pDC->PolyBezier(m_apt[m_count-1].apt, m_apt[m_count-1].count);
	pDC->SelectObject(pOldPen);
}

void CHomework5View::DrawResult(PointQueue *m_apt, int m_count)
{
	CDC* pDC = this->GetWindowDC();
	if(m_apt[0].count > 0)
	{
//		m_Drawing[0] = m_apt[m_count-1];
		CPen  *pOldPen, pPenBizer;
		COLORREF color = RGB(0, 0, 255);
		pPenBizer.CreatePen(PS_SOLID, 1, color);
		pOldPen = pDC->SelectObject(&pPenBizer);
		for(int j = 0; j < m_count; j++)
		{
			POINT* m_Drawing = new POINT[m_apt[j].count + 2];
			for(int i = 0; i < m_apt[j].count; i++)
				m_Drawing[i] = m_apt[j].apt[i];
			m_Drawing[m_apt[j].count] = m_apt[j].apt[0];
			m_Drawing[m_apt[j].count + 1] = m_apt[j].apt[0];
			pDC->MoveTo(m_apt[j].apt[0]);
			pDC->PolyBezierTo(m_Drawing, m_apt[j].count+2);
			delete[] m_Drawing;
		}
		pDC->SelectObject(pOldPen);
	}
}

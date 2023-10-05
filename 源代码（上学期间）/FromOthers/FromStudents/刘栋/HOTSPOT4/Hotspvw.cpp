// hotspvw.cpp : implementation of the CHotspot4View class
//

#include "stdafx.h"
#include "hotspot4.h"
#include "hotspdoc.h"
#include "hotspvw.h"
#include "editlink.h"
#include "linktext.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHotspot4View

IMPLEMENT_DYNCREATE(CHotspot4View, CView)

BEGIN_MESSAGE_MAP(CHotspot4View, CView)
	//{{AFX_MSG_MAP(CHotspot4View)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_MODE_DEFINE, OnModeDefine)
	ON_COMMAND(ID_MODE_TEST, OnModeTest)
	ON_UPDATE_COMMAND_UI(ID_MODE_TEST, OnUpdateModeTest)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEWHOTSPOT, OnUpdateFileNewhotspot)
	ON_COMMAND(ID_FILE_NEWHOTSPOT, OnFileNewhotspot)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVEHOTSPOT, OnUpdateFileSavehotspot)
	ON_COMMAND(ID_FILE_SAVEHOTSPOT, OnFileSavehotspot)
	ON_COMMAND(ID_EDIT_EDITHOTSPOT, OnEditEdithotspot)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHotspot4View construction/destruction

CHotspot4View::CHotspot4View()
{
	// TODO: add construction code here

}

CHotspot4View::~CHotspot4View()
{
}

/////////////////////////////////////////////////////////////////////////////
// CHotspot4View drawing

void CHotspot4View::OnDraw(CDC* pDC)
{
	CHotspot4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	HDIB hDIB = pDoc->GetHDIB();
	if (hDIB == NULL)
		return;

	//Display the bitmap.
	CRect rectDIB(0,0,pDoc->GetDocSize()->cx,pDoc->GetDocSize()->cy);
	pDC->SelectPalette(pDoc->GetDIBPalette(), FALSE);
	pDC->RealizePalette();
	::PaintDIB(pDC->m_hDC, &rectDIB, hDIB, &rectDIB, pDoc->GetDIBPalette());

	//Draw the polygon.
	OutlineRegion();
}

/////////////////////////////////////////////////////////////////////////////
// CHotspot4View diagnostics

#ifdef _DEBUG
void CHotspot4View::AssertValid() const
{
	CView::AssertValid();
}

void CHotspot4View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHotspot4Doc* CHotspot4View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHotspot4Doc)));
	return (CHotspot4Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHotspot4View message handlers

void CHotspot4View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetCapture();	
}

void CHotspot4View::OnRButtonDown(UINT nFlags, CPoint point) 
{
	SetCapture();	
}

void CHotspot4View::OnMouseMove(UINT nFlags, CPoint point) 
{
	CHotspot4Doc* pDoc = GetDocument();

	//If we are drawing and at least one point has
	//been placed, erase the old line and draw the new.
	if (pDoc->m_drawing && (pDoc->m_record.num_points > 0))
		{
		DrawLine(pDoc->m_record.points[pDoc->m_record.num_points-1], m_oldPoint);
	 	m_oldPoint = point;
		DrawLine(pDoc->m_record.points[pDoc->m_record.num_points-1], m_oldPoint);
		}
}

void CHotspot4View::OnLButtonUp(UINT nFlags, CPoint point) 
{
	ReleaseCapture();
	CHotspot4Doc* pDoc = GetDocument();	

	//If no bitmap is loaded, do nothing.
	if (pDoc->m_bitmapLoaded == FALSE)
		return;

	//If we're defining...
	if (pDoc->m_mode == DEFINE)
		{
		//If we are not already drawing, then
		//we are placing the first point.
		if (pDoc->m_drawing == FALSE)
			if (pDoc->m_record.num_points == 0)
				pDoc->m_drawing = TRUE;
			else
				//Polygon is complete - display message.
				{
				MessageBox("Polygon closed - use Test mode to try it out.");
				return;
				}

		//Add the new point to the point array.
		pDoc->m_record.points[pDoc->m_record.num_points++] = point;
		m_oldPoint = point;

		//If we have filled the point array, complete the
		//polygon and display a message.
		if (pDoc->m_record.num_points == MAX_POINTS)
			{
			pDoc->m_drawing = FALSE;

			//Delete any existing CRgn and create a new one
			if (pDoc->m_region != NULL)
				delete pDoc->m_region;
			pDoc->m_region = new CRgn;
			//Initialize the CRgn object with our points.
			if (!pDoc->m_region->CreatePolygonRgn(pDoc->m_record.points,
											 pDoc->m_record.num_points,
											 0 ))
				{
				MessageBox("Could not create region.");
				return;
				}
			pDoc->m_regionDefined = TRUE;
			
			//Erase the line to the mouse cursor.			
			DrawLine(pDoc->m_record.points[pDoc->m_record.num_points-1], point);
			//Draw the last leg of the polygon.
			DrawLine(pDoc->m_record.points[0], pDoc->m_record.points[pDoc->m_record.num_points-1]);
			MessageBox("Maximum number of points reached - polygon has been completed.");
			}	
		}
	else
		if (pDoc->m_mode == TEST)		//If we're testing...
			{
			//Display "hit" or "miss" message.
			if (pDoc->m_region->PtInRegion(point))
				MessageBox("A hit!");
			else
				MessageBox("A miss!");			
			}
}

void CHotspot4View::OnRButtonUp(UINT nFlags, CPoint point) 
{
	ReleaseCapture();
	
	CHotspot4Doc* pDoc = GetDocument();

	//Respond to right click only if we are drawing and at
	//least 3 points have been placed.
	if ((pDoc->m_drawing == TRUE) && (pDoc->m_record.num_points > 2))
		{
		pDoc->m_drawing = FALSE;
		
		//Delete any existing CRgn and create a new one
		if (pDoc->m_region != NULL)
			delete pDoc->m_region;
		pDoc->m_region = new CRgn;
		//Initialize the CRgn object with our points.
		if (!pDoc->m_region->CreatePolygonRgn(pDoc->m_record.points,
										 pDoc->m_record.num_points,
										 0 ))
			{
			MessageBox("Could not create region.");
			return;
			}
		pDoc->m_regionDefined = TRUE;

		//Draw the last leg of the polygon.
		DrawLine(pDoc->m_record.points[pDoc->m_record.num_points-1], point);
		DrawLine(pDoc->m_record.points[0], pDoc->m_record.points[pDoc->m_record.num_points-1]);
		}	
	else
		{
		ReleaseCapture();
		MessageBox("You must define at least 3 points before completing the polygon.");
		SetCapture();
		}
}

void CHotspot4View::DrawLine(CPoint point1, CPoint point2)
{
	//Draws a line in "invert" mode between
	//the two specified points.

 	CClientDC dc(this);
	m_oldMode = dc.SetROP2(R2_NOT);
	m_oldPen = (CPen*) dc.SelectStockObject(BLACK_PEN);
	dc.MoveTo(point1);
	dc.LineTo(point2);
	//Reselect original pen and mode.
	dc.SelectObject(m_oldPen);
	dc.SetROP2(m_oldMode);
}

void CHotspot4View::OutlineRegion(void)
{
	//Draws the entire polygon.
	CHotspot4Doc* pDoc = GetDocument();
	for (int i = 0; i < pDoc->m_record.num_points-1; i++)
		DrawLine(pDoc->m_record.points[i], pDoc->m_record.points[i+1]);
	DrawLine( pDoc->m_record.points[i], pDoc->m_record.points[0]);
}

void CHotspot4View::OnModeDefine() 
{
	CHotspot4Doc* pDoc = GetDocument();

	//If we are returning from testing, redisplay the polygon.
	if (pDoc->m_mode == TEST)
		OutlineRegion();
	pDoc->m_mode = DEFINE;
}

void CHotspot4View::OnModeTest() 
{
	CHotspot4Doc* pDoc = GetDocument();

	//Hide the polygon.
	if (pDoc->m_mode == DEFINE)
		OutlineRegion();
	pDoc->m_mode = TEST;
}

void CHotspot4View::OnFileNewhotspot() 
{
	CHotspot4Doc* pDoc = GetDocument();	
	pDoc->m_drawing = FALSE;
	pDoc->m_mode = DEFINE;
	pDoc->m_regionDefined = FALSE;
	pDoc->BlankCurrentHS();
	InvalidateRect(NULL, FALSE);
}

void CHotspot4View::OnFileSavehotspot() 
{
	CHotspot4Doc* pDoc = GetDocument();
	
	//Display the dialog box for entry 
	//of the target text.
	CLinkTextDlg dlg;
	dlg.m_linkText = pDoc->m_record.target;
	int ret = dlg.DoModal();

	//If user selected Cancel, return.
	if (ret != IDOK)
		return;

	//Erase the hotspot outline.
	OutlineRegion();

	//Save the hot spot
	strcpy(pDoc->m_record.target, dlg.m_linkText);
	pDoc->SaveHotspot();
}

void CHotspot4View::OnEditEdithotspot() 
{
	//Create the dialog box and display it.
	CEditLinkDlg dlg;
	int ret;
	if ((ret = dlg.DoModal()) == IDCANCEL)
		return;

	//If user did not select a hotspot to edit, or
	//did not select the Edit button, return.
	if (ret != IDOK || dlg.m_selectedLink == -1)
		{
		MessageBox("Nothing Selected");
		return;
		}

	//We reach here only if user selected a valid
	//record to edit.
	//Get the record to edit.
	CHotspot4Doc* pDoc = GetDocument();
	pDoc->m_editRecord = pDoc->m_recordNum[dlg.m_selectedLink];
	long pos = sizeof(HotSpotRecord) * pDoc->m_editRecord;
	pDoc->m_datafile.Seek(pos, CFile::begin);
	pDoc->m_datafile.Read(&pDoc->m_record, sizeof(HotSpotRecord));

	//Outline it on the bitmap.
	OutlineRegion();

	//Create a region for the hotspot.
	//Delete any existing CRgn and create a new one
	if (pDoc->m_region != NULL)
		delete pDoc->m_region;
	pDoc->m_region = new CRgn;
	if (!pDoc->m_region->CreatePolygonRgn(pDoc->m_record.points,
									 pDoc->m_record.num_points,
									 0 ))
			{
			MessageBox("Could not create region.");
			pDoc->m_regionDefined = FALSE;
			return;
			}
	pDoc->m_regionDefined = TRUE;
	pDoc->m_mode = DEFINE;
}

void CHotspot4View::OnUpdateFileNewhotspot(CCmdUI* pCmdUI) 
{
	CHotspot4Doc* pDoc = GetDocument();
	pCmdUI->Enable(pDoc->m_bitmapLoaded && !pDoc->m_drawing);	
}

void CHotspot4View::OnUpdateFileSavehotspot(CCmdUI* pCmdUI) 
{
	CHotspot4Doc* pDoc = GetDocument();
	pCmdUI->Enable(pDoc->m_regionDefined);	
}

void CHotspot4View::OnUpdateModeTest(CCmdUI* pCmdUI) 
{
	CHotspot4Doc* pDoc = GetDocument();
	pCmdUI->Enable(pDoc->m_regionDefined);		
}


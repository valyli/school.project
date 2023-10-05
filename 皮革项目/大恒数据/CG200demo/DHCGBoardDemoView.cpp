// DHCGBoardDemoView.cpp : implementation of the CDHCGBoardDemoView class
//

#include "stdafx.h"
#include "DHCGBoardDemo.h"
#include "cgparasetup.h"
#include "DHCGBoardDemoDoc.h"
#include "DHCGBoardDemoView.h"
#include "averageNumdlg.h"
#include "myImagePropertySheet.H"
//	#include "dlgmak.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDHCGBoardDemoView

IMPLEMENT_DYNCREATE(CDHCGBoardDemoView, CScrollView)

BEGIN_MESSAGE_MAP(CDHCGBoardDemoView, CScrollView)
	//{{AFX_MSG_MAP(CDHCGBoardDemoView)
	ON_WM_ERASEBKGND()
	ON_WM_MOVE()
	ON_WM_SIZE()
	ON_COMMAND(ID_CGCARD_ATUOFORMAT, OnCgcardAtuoformat)
	ON_COMMAND(ID_CGCARD_CG210PARA, OnCgcardCg210para)
	ON_COMMAND(ID_CGCARD_MEM, OnCgcardMem)
	ON_COMMAND(ID_CGCARD_MODE_DIRECTX, OnCgcardModeDirectx)
	ON_COMMAND(ID_CGCARD_MODE_SCREEN, OnCgcardModeScreen)
	ON_COMMAND(ID_CGCARD_PARAM, OnCgcardParam)
	ON_COMMAND(ID_CGCARD_SNAP, OnCgcardSnap)
	ON_COMMAND(ID_CGBOARDPLAY, OnCgboardplay)
	ON_UPDATE_COMMAND_UI(ID_CGCARD_CG210PARA, OnUpdateCgcardCg210para)
	ON_UPDATE_COMMAND_UI(ID_CGCARD_MODE_DIRECTX, OnUpdateCgcardModeDirectx)
	ON_UPDATE_COMMAND_UI(ID_CGCARD_MODE_SCREEN, OnUpdateCgcardModeScreen)
	ON_UPDATE_COMMAND_UI(ID_CGBOARDPLAY, OnUpdateCgboardplay)
	ON_COMMAND(ID_CGBOARDSTOP, OnCgboardstop)
	ON_UPDATE_COMMAND_UI(ID_CGBOARDSTOP, OnUpdateCgboardstop)
	ON_COMMAND(ID_CGBOARD_MASK, OnCgboardMask)
	ON_UPDATE_COMMAND_UI(ID_CGBOARD_MASK, OnUpdateCgboardMask)
	ON_COMMAND(ID_CGBOARD_CAPTUREMEM, OnCgboardCapturemem)
	ON_UPDATE_COMMAND_UI(ID_CGBOARD_CAPTUREMEM, OnUpdateCgboardCapturemem)
	ON_UPDATE_COMMAND_UI(ID_CGCARD_ATUOFORMAT, OnUpdateCgcardAtuoformat)
	ON_UPDATE_COMMAND_UI(ID_CGCARD_MEM, OnUpdateCgcardMem)
	ON_UPDATE_COMMAND_UI(ID_CGCARD_PARAM, OnUpdateCgcardParam)
	ON_UPDATE_COMMAND_UI(ID_CGCARD_SNAP, OnUpdateCgcardSnap)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDHCGBoardDemoView construction/destruction

CDHCGBoardDemoView::CDHCGBoardDemoView()
{
	// TODO: add construction code here
	//附初值
	m_bFreeze=true;
	m_bDDraw=false;
	m_bMask=true;
	//	m_bPrePrint=false;
}

CDHCGBoardDemoView::~CDHCGBoardDemoView()
{
	//	delete pScrnBMP;
	//	delete pScrnImageMemDC;
	//结束图象卡活动状态，保存设置参数，退出
	if(!m_bFreeze)
	{
		if(!m_bDDraw)
			cgBoard.SetCgBoardLiveOrFreeze(false);
		else
			cgBoard.DDrawSample(false);
	}
	cgBoard.SetInputVideoRect(InputVideoRect);
	cgBoard.CloseCgBoard();
}
//初始化图象卡为写屏模式
//读取历史输入窗口
BOOL CDHCGBoardDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	m_bInitCGboard=false;
	if(!cgBoard.InitialCgBoard(ID_DHCG200,false,NULL))
	{
		AfxMessageBox("图象卡初始失败!",MB_OK|MB_ICONWARNING,NULL);
		
			//	::SendMessage(WM_CLOSE);
			//	return false;
		m_bInitCGboard=false;
			
	}
	else
		m_bInitCGboard=true;
	InitInputVideoRect();
	
	return CScrollView::PreCreateWindow(cs);

}

/////////////////////////////////////////////////////////////////////////////
// CDHCGBoardDemoView drawing
//显示图象
void CDHCGBoardDemoView::OnDraw(CDC* pDC)
{
	CDHCGBoardDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	if(!pDC->IsPrinting())
	{
		if(m_bFreeze)
		{
			if(pDoc->hdib!=NULL)
			{
				CRect lprect;
				//	GetClientRect(lprect);
				CSize size;
				DIBSize(pDoc->hdib,&size);
				SetScrollSizes(MM_TEXT, size);
				lprect.SetRectEmpty();
				lprect.right=size.cx;
				lprect.bottom=size.cy;
				PaintDIB(pDC->GetSafeHdc(),lprect,pDoc->hdib,lprect,NULL);
			}
		}
		else
		{
			if(m_bMask)
			{
				CFont	font;
				if(cgBoard.m_CVideoCGPara.nInterlace)//2000 2 5 桢和场
					font.CreateFont(17,       // nHeight
					0,        // nWidth
					0,        // nEscapement
					0,        // nOrientation
					FW_BOLD,// nWeight   
					FALSE,    // bItalic
					FALSE,    // bUnderline
					0,        // cStrikeOut
					ANSI_CHARSET, // nCharSet
					OUT_DEFAULT_PRECIS,// nOutPrecision
					CLIP_DEFAULT_PRECIS,// nClipPrecision
					DEFAULT_QUALITY,// nQuality
					DEFAULT_PITCH | FF_SWISS,// nPitchAndFamily
					"Times New Roman");// lpszFacena
				else
					font.CreateFont(35,       // nHeight
					0,        // nWidth
					0,        // nEscapement
					0,        // nOrientation
					FW_BOLD,// nWeight   
					FALSE,    // bItalic
					FALSE,    // bUnderline
					0,        // cStrikeOut
					ANSI_CHARSET, // nCharSet
					OUT_DEFAULT_PRECIS,// nOutPrecision
					CLIP_DEFAULT_PRECIS,// nClipPrecision
					DEFAULT_QUALITY,// nQuality
					DEFAULT_PITCH | FF_SWISS,// nPitchAndFamily
					"Times New Roman");// lpszFacena
				CFont* poldFont=pDC->SelectObject(&font);
				int leftmove=GetScrollPos(SB_HORZ);
				int topmove=GetScrollPos(SB_VERT);
				pDC->SetTextColor(RGB(0,255,0));
				if(cgBoard.m_CVideoCGPara.nInterlace)
					pDC->TextOut(40+leftmove,25+topmove/2,"大恒图象卡演示");
				else
					pDC->TextOut(40+leftmove,50+topmove,"大恒图象卡演示");
				pDC->SelectObject(poldFont);
			}
		}
	}

	
}


void CDHCGBoardDemoView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	m_bAutoFormat=true;
}

/////////////////////////////////////////////////////////////////////////////
// CDHCGBoardDemoView printing

BOOL CDHCGBoardDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation

	return DoPreparePrinting(pInfo);
}

void CDHCGBoardDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	
}

//DEL void CDHCGBoardDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
//DEL {
//DEL 	// TODO: add cleanup after printing
//DEL 	//	m_bPrePrint=false;
//DEL }

/////////////////////////////////////////////////////////////////////////////
// CDHCGBoardDemoView diagnostics

#ifdef _DEBUG
void CDHCGBoardDemoView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDHCGBoardDemoView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CDHCGBoardDemoDoc* CDHCGBoardDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDHCGBoardDemoDoc)));
	return (CDHCGBoardDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDHCGBoardDemoView message handlers
//设置背景界面
BOOL CDHCGBoardDemoView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CBrush br;
	br.CreateHatchBrush(HS_DIAGCROSS, RGB(0, 37, 0));
	CRect rec;
	GetClientRect(&rec);
	pDC->FillRect(&rec, &br);
	return true;
}

void CDHCGBoardDemoView::OnMove(int x, int y) 
{

	x=x-x%4;
	y=y-y%2;
	CScrollView::OnMove(x, y);
	OnChangeViewSize();
}

void CDHCGBoardDemoView::OnSize(UINT nType, int cx, int cy) 
{
	cx=cx-cx%4;
	cy=cy-cy%2;
	CScrollView::OnSize(nType, cx, cy);
	OnChangeViewSize();
}
//活动图象卡图象
 void CDHCGBoardDemoView::OnCgboardplay() 
 {
 	CDHCGBoardDemoDoc* pDoc = GetDocument();
 		ASSERT_VALID(pDoc);
 	if(m_bFreeze)
 	{
 		if(pDoc->hdib!=NULL)
 			pDoc->FreeDIBHandle();
		pDoc->SetTitle("无标题");
 		pDoc->UpdateAllViews(NULL);
 		if(!m_bDDraw)
 		{
 			OnChangeViewSize();
			CRect rect(45,50,265,80);
			//	cgBoard.GetInputVideoRect(rect);
			//	rect.bottom=rect.top+24;
			//	rect.right=rect.left+24;
			if(m_bAutoFormat)
			{
				cgBoard.DhBoardSetColorSpaceToScreen();
				cgBoard.SetCgBoardLiveOrFreeze(false);
			}
			SetMask(rect,m_bMask);
 			
			cgBoard.SetCgBoardLiveOrFreeze(true);
 		}
 		else
 		{
 			OnChangeViewSize();
			if(m_bAutoFormat)
			{
				cgBoard.DhBoardSetColorSpaceToScreen();
				cgBoard.SetCgBoardLiveOrFreeze(false);
			}
 			cgBoard.DDrawSample(true);
 		}
 			m_bFreeze=false;
	}

 }
 //冻结图象卡图象
void CDHCGBoardDemoView::OnCgboardstop() 
{
	CDHCGBoardDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(!m_bFreeze)
 	{
 		if(!m_bDDraw)
		{
			
			cgBoard.SetCgBoardLiveOrFreeze(FALSE);

			cgBoard.DhBoardEnableOverlay(false);
		}
 		else
 			cgBoard.DDrawSample(false);
 		m_bFreeze=true;
 		
 		if(pDoc->hdib!=NULL)
 			pDoc->FreeDIBHandle();
		//冻结图象后，采一幅图象到内存，作为冻结的图象
 		int avr=cgBoard.GetAverageNum();
 		cgBoard.SetAverageNum(1);
 		CRect rect,rect2;
 		cgBoard.GetInputVideoRect(rect);
		cgBoard.GetVisualVideoRect(rect2);
 		cgBoard.SetInputVideoRect(InputVideoRect);
//		if(cgBoard.m_CVideoCGPara.nColorSpace)
//		{
//			CRect r2;
//			r2.left=InputVideoRect.left;
//			r2.top=InputVideoRect.top;
//			r2.right=InputVideoRect.left+InputVideoRect.Width()*2;
//			r2.bottom=InputVideoRect.top+InputVideoRect.Height()*2;
//			cgBoard.SetVisualVideoRect(r2);
//		}
//		else
			cgBoard.SetVisualVideoRect(InputVideoRect);
 		cgBoard.SetCgBoardLiveOrFreeze(FALSE);
		//2001 2 5 LFL
		DWORD offset=cgBoard.GetPhysicalMemSize();//-1024*1024;
		//	BYTE* pLine=(BYTE*)cgBoard.GetPhysicalMemHandle();
		BYTE* pLine=(BYTE*)cgBoard.GetLinearAdd();
		memset(pLine,0xff,offset);
 		cgBoard.DhBoardCaptureImage(pDoc->hdib);
//		CSize size;
//		DIBSize(pDoc->hdib,&size);
 		cgBoard.SetInputVideoRect(rect);
		cgBoard.SetVisualVideoRect(rect2);
 		cgBoard.SetAverageNum(avr);
 		pDoc->UpdateAllViews(NULL);	
 	}	
}
//调整显示窗口和输入窗口
//当窗口移动，改变大小，从新设定参数后，均须重新调整窗口
//在不同模式下，窗口的调节方法不同
void CDHCGBoardDemoView::OnChangeViewSize()
{
	if(!m_bDDraw)
	{
		CRect VideoRect;
		GetClientRect(&VideoRect);
		MapWindowPoints(NULL,&VideoRect);		
		int leftmove=GetScrollPos(SB_HORZ);
		int topmove=GetScrollPos(SB_VERT);
		CRect rectInput;
		while(leftmove%2)
			++leftmove;
		if(topmove%2)
			++topmove;
		SetScrollPos(SB_HORZ,leftmove,true);
		SetScrollPos(SB_VERT,topmove,true);
		rectInput=InputVideoRect;
		rectInput.left=leftmove+InputVideoRect.left;
		
		rectInput.top=topmove+InputVideoRect.top;
		int moveleft=0;
		int movetop=0;
		if(VideoRect.left<0)
		{
			rectInput.left-=VideoRect.left;
			moveleft-=VideoRect.left;
			VideoRect.left=0;
		}
		if(VideoRect.top<0)
		{
			rectInput.top-=VideoRect.top;
			movetop-=VideoRect.top;
			VideoRect.left=0;
		}
		if( VideoRect.Width() && VideoRect.Height() )
		{
			while(rectInput.left%4)
				--rectInput.left;
			while(rectInput.Width()%4)
				++rectInput.right;	
			if(rectInput.top%2)
				--rectInput.top;
			if(rectInput.Height()%2)
				++rectInput.bottom;
			if(VideoRect.top%2)
				--VideoRect.top;
			while(VideoRect.left%4)
				--VideoRect.left;	
			//	MoveWindow(VideoRect,true);
			if( cgBoard.m_CVideoCGPara.bClip )
			{
				if(rectInput.Width()>VideoRect.Width())
					rectInput.right=VideoRect.Width()+rectInput.left;
				if(rectInput.Height()>VideoRect.Height())
					rectInput.bottom=VideoRect.Height()+rectInput.top;
				VideoRect.right=VideoRect.left+rectInput.Width();
				VideoRect.bottom=VideoRect.top+rectInput.Height();

			}
			HDC pdc=::GetDC(NULL);
			DWORD width=GetDeviceCaps(pdc,HORZRES);
			if((DWORD)VideoRect.right>width)
				VideoRect.right=width;
			DWORD hight=GetDeviceCaps(pdc,VERTRES);
			if((DWORD)VideoRect.bottom>hight)
				VideoRect.bottom=hight;
			::ReleaseDC(NULL,pdc);
			hight-=1;

			if(hight<(DWORD)VideoRect.top)
			{
				cgBoard.SetCgBoardLiveOrFreeze(false);
				return;
			}

			if(VideoRect.Width()==1||VideoRect.Height()==1)
			{
				cgBoard.SetCgBoardLiveOrFreeze(false);
				return;
			}
			
			cgBoard.SetInputVideoRect(rectInput);
			cgBoard.SetVisualVideoRect(VideoRect);//
			cgBoard.SetCgBoardLiveOrFreeze(!m_bFreeze);
			return;
		}
		else
		{
			cgBoard.SetCgBoardLiveOrFreeze(false);
			m_bFreeze=true;
		}
	}
	else
	{
		CRect VideoRect;
		GetClientRect(&VideoRect);	
		int leftmove=GetScrollPos(SB_HORZ);
		int topmove=GetScrollPos(SB_VERT);
		CRect rectInput;
		while(leftmove%4)
			--leftmove;
		while(topmove%2)
			--topmove;
		SetScrollPos(SB_HORZ,0,true);
		SetScrollPos(SB_VERT,topmove,true);
		rectInput=InputVideoRect;
		rectInput.left=0+InputVideoRect.left;
		rectInput.top=topmove+InputVideoRect.top;

		if( VideoRect.Width() && VideoRect.Height() )
		{	
			//	if( cgBoard.m_CVideoCGPara.bClip )
			//	{
				VideoRect.right=rectInput.Width();
				VideoRect.bottom=rectInput.Height();
			//	}
			while(rectInput.Width()%4)
				--rectInput.right;	
			while(VideoRect.Width()%4)
				--VideoRect.right;
			while(rectInput.Height()%2)
				--rectInput.bottom;
			while(VideoRect.Height()%2)
				--VideoRect.bottom;
			if(VideoRect.Width()==1||VideoRect.Height()==1)
			{
				cgBoard.SetCgBoardLiveOrFreeze(false);
				return;
			}
			cgBoard.SetInputVideoRect(rectInput);
			cgBoard.SetVisualVideoRect(VideoRect);//
			cgBoard.SetCgBoardLiveOrFreeze(false);
			cgBoard.DDrawSample(!m_bFreeze);
			return;
			//	CG200SetDispWindow(hcg200, (int)VideoRect.left, (int)VideoRect.top, VideoRect.Width(), VideoRect.Height());
		}
		else
		{
			cgBoard.SetCgBoardLiveOrFreeze(false);
			m_bFreeze=true;
		}
	}

}
//读取屏幕图形到位图句柄
HANDLE CDHCGBoardDemoView::ReadDispWindowToHandle()
{
	HANDLE ret=NULL;

	CDC* pDC=GetDC();
	CRect rect;
	cgBoard.GetVisualVideoRect(rect);//
	InitDIBBuffers(ret,rect.Width(),rect.Height(),24);
	DWORD size=rect.Width()*rect.Height()*3L;
	HANDLE temp=GlobalAlloc(GHND, size);
	BYTE* lpdata=(BYTE *)GlobalLock(temp);
	if(ReadDispWindow(pDC->GetSafeHdc(),0,0 ,rect.Width(),rect.Height(),lpdata))
	{
		if(lpdata!=NULL)
			ScreenBufferToDIB(lpdata,&ret);
	}
	::GlobalUnlock(temp);
	::GlobalFree(temp);
	return ret;
}

BOOL CDHCGBoardDemoView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll) 
{
	if(!m_bFreeze)
	{
		OnChangeViewSize();
		CDHCGBoardDemoDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->UpdateAllViews(NULL);
	}
	return CScrollView::OnScroll(nScrollCode, nPos, bDoScroll);
}
//为InputVideoRect附值，并设置ScaollView的Size
void CDHCGBoardDemoView::InitInputVideoRect()
{
	cgBoard.GetInputVideoRect(InputVideoRect);
	CSize size;
	size.cx=InputVideoRect.Width();//
	size.cy=InputVideoRect.Height();
	SetScrollSizes(MM_TEXT,size);
}
//初始化显示窗口
void CDHCGBoardDemoView::InitVisualVideoRect(bool bToScreen)
{
	
	CRect VideoRect;
	cgBoard.GetVisualVideoRect(VideoRect);
	if(bToScreen)
		MapWindowPoints(NULL,VideoRect);
	else
	{
		CRect rect;
		rect.SetRectEmpty();
		rect.bottom=VideoRect.Height();
		rect.right=VideoRect.Width();
		VideoRect=rect;
	}
	cgBoard.SetVisualVideoRect(VideoRect);
}
//自动适应当前屏幕分辨率
void CDHCGBoardDemoView::OnCgcardAtuoformat() 
{
	if(m_bFreeze)
	{
		if(m_bAutoFormat)
			m_bAutoFormat=false;
		else
			m_bAutoFormat=true;
	}

}
void CDHCGBoardDemoView::OnUpdateCgcardAtuoformat(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(	m_bInitCGboard);//=false

	pCmdUI->SetCheck(m_bAutoFormat);
	
}

//设置CG210专有参数
void CDHCGBoardDemoView::OnCgcardCg210para() 
{
	if(cgBoard.GetCGBoardType())
	{
		CG210AdvaceParaSetup(cgBoard.GetCGBoardHandle(),cgBoard.GetCGBoardType(),
		 cgBoard.m_CVideoCGPara	);
	}
}
//平均内存图形
//平均图形由位图大小和采集的数量决定
void CDHCGBoardDemoView::OnCgcardMem() 
{
	if(m_bFreeze)
	{
		if(cgBoard.m_CVideoCGPara.nInterlace)
		{
			AfxMessageBox("内存平均操作需要在采集桢方式下进行！");
			return;
		}
		CAverageNumDlg* NumDlg;
		NumDlg=new CAverageNumDlg;
		NumDlg->m_avernum=cgBoard.GetAverageNum();
		NumDlg->m_nMaxNum=cgBoard.GetMaxAverageNum();
		if(NumDlg->DoModal()==IDOK)
		{
			DWORD offset=cgBoard.GetPhysicalMemSize();//-1024*1024;
			//	BYTE* pLine=(BYTE*)cgBoard.GetPhysicalMemHandle();
			BYTE* pLine=(BYTE*)cgBoard.GetLinearAdd();
			memset(pLine,0xff,offset);
			cgBoard.SetAverageNum(NumDlg->m_avernum);
			CDHCGBoardDemoDoc* pDoc = GetDocument();
			ASSERT_VALID(pDoc);
			if(pDoc->hdib!=NULL)
				pDoc->FreeDIBHandle();
			cgBoard.DhBoardCaptureImage(pDoc->hdib);
			pDoc->UpdateAllViews(NULL);
		}
		delete NumDlg;
	}
	
}
//初始化为DirectX模式
void CDHCGBoardDemoView::OnCgcardModeDirectx() 
{
	if(!m_bDDraw)
	{
		if(!m_bFreeze)
			cgBoard.SetCgBoardLiveOrFreeze(false);
		m_bFreeze=true;
		HWND hwnd;//=::GetActiveWindow();
		CDC* pDC=GetDC();
		CWnd* wnd=pDC->GetWindow();
		hwnd=wnd->GetSafeHwnd();
		if(!cgBoard.InitialCgBoard(ID_DHCG200,true,hwnd))
		{
			AfxMessageBox("图象卡初始失败!",MB_OK|MB_ICONWARNING,NULL);//==IDOK)
			m_bInitCGboard=false;
				
		}
		else
			m_bInitCGboard=true;
		InitVisualVideoRect(false);

		m_bDDraw=true;
	}
}
//初始化为写屏模式
void CDHCGBoardDemoView::OnCgcardModeScreen() 
{
	if(m_bDDraw)
	{
		if(!m_bFreeze)
			cgBoard.DDrawSample(false);
		m_bFreeze=true;
		//	cgBoard.CloseCgBoard();
		if(!cgBoard.InitialCgBoard(ID_DHCG200,false,NULL))
		{
			AfxMessageBox("图象卡初始失败!",MB_OK|MB_ICONWARNING,NULL);//==IDOK)
			//	SendMessage(WM_CLOSE);
			m_bInitCGboard=false;
				
		}
		else
			m_bInitCGboard=true;
		//	InitInputVideoRect();
		InitVisualVideoRect(true);
		m_bDDraw=false;
	}	
}
//调整图象卡基本参数
void CDHCGBoardDemoView::OnCgcardParam() 
{
	CRect rect;
	cgBoard.GetVisualVideoRect(rect);
	if(m_bDDraw)
		InitVisualVideoRect(true);
	cgBoard.SetInputVideoRect(InputVideoRect);
	CMyImagePropertySheet m_dlg;
	//	m_dlg=new CMyImagePropertySheet;//
	m_dlg.m_Page1->hcg=cgBoard.GetCGBoardHandle();
	m_dlg.m_Page2->hcg=cgBoard.GetCGBoardHandle();
	m_dlg.m_Page3->hcg=cgBoard.GetCGBoardHandle();
	m_dlg.m_Page4->hcg=cgBoard.GetCGBoardHandle();
	m_dlg.m_Page5->hcg=cgBoard.GetCGBoardHandle();//
	//
	m_dlg.m_Page1->CGoption=cgBoard.GetCGBoardType();
	m_dlg.m_Page2->CGoption=cgBoard.GetCGBoardType();
	m_dlg.m_Page3->CGoption=cgBoard.GetCGBoardType();
	m_dlg.m_Page4->CGoption=cgBoard.GetCGBoardType();
	m_dlg.m_Page5->CGoption=cgBoard.GetCGBoardType();
	
	//
	m_dlg.m_Page1->nADBri=cgBoard.m_CVideoCGPara.nADBri;
	m_dlg.m_Page1->nADCon=cgBoard.m_CVideoCGPara.nADCon;
	m_dlg.m_Page1->nADHue=cgBoard.m_CVideoCGPara.nADHue;
	m_dlg.m_Page1->nADSat=cgBoard.m_CVideoCGPara.nADSat;
	if(cgBoard.GetCGBoardType()==0)
	{
		m_dlg.m_Page1->nADClamp=cgBoard.m_CVideoCGPara.nADClamp;
		m_dlg.m_Page1->nADBand=cgBoard.m_CVideoCGPara.nADBandPass;
	}
	//source
	m_dlg.m_Page2->nADSource=cgBoard.m_CVideoCGPara.nADSource;
	//color
	m_dlg.m_Page3->nADCla=cgBoard.m_CVideoCGPara.nColorSpace;
	//interlace
	m_dlg.m_Page4->nADFld=cgBoard.m_CVideoCGPara.nInterlace;
	m_dlg.m_Page4->m_display=cgBoard.m_CVideoCGPara.bClip;
	m_dlg.m_Page4->m_mode=cgBoard.m_CVideoCGPara.nVideoStand;
	CRect rcInput;
	cgBoard.GetInputVideoRect(rcInput);
	m_dlg.m_Page4->m_rcInput=rcInput;//CRect(m_CVideoCG210Para.StartX,m_CVideoCG210Para.StartY,m_CVideoCG210Para.ImageSize_X+m_CVideoCG210Para.StartX,m_CVideoCG210Para.ImageSize_Y+m_CVideoCG210Para.StartY);
	CRect rcDisp;
	cgBoard.GetVisualVideoRect(rcDisp);
	m_dlg.m_Page4->m_rcDisp=rcDisp;//CRect(m_CVideoCG210Para.StartX,m_CVideoCG210Para.StartY,rcDisp.Width()+m_CVideoCG210Para.StartX,rcDisp.Height()+m_CVideoCG210Para.StartY);
	//Windows
	m_dlg.m_Page5->m_nStartx=InputVideoRect.left;//m_CVideoCG210Para.StartX;
	m_dlg.m_Page5->m_nStarty=InputVideoRect.top;//m_CVideoCG210Para.StartY;
	m_dlg.m_Page5->m_nWidth=InputVideoRect.Width();//m_CVideoCG210Para.ImageSize_X;
	m_dlg.m_Page5->m_nHeight=InputVideoRect.Height();//m_CVideoCG210Para.ImageSize_Y;
	//
	BOOL ret;
	if(m_dlg.DoModal()==IDOK) 
	{
		
		cgBoard.m_CVideoCGPara.nADBri=m_dlg.m_Page1->nADBri;
		cgBoard.m_CVideoCGPara.nADCon=m_dlg.m_Page1->nADCon;
		cgBoard.m_CVideoCGPara.nADHue=m_dlg.m_Page1->nADHue;
		cgBoard.m_CVideoCGPara.nADSat=m_dlg.m_Page1->nADSat;
		if(cgBoard.GetCGBoardType()==0)
		{
			cgBoard.m_CVideoCGPara.nADClamp = m_dlg.m_Page1->nADClamp;
			cgBoard.m_CVideoCGPara.nADBandPass = m_dlg.m_Page1->nADBand;
		}
		//source
		cgBoard.m_CVideoCGPara.nADSource=m_dlg.m_Page2->nADSource;
		//color
		cgBoard.m_CVideoCGPara.nColorSpace=m_dlg.m_Page3->nADCla;
	
		//interlace
		cgBoard.m_CVideoCGPara.nInterlace=m_dlg.m_Page4->nADFld;
		cgBoard.m_CVideoCGPara.bClip=m_dlg.m_Page4->m_display;
		cgBoard.m_CVideoCGPara.nVideoStand=m_dlg.m_Page4->m_mode;
		//
		InputVideoRect.left = m_dlg.m_Page5->m_nStartx;
		InputVideoRect.top = m_dlg.m_Page5->m_nStarty;
		InputVideoRect.right = m_dlg.m_Page5->m_nWidth+InputVideoRect.left;
		InputVideoRect.bottom = m_dlg.m_Page5->m_nHeight+InputVideoRect.top;
		
		ret= TRUE;
	}
	else
	{
		ret= FALSE;
	}
	cgBoard.SetInputVideoRect(InputVideoRect);
	DWORD cgHandle=cgBoard.GetCGBoardHandle();
	cgBoard.m_CVideoCGPara.VideoParaTakeEffect(cgHandle);
	//	CG200SetColorSpace( cgHandle, cgBoard.m_CVideoCGPara.nColorSpace);
	//	cgBoard.DhBoardSetColorSpace(cgBoard.m_CVideoCGPara.nColorSpace);
	//	cgBoard.SetCgBoardLiveOrFreeze(false);
	InitInputVideoRect();
	if(m_bDDraw)
		InitVisualVideoRect(false);
	OnChangeViewSize();
	return;
	
}
//抓取一幅图象到屏幕
//并保存为位图句柄
void CDHCGBoardDemoView::OnCgcardSnap() 
{
	if(m_bFreeze)
	{
		BeginWaitCursor();
		CDHCGBoardDemoDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if(pDoc->hdib!=NULL)
			pDoc->FreeDIBHandle();
		//	CRect inpRect;
		//	CRect disRect;
		if(m_bDDraw)
		{
			InitVisualVideoRect(true);
			//	cgBoard.GetInputVideoRect(inpRect);
			//	GetClientRect(disRect);
			//	cgBoard.GetVisualVideoRect(disRect);
			//	cgBoard.SetInputVideoRect(disRect);
		}
		cgBoard.DhBoardSnap();
		if(m_bDDraw)
		{
			InitVisualVideoRect(false);
			//	cgBoard.SetInputVideoRect(inpRect);
		}
		pDoc->hdib=ReadDispWindowToHandle();

		pDoc->UpdateAllViews(NULL);
		EndWaitCursor();
	}
	
}
//以下为菜单和工具条的调整

void CDHCGBoardDemoView::OnUpdateCgcardCg210para(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bInitCGboard&&cgBoard.GetCGBoardType());	
}

void CDHCGBoardDemoView::OnUpdateCgcardModeDirectx(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bInitCGboard);
	pCmdUI->SetCheck(m_bDDraw);
	
}

void CDHCGBoardDemoView::OnUpdateCgcardModeScreen(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bInitCGboard);
	pCmdUI->SetCheck(!m_bDDraw);	
}

void CDHCGBoardDemoView::OnUpdateCgboardplay(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bInitCGboard&&m_bFreeze);
}

void CDHCGBoardDemoView::OnUpdateCgboardstop(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bInitCGboard&&!m_bFreeze);
	
}

void CDHCGBoardDemoView::OnCgboardMask() 
{
	// TODO: Add your command handler code here
	if(m_bFreeze)
	{
		if(m_bMask)
			m_bMask=false;
		else
			m_bMask=true;
	}
}

void CDHCGBoardDemoView::OnUpdateCgboardMask(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bInitCGboard&&!m_bDDraw);
	pCmdUI->SetCheck(m_bMask);
}

void CDHCGBoardDemoView::SetMask(CRect rect,bool bMask)
{
	if(bMask)
	{
		DWORD pPhy=cgBoard.GetPhysicalAdd();
		DWORD offset=cgBoard.GetPhysicalMemSize()-1024*1024;
		//	BYTE* pLine=(BYTE*)cgBoard.GetPhysicalMemHandle();
		BYTE* pLine=(BYTE*)cgBoard.GetLinearAdd();
		pLine+=offset;
		DWORD MaskOffset;
		if(GetDeviceCaps(::GetDC(NULL),HORZRES)==800&&cgBoard.m_CVideoCGPara.nColorSpace==RGB888)
		{//2001 2 5
			MaskOffset	=GetDeviceCaps(::GetDC(NULL),HORZRES)/8+4;//有些卡需要使用		
		}
		else
		{
			MaskOffset=GetDeviceCaps(::GetDC(NULL),HORZRES)/8;
		}
		memset(pLine,0xff,MaskOffset*576);
		
		int i,j,pos=rect.top*MaskOffset;
		int left=rect.left/8;
		int right=rect.right/8;
		for(i=0;i<rect.Height();i++)
			for(j=0;j<rect.Width()/8;j++)
				*(pLine+pos+j+(i*MaskOffset)+left)=0;
			
		cgBoard.DhBoardSetMask(TopField,pPhy+offset);
		cgBoard.DhBoardSetMask(BottomField,pPhy+offset);
	}
	cgBoard.DhBoardEnableOverlay(bMask);
}

void CDHCGBoardDemoView::OnCgboardCapturemem() 
{
	if(m_bFreeze)
	{
		CDHCGBoardDemoDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if(pDoc->hdib!=NULL)
			pDoc->FreeDIBHandle();
		CRect DisplayRect;
		cgBoard.GetVisualVideoRect(DisplayRect);

		BITMAPINFO BMIInfo;
		BMIInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		BMIInfo.bmiHeader.biWidth = DisplayRect.Width();
		BMIInfo.bmiHeader.biHeight = DisplayRect.Height();
		BMIInfo.bmiHeader.biPlanes = 1;
		BMIInfo.bmiHeader.biBitCount = 24;
		BMIInfo.bmiHeader.biCompression = BI_RGB;
		BMIInfo.bmiHeader.biSizeImage = 0;
		BMIInfo.bmiHeader.biXPelsPerMeter = 0;
		BMIInfo.bmiHeader.biYPelsPerMeter = 0;
		BMIInfo.bmiHeader.biClrUsed = 0;
		BMIInfo.bmiHeader.biClrImportant = 0;
		
		HGLOBAL hDIB;
		DWORD dwSize = (long)DisplayRect.Width() * 
			(long)DisplayRect.Height()*3L;
		hDIB = GlobalAlloc(GHND, dwSize);
		if( hDIB ){
			char* lpvBits = (char *)GlobalLock(hDIB);
			CDC* pScrnDC = GetDC();
			//	HANDLE vxdHandle = LoadDevice();
			DWORD dwPage;
			DWORD PhysMemAddr;
			DWORD MemHandle;
			DWORD LineAddr;
			StaticMemAlloc(&dwPage, &PhysMemAddr, &MemHandle, &LineAddr);
			
			char *lpSourceBuf = (char *)LineAddr;
			int nSum = 23;
			int type=cgBoard.GetCGBoardType();
			if(type)
				CG210CaptureToMem(cgBoard.GetCGBoardHandle(), PhysMemAddr, dwPage*4*1024, 2 ,FRAME, nSum);
			else
				CG200CaptureToMem(cgBoard.GetCGBoardHandle(), PhysMemAddr, dwPage*4*1024, 2 ,FRAME, nSum);
			for(int k = 0; ; ++k){	
				if(type)
					CG210ReadFromMem(cgBoard.GetCGBoardHandle(), lpSourceBuf, dwPage*4*1024, k, lpvBits);
				else
					CG200ReadFromMem(cgBoard.GetCGBoardHandle(), lpSourceBuf, dwPage*4*1024, k, lpvBits);
				//		CG200ReadFromMem( hcg200, &LineAddr, dwPage*4*1024, k, lpvBits);
				pScrnDC->SetStretchBltMode(COLORONCOLOR);
				SetDIBitsToDevice( pScrnDC->GetSafeHdc(),//
					0, 0,
					DisplayRect.Width(), DisplayRect.Height(),
					0, 0,
					0, DisplayRect.Height(), lpvBits,
					&BMIInfo, DIB_RGB_COLORS);
				if(k >21)
					k = -1; 
				
				MSG	lpMsg;
				PeekMessage(&lpMsg,NULL,0,0,PM_REMOVE);
				if( (GetKeyState(VK_ESCAPE) &0x80) == 0x80 ||
					(GetKeyState(VK_LBUTTON)&0x80) == 0x80 ||
					(GetKeyState(VK_RBUTTON)&0x80) == 0x80 )
					break; 
			}
			
			//	bRet = PhysMemFree(vxdHandle, MemAlloc.Handle);
			ReleaseDC(pScrnDC);
			GlobalUnlock(hDIB);
			GlobalFree(hDIB);
			//	CloseDevice(vxdHandle);
		}	
	}
}

void CDHCGBoardDemoView::OnUpdateCgboardCapturemem(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bInitCGboard&&m_bFreeze);	
}


//DEL void CDHCGBoardDemoView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
//DEL {
//DEL 	// TODO: Add your specialized code here and/or call the base class
//DEL 		
//DEL 	
//DEL 	//	CDHCGBoardDemoDoc* pDoc = GetDocument();
//DEL  		//	ASSERT_VALID(pDoc);
//DEL 
//DEL 	CScrollView::OnPrint(pDC, pInfo);
//DEL }

//DEL void CDHCGBoardDemoView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
//DEL {
//DEL 	// TODO: Add your specialized code here and/or call the base class
//DEL 		//	m_bPrePrint=false;
//DEL 	CScrollView::OnEndPrintPreview(pDC, pInfo, point, pView);
//DEL 	
//DEL }

void CDHCGBoardDemoView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	CDHCGBoardDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(pInfo->m_bPreview)
	{
		if(pDoc->hdib!=NULL)
		{	
			CSize size;
			DIBSize(pDoc->hdib,&size);
			//	SetScrollSizes(MM_TEXT, size);
			CRect lprect,rectdisp;
			lprect.SetRectEmpty();
			lprect.right=size.cx;
			lprect.bottom=size.cy;
			rectdisp.SetRectEmpty();
			//	pDC;
			//2000 2 2
			rectdisp.right=pInfo->m_rectDraw.Width();
			rectdisp.bottom=lprect.bottom*pInfo->m_rectDraw.Width()/lprect.Width();
			PaintDIB(pDC->GetSafeHdc(),rectdisp,pDoc->hdib,lprect,NULL);
		}
		CMainFrame* pMainfrm=(CMainFrame*)AfxGetMainWnd();
		
		pMainfrm->m_bPrePrint=true;
	}
	CScrollView::OnPrint(pDC, pInfo);
}



void CDHCGBoardDemoView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CScrollView::OnEndPrintPreview(pDC, pInfo, point, pView);
	CMainFrame* pMainfrm=(CMainFrame*)AfxGetMainWnd();
	if(pMainfrm->m_bPrePrint)//2000 2 5 lfl切换图象
		pMainfrm->m_bPrePrint=false;
}

void CDHCGBoardDemoView::OnUpdateCgcardMem(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_bInitCGboard);
}

void CDHCGBoardDemoView::OnUpdateCgcardParam(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_bInitCGboard);
}

void CDHCGBoardDemoView::OnUpdateCgcardSnap(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_bInitCGboard);
}

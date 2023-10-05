// 主控报表View.cpp : implementation of the CMyView class
//

#include "stdafx.h"
#include "主控报表.h"
#include "GridCtrl.h"
#include "OwnWnd.h"


#include "主控报表Doc.h"
#include "主控报表View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyView

IMPLEMENT_DYNCREATE(CMyView, CView)

BEGIN_MESSAGE_MAP(CMyView, CView)
	//{{AFX_MSG_MAP(CMyView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyView construction/destruction

CMyView::CMyView()
{
	// TODO: add construction code here
	m_pGridCtrl = NULL;
	m_ownwnd=NULL;

}

CMyView::~CMyView()
{
	if (m_pGridCtrl)
		delete m_pGridCtrl;
	
}

BOOL CMyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyView drawing

void CMyView::OnDraw(CDC* pDC)
{
	CMyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMyView printing

BOOL CMyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyView diagnostics

#ifdef _DEBUG
void CMyView::AssertValid() const
{
	CView::AssertValid();
}

void CMyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyDoc* CMyView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyDoc)));
	return (CMyDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyView message handlers

BOOL CMyView::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CView::DestroyWindow();
}

void CMyView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class


	// TODO: Add your specialized code here and/or call the base class

	m_ownwnd=new COwnWnd();
	
    CRect rect;
		GetClientRect(rect);
		rect.bottom=rect.top+rect.Height()/4+10;
	//	rect.left=rect.left-80;
 
		m_ownwnd->Create(rect,this,200);

	CDC *pDC;

	if (m_pGridCtrl == NULL)
	{
		// 创建 Gridctrl 对象
		m_pGridCtrl = new CGridCtrl;
		if (!m_pGridCtrl) return;

		// 创建 Gridctrl 窗口
		CRect rect;
		GetClientRect(rect);
		
		m_pGridCtrl->Create(rect, this, 100);

		// 填充数据
		m_pGridCtrl->SetEditable(TRUE);
		m_pGridCtrl->EnableDragAndDrop(TRUE);

		try {
			m_pGridCtrl->SetRowCount(33);
			m_pGridCtrl->SetColumnCount(31);
			m_pGridCtrl->SetFixedRowCount(4);
			m_pGridCtrl->SetFixedColumnCount(1);
		}
		catch (CMemoryException* e)
		{
			e->ReportError();
			e->Delete();
			return;
		}

		// 填充每格数据
		for (int row = 0; row < m_pGridCtrl->GetRowCount(); row++)
			for (int col = 0; col < m_pGridCtrl->GetColumnCount(); col++)
			{ 
				GV_ITEM Item;
				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = row;
				Item.col = col;
				if (row < 1) {
					Item.nFormat = DT_LEFT|DT_WORDBREAK;
					switch(col)
					{
					  case 1:
						Item.szText.Format(_T("1# 发电机"));break;
					  case 10:
						Item.szText.Format(_T("2# 发电机"));break;
					  case 19:
						  Item.szText.Format(_T("1# 主变"));break;
					   case 22:
						   Item.szText.Format(_T("110kv 车乔线"));break;
					   case 27:
						   Item.szText.Format(_T("10kv 母线"));break;
					   case 29:
						   Item.szText.Format(_T("110kv 母线"));break;

					}
					
				} else if (col < 1) {
					Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
					if(row>=4&&row<28)
					Item.szText.Format(_T(" %d"),row-3);
					else 
					{
						switch(row)
						{
						case 30:Item.szText.Format(_T("4"));break;
						case 31:Item.szText.Format(_T(" 12"));break;
						case 32:Item.szText.Format(_T(" 20"));break;
						}

					}
				} else {
					Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
					Item.szText.Format(_T(" "));
				}
				m_pGridCtrl->SetItem(&Item);
		}

		m_pGridCtrl->AutoSize();
		m_pGridCtrl->SetRowHeight(0, 3*m_pGridCtrl->GetRowHeight(0)/2);
	}
      

	      
		  pDC=m_pGridCtrl->GetDC();
		  CSize cellSize;
		  GV_ITEM Item;
		  Item.mask = GVIF_TEXT|GVIF_FORMAT;
		  Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
		  CRect tempRect;
	  if (m_pGridCtrl->GetSafeHwnd())
	  {   
		  m_pGridCtrl->SetFixedCellCombine(0,0,3,0);
		  m_pGridCtrl->SetFixedCellCombine(0,1,0,8);
		  m_pGridCtrl->SetFixedCellCombine(0,10,0,8);
		  m_pGridCtrl->SetFixedCellCombine(0,19,0,2);
		  m_pGridCtrl->SetFixedCellCombine(0,22,0,4);
		  m_pGridCtrl->SetFixedCellCombine(0,27,0,1);
		  m_pGridCtrl->SetFixedCellCombine(0,29,0,1);
		  int i;
          
		  

		  for(i=5;i<=10;i++)
		  {
			  Item.col=i;
			  Item.row=1;
			  m_pGridCtrl->SetFixedCellCombine(1,i,1,0);
			  switch(i)
			  {
			  case 5:
				  Item.szText.Format(_T("有功"));
				  
				  cellSize=pDC->GetTextExtent("有功");
				  m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);
				  break;
			  case 6:
				  Item.szText.Format(_T("无功"));
			
				  cellSize=pDC->GetTextExtent("无功");
				  m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);break;
			  case 7:
				   Item.szText.Format(_T("励磁电压"));
				  
				  cellSize=pDC->GetTextExtent("励磁电压");
				  m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);break; 
			  case 8:

				  Item.szText.Format(_T("励磁电流"));
				  
				  cellSize=pDC->GetTextExtent("励磁电流");
				  m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);break;
               case 9:
				  Item.szText.Format(_T("复励电流"));
				  
				  cellSize=pDC->GetTextExtent("复励电流");
				  m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);break;
			   case 10:
				  Item.szText.Format(_T("电压"));
				  
				  cellSize=pDC->GetTextExtent("电压");
				  m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);break;

			  }
			  m_pGridCtrl->SetItem(&Item);
		  }
		  for(i=14;i<=23;i++)
		  {
			  Item.col=i;
			  Item.row=1;
			  m_pGridCtrl->SetFixedCellCombine(1,i,1,0);
			  switch(i)
			  {
			  case 14:case 19:case 22:
                  Item.szText.Format(_T("有功"));
				  
				  cellSize=pDC->GetTextExtent("有功");
				  m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);
				  break;
			  case 15:case 20:case 23:
				  Item.szText.Format(_T("无功"));
				  
				 cellSize=pDC->GetTextExtent("无功");
				  m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);
				  break;
			  case 16:
				   Item.szText.Format(_T("励磁电压"));
				  
				  cellSize=pDC->GetTextExtent("励磁电压");
				  m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);
				  break; 
			  case 18:
				  Item.szText.Format(_T("复励电流"));
				  
				  cellSize=pDC->GetTextExtent("复励电流");
				  m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);
				  break;
			  case 17:
				  Item.szText.Format(_T("励磁电流"));
				  
				  cellSize=pDC->GetTextExtent("励磁电流");
				  m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);
				  break;
			  case 21:
				  Item.szText.Format(_T("电流"));
				  
				  cellSize=pDC->GetTextExtent("电流");
				  m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);
				  break;

			  }
           m_pGridCtrl->SetItem(&Item);

		  }
		  for(i=27;i<=30;i++)
		  {   
			  Item.col=i;
			  Item.row=1;
			  m_pGridCtrl->SetFixedCellCombine(1,i,1,0);
			  switch(i)
			  {
			  case 27:case 29:
				  Item.szText.Format(_T("周波"));
				  
				  cellSize=pDC->GetTextExtent("周波");
				  m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);
				  break;
			  case 28:case 30:
				  Item.szText.Format(_T("电压"));
				  
				  cellSize=pDC->GetTextExtent("电压");
				  m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);
				  break;
				 } 

			  m_pGridCtrl->SetItem(&Item);
		  }
		  m_pGridCtrl->SetFixedCellCombine(1,24,0,2);
                 Item.col=24;
			     Item.row=1;
		          Item.szText.Format(_T("电流"));
				  m_pGridCtrl->SetItem(&Item);
				  cellSize=pDC->GetTextExtent("电流");
				  m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);
				  for(i=0;i<=2;i++)
				  {
					  Item.row=2;
					  switch(i)
					  {
						  
					  case 0:
                        Item.col=24;
					    Item.szText.Format(_T(" A "));
				        
				        cellSize=pDC->GetTextExtent(" A ");
				        m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);
						break;
					  case 1:
						 Item.col=25;
					    Item.szText.Format(_T(" B "));
				        
				        cellSize=pDC->GetTextExtent(" B ");
				        m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);
						break;
					  case 2:
						 Item.col=26;
					    Item.szText.Format(_T(" C "));
				        
				        cellSize=pDC->GetTextExtent(" C ");
				        m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);
						break;

					  }
					  m_pGridCtrl->SetItem(&Item);

				  }




          m_pGridCtrl->SetFixedCellCombine(1,2,0,2);
		         Item.col=2;
			     Item.row=1;
		          Item.szText.Format(_T("电流"));
				  m_pGridCtrl->SetItem(&Item);
				  cellSize=pDC->GetTextExtent("电流");
				  m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);
                  for(i=0;i<=2;i++)
				  {
					  Item.row=2;
					  switch(i)
					  {
						  
					  case 0:
                        Item.col=2;
					    Item.szText.Format(_T(" A "));
				        
				        cellSize=pDC->GetTextExtent(" A ");
				        m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);
						break;
					  case 1:
						 Item.col=3;
					    Item.szText.Format(_T(" B "));
				        
				        cellSize=pDC->GetTextExtent(" B ");
				        m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);
						break;
					  case 2:
						 Item.col=4;
					    Item.szText.Format(_T(" C "));
				        
				        cellSize=pDC->GetTextExtent(" C ");
				        m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);
						break;

					  }
					  m_pGridCtrl->SetItem(&Item);

				  }



		  m_pGridCtrl->SetFixedCellCombine(1,1,1,0);
		         Item.col=1;
			     Item.row=1;
		          Item.szText.Format(_T("电压"));
				  m_pGridCtrl->SetItem(&Item);
				  cellSize=pDC->GetTextExtent("电压");
				  m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);


		  m_pGridCtrl->SetFixedCellCombine(1,11,0,2);

		         Item.col=11;
			     Item.row=1;
		          Item.szText.Format(_T("电流"));
				  m_pGridCtrl->SetItem(&Item);
				  cellSize=pDC->GetTextExtent("电流");
				  m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);
                  for(i=0;i<=2;i++)
				  {
					  Item.row=2;
					  switch(i)
					  {
						  
					  case 0:
                        Item.col=11;
					    Item.szText.Format(_T(" A "));
				        
				        cellSize=pDC->GetTextExtent(" A ");
				        m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);
						break;
					  case 1:
						 Item.col=12;
					    Item.szText.Format(_T(" B "));
				        
				        cellSize=pDC->GetTextExtent(" B ");
				        m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);
						break;
					  case 2:
						 Item.col=13;
					    Item.szText.Format(_T(" C "));
				        
				        cellSize=pDC->GetTextExtent(" C ");
				        m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);
						break;
				  }
					  m_pGridCtrl->SetItem(&Item);

				}
		 
		  Item.row = 3;
		
		  for(i=1;i<=30;i++)
		  {
			  Item.col=i;
			  switch(i)
			  {
			     case 2:case 3:case 4:case 8:case 9:case 11:case 12: case 13: 
				 case 17:case 18:case 21:case 24:case 25:case 26:
				  
			      Item.szText.Format(_T(" A"));
				  break;
				 case 1:case 10:case 28:case 30:
                  Item.szText.Format(_T("KV"));
				  break;
				 case 5:case 14:case 19:case 22:
				 Item.szText.Format(_T("MW"));
				  break;
				 case 6:case 15:case 20:case 23:
				 Item.szText.Format(_T("MVar"));
				  break;
				 case 7:case 16:
				 Item.szText.Format(_T("V"));
				  break;
				 case 27:case 29:
				  Item.szText.Format(_T("Hz"));
				  break;

			  }
				m_pGridCtrl->SetItem(&Item);
		  }

       CGridCell *pCell;
        m_pGridCtrl->SetFixedCellCombine(28,0,1,0);
        m_pGridCtrl->SetCellCombine(28,1,0,2,TRUE);
	       Item.col=1;
		   Item.row=28;
		   Item.szText.Format(_T("发电机风温℃"));
		   m_pGridCtrl->SetItem(&Item);
		   for(i=1;i<4;i++)
		   {
				Item.row=29;
				Item.col=i;
				switch(i)
				{
				case 1:Item.szText.Format(_T("励磁侧入口"));break;
				case 2:Item.szText.Format(_T("汽机侧入口"));break;
				case 3:Item.szText.Format(_T("出口"));break;

				}
				m_pGridCtrl->SetItem(&Item);
				pCell=m_pGridCtrl->GetCellP(Item.row,Item.col);
				pCell->m_bNoEdit=TRUE;
				cellSize=pDC->GetTextExtent("123456");
			   if(m_pGridCtrl->GetCellRect(Item.row,Item.col,tempRect))
				   if(cellSize.cx+10>tempRect.Width())
					   m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);

		   }



		   m_pGridCtrl->SetCellCombine(28,4,0,11,TRUE);
	       Item.col=4;
		   Item.row=28;
		   Item.szText.Format(_T("发电机静子线圈．静子铁心温度℃"));
		   m_pGridCtrl->SetItem(&Item);
		   for(i=0;i<12;i++)
		   {
			   Item.row=29;
			   Item.col=4+i;
               Item.szText.Format(_T(" %d  "),19+i);
			   m_pGridCtrl->SetItem(&Item);
			   pCell=m_pGridCtrl->GetCellP(Item.row,Item.col);
				pCell->m_bNoEdit=TRUE;
			   cellSize=pDC->GetTextExtent("123456");
			   if(m_pGridCtrl->GetCellRect(Item.row,Item.col,tempRect))
				   if(cellSize.cx+10>tempRect.Width())
					   m_pGridCtrl->SetColumnWidth(Item.col,cellSize.cx+10);



		   }
       
	 for(i=0;i<6;i++)
	 {
		 CString str;
		Item.row=28;
		switch(i)
		{
		case 0:Item.col=16;
			Item.szText.Format(_T("1#高厂变温度"));break;
		case 1:Item.col=17;
            Item.szText.Format(_T("2#高厂变温度"));break;
		case 2:Item.col=18;
			Item.szText.Format(_T("0#高厂变温度"));break;
		case 3:Item.col=28;
			Item.szText.Format(_T("除尘变温度"));break;
		case 4:Item.col=29;
			Item.szText.Format(_T("输煤变温度"));break;
		case 5:Item.col=30;
			Item.szText.Format(_T("主变温度"));break;


		}
	
		 m_pGridCtrl->SetItem(&Item);
		 m_pGridCtrl->SetCellCombine(Item.row,Item.col,1,0,TRUE);

       
		 
	 }
       

	 for (i=0;i<=3;i++)
	 {
		 
		Item.row=28;
		switch (i)
		{
		   case 0:Item.col=19;
			   Item.szText.Format(_T("1#低厂变温度"));break;
		   case 1:Item.col=21;
			   Item.szText.Format(_T("2#低厂变温度"));break;
		   case 2:Item.col=23;
			   Item.szText.Format(_T("3#低厂变温度"));break;
		   case 3:Item.col=25;
			   Item.szText.Format(_T("0#低厂变温度"));break;



		}

		
		 m_pGridCtrl->SetItem(&Item);
         int hNum=i!=3?1:2;
		 m_pGridCtrl->SetCellCombine(Item.row,Item.col,1,hNum,TRUE);
		 int j=m_pGridCtrl->GetRowCount();
		 while(j>Item.row)
		 {
			 m_pGridCtrl->SetCellCombine(j,Item.col,0 ,hNum);
			 j--;}
		 
	 }

		  
	   }//if (m_pGridCtrl->GetSafeHwnd())ended
     




	
}

void CMyView::OnSize(UINT nType, int cx, int cy) 
{

	CView::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here
	CRect rect,tempRect;
	GetClientRect(rect);
	tempRect=rect;
	if(m_ownwnd->GetSafeHwnd())
	{
        tempRect.bottom=rect.top+rect.Width()/7;
		m_ownwnd->MoveWindow(tempRect);
	}
	
	
	if (m_pGridCtrl->GetSafeHwnd())
	{
		
        rect.top=rect.top+rect.Width()/7;
		m_pGridCtrl->MoveWindow(rect);
	}
	
	

	
}

BOOL CMyView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (m_pGridCtrl && IsWindow(m_pGridCtrl->m_hWnd))
        if (m_pGridCtrl->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
            return TRUE;


	return CView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

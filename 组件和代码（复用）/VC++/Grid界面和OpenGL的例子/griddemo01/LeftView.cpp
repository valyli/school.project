// LeftView.cpp : implementation file
//

#include "stdafx.h"
#include "���ر���.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

CLeftView::CLeftView()
{
}

CLeftView::~CLeftView()
{
}


BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	//{{AFX_MSG_MAP(CLeftView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing

void CLeftView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers

void CLeftView::OnInitialUpdate() 
{
	CTreeView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	CTreeCtrl &treeCtrl=GetTreeCtrl();
	DWORD dwStyle=::GetWindowLong(treeCtrl.m_hWnd,GWL_STYLE);
	dwStyle|=TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT;
	::SetWindowLong(treeCtrl.m_hWnd,GWL_STYLE,dwStyle);
	HTREEITEM hRoot,hCurPos;
	TV_INSERTSTRUCT tInsert;
	tInsert.hParent=TVI_ROOT;
	tInsert.hInsertAfter=TVI_LAST;
	tInsert.item.mask=TVIF_TEXT|TVIF_PARAM;
    tInsert.item.pszText="���繫˾�����������籨��";
	tInsert.item.lParam=0;
	hRoot=treeCtrl.InsertItem(&tInsert);
	char *plant[4]={"����","����","��¯","��ѧ"};
	char *cell[4][5]={
        {"(һ)","(��)","(��)","(��)","(��)"},//��ϵͳ������־
		{"1#��","2#��","����","����","����"},
		{"1#¯","2#¯","3#¯","�����","�ͱ÷�"},
		{"����վ","","","",""}
	};
	int i,j;
	for(i=0;i<4;i++)
	{
		tInsert.hParent=hRoot;
		tInsert.item.pszText=plant[i];
		hCurPos=treeCtrl.InsertItem(&tInsert);
		for(j=0;j<5;j++)
		{
			tInsert.hParent=hCurPos;
			if(cell[i][j]!="")
			{
		      tInsert.item.pszText=cell[i][j];
			  treeCtrl.InsertItem(&tInsert);}
		}
		//treeCtrl.Expand(hCurPos,TVE_EXPAND);


	}
	treeCtrl.Expand(hRoot,TVE_EXPAND);

 
	

	
}

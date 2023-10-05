// 绘图程序View.cpp : implementation of the CMyView class
//

#include "stdafx.h"
#include "绘图程序.h"

#include "绘图程序Doc.h"
#include "绘图程序View.h"
#include <stdlib.h>
#include <math.h>
#include "Eillpise.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define N 5
#define M 10
#define M_B 1000
#define N_B 6

int MaxX = 640, MaxY = 480;
int Origin_X = 320, Origin_Y = 240;
int Unit_Size=40;



/////////////////////////////////////////////////////////////////////////////
// CMyView

IMPLEMENT_DYNCREATE(CMyView, CView)

BEGIN_MESSAGE_MAP(CMyView, CView)
	//{{AFX_MSG_MAP(CMyView)
	ON_COMMAND(ID_PAOWU2, OnPaowu2)
	ON_COMMAND(ID_EQUATION, OnEquation)
	ON_COMMAND(ID_B, OnB)
	ON_COMMAND(ID_ELLIPSE, OnEllipse)
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
	m_ea = 150;
	m_eb = 100;
}

CMyView::~CMyView()
{
}

BOOL CMyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	DrawNew = 0;
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyView drawing

void CMyView::OnDraw(CDC* pDC)
{
	CMyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
//	if(DrawNew == 0)
//		return;
	DrawFrame();
	if(DrawNew != 0)
	{
		if(DrawNew == 1)
			DrawPaowu2();
		if(DrawNew == 2)
			DrawEquation();
		if(DrawNew == 3)
			DrawB();
		if(DrawNew == 4)
			DrawEllpise();
	}
//	DrawNew = 0;
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

void CMyView::OnPaowu2() 
{
	DrawNew = 1;
	Invalidate(TRUE);
}

void CMyView::DrawFrame()
{
//	int MaxX = 640;
//	int MaxY = 480;
//	int Unit_Size = 40;
	Origin_X = 320;//40;
	Origin_Y = 240;//MaxY-40;
	CClientDC dc(this);
	CPoint m_point;
	CPen pen(PS_SOLID,1,RGB(0,100,50));
	dc.SelectObject(&pen);
	char string[4];
	dc.SetTextColor(RGB(50,100,0));//setcolor(Font_Color);
//	dc.TextOut(int(MaxX/2)-60,10,"Draw Line Program");
	dc.TextOut(MaxX,30,"计算机系99级2班");
	dc.TextOut(MaxX+20,10,"李佳, CNU");
	dc.SetTextColor(RGB(0,0,255));//setcolor(DARKGRAY);
	for(int x=40; x<MaxX; x+=Unit_Size)
	{
		dc.MoveTo(x,40);
		m_point.x = x;m_point.y = MaxY-40;
		dc.LineTo(m_point);//line(x,40,x,MaxY-40);
		dc.SetTextColor(RGB(0,0,255));//setcolor(BLUE);
		dc.MoveTo(x,MaxY-40);
		m_point.x = x;m_point.y = MaxY-40-5;
		dc.LineTo(m_point);//(x,MaxY-40,x,MaxY-40-5);
		dc.SetTextColor(RGB(0,0,255));//setcolor(Font_Color);
		dc.TextOut(x-10, Origin_Y,gcvt(int(x-Origin_X),4,string));
//		outtextxy(x-10,MaxY-40+3,gcvt(x-Origin_X,4,string));
		dc.SetTextColor(RGB(0,0,255));//setcolor(DARKGRAY);
	}
//	dc.SetTextColor(RGB(0,0,255));//setcolor(DARKGRAY);
	for(int y=40; y<MaxY; y+=Unit_Size)
	{
		dc.MoveTo(40,y);
		m_point.x = MaxX-40; m_point.y = y;
		dc.LineTo(m_point);//line(40,y,MaxX-40,y);
		dc.SetTextColor(RGB(0,0,255));//setcolor(BLUE);
		dc.MoveTo(40,y);
		m_point.x = 40+5; m_point.y = y;
		dc.LineTo(m_point);//line(40,y,40+5,y);
		dc.SetTextColor(RGB(0,0,255));//setcolor(Font_Color);
		dc.TextOut(Origin_X-10,y,gcvt(int(Origin_Y-y),4,string));
//		outtextxy(40-25,y,gcvt(440-y,4,string));
//		dc.SetTextColor(RGB(0,0,255));//setcolor(DARKGRAY);
	}
	CPen pen1(PS_SOLID,1,RGB(20,0,150));
	dc.SelectObject(&pen1);
//	dc.SetTextColor(RGB(255,255,0));//setcolor(BLUE);
	dc.MoveTo(40,Origin_Y);
	m_point.x = MaxX-40; m_point.y= Origin_Y;
	dc.LineTo(m_point);//line(40,MaxY-40+1,MaxX-40,MaxY-40+1);
	dc.MoveTo(Origin_X,40);
	m_point.x = Origin_X; m_point.y = MaxY-40;
	dc.LineTo(m_point);//line(40,40,40,MaxY-40);
}

void CMyView::OnEquation() 
{
	DrawNew = 2;
	Invalidate(TRUE);
}

void CMyView::DrawEquation()
{
	CClientDC dc(this);
	CPoint m_point;
	CPen pen(PS_SOLID,1,RGB(255,0,0));
	dc.SelectObject(&pen);
//  int     color,i,j  	 ;		/* woke vabriables	*/
  int     xi,yi          ;		/* int x,y   ,for draw  */
  int     xi_old,yi_old;
  double   xf,yf          ; 		/* float x,y ,for count */
  double   x_relative     ;              /* relative value of x  */
  double   x_arc          ;    		/* arc of x		*/
//  char    ch		 ;
  int n = 0;

//  outtextxy(480,60,"y = sin x ");
  xf = 20.0;                		/* draw from 20 to 620	*/
  while (xf <= 620.0 )
  {
//     for (int i=1;i<= 20000;i++)  ;           /* delay time		*/
     x_relative = xf-320.0;             /* 320 means x=0	*/
     x_arc=2.0*3.1415926/300.0*x_relative;  	/* count arc		*/
					/* 2*PI=360=300 points  */
     yf = sin(x_arc);                   /* count sin x      	*/
     yf = (-yf)*190.0+240.0;            /* '-' means Display's plus
					   is diffrent from axis'plus */
					/* 240 means y=0 ; 	*/
					/* 190 means 1/2 Vpp 	*/
     xi = (int)(xf);   			/* change float to int 	*/
     yi = (int)(yf); 		        /* change float to int  */
	 if(n == 0)
	 {
		 xi_old = xi;
		 yi_old = yi;
	 }
	 n++;
     dc.MoveTo(xi_old, yi_old);
	 m_point.x = xi;
	 m_point.y = yi;
	 dc.SelectObject(&pen);
	 dc.LineTo(m_point);
//putpixel(xi,yi,RED);               /* draw equation	*/
     xi_old = xi;
	 yi_old = yi;
	 xf = xf+0.1;
	}
}

void CMyView::DrawPaowu2()
{
	DrawFrame();
	CClientDC dc(this);
	CPen pen(PS_SOLID,1,RGB(255,0,0));
	CPoint m_point;
	int x_org=320;
	int y_org=240;
	
	double p[N+2][2];
	double q[5][2]={{0.0,0.0},{0.4,0.08},{0.8,0.32},{1.2,0.72},{1.6,1.28}};
 	int i,j;
	double px,py;
	int ix,iy;
	double t,t2,t3;
	double f1,f2,f3,f4;
//	char msg[10];
	dc.SelectObject(&pen);

	dc.SetTextColor(RGB(0,0,255));//setcolor(BLUE);
	p[0][0]=q[0][0];
	p[0][1]=q[0][1];

	p[N+1][0]=q[N-1][0];
	p[N+1][1]=q[N-1][1];

  for(i=0;i<=N-1;i++)
  {
    p[i+1][0]=q[i][0];
    p[i+1][1]=q[i][1];
  }
  ix=(int)(p[1][0]*(100)+x_org);
  iy=(int)(p[1][1]*(-100)+y_org);
  dc.MoveTo(ix, iy);//moveto(ix,iy);
//  circle(ix,iy,2);
//  sprintf(msg, " (%.2f, %.2f)", px, py);
//  outtextxy(ix+15, iy+15, msg);

  for(i=0;i<N-1;i++)
  {
    for(j=1;j<M;j++)
    {
      t=j*0.5/(M+1);
      t2 = t*t;
      t3 = t2*t;
      f1 = 4.0*t2-t-4.0*t3;
      f2 = 1.0-10.0*t2+12.0*t3;
      f3 = t+8.0*t2-12.0*t3;
      f4 = 4.0*t3-2.0*t2;
      px = f1*p[i][0]+f2*p[i+1][0]+f3*p[i+2][0]+f4*p[i+3][0];
      py = f1*p[i][1]+f2*p[i+1][1]+f3*p[i+2][1]+f4*p[i+3][1];
      ix = (int)(px*(100)+x_org);
      iy = (int)(py*(-100)+y_org);
	  m_point.x = ix;
	  m_point.y = iy;
      dc.LineTo(m_point);//lineto(ix,iy);
    }
    ix = (int)(p[i+2][0]*(100)+x_org);
    iy = (int)(p[i+2][1]*(-100)+y_org);
	m_point.x = ix;
	m_point.y = iy;
    dc.LineTo(m_point);
//    circle(ix,iy,2);
//    sprintf(msg, " (%.2f, %.2f)", p[i+2][0], p[i+2][1]);
//    outtextxy(ix+15, iy+15, msg);
  }
}

void CMyView::OnB() 
{
	DrawNew = 3;
	Invalidate(TRUE);	
}

void CMyView::DrawB()
{
	CClientDC dc(this);
	CPen pen(PS_SOLID,1,RGB(255,0,0));
	dc.SelectObject(&pen);
	CPoint m_point;

	double Bk[N_B][2]={{-0.6,1.0},{0.1,0.5},{0.9,1.5},{1.7,1.3},{2.2,0.2},{-1.5,-1.5}};

	int x_org=320;
	int y_org=240;
	int i,x,y;
	int n = 0;
	double t3,t2,t1,t;
	double f0,f1,f2,f3;
	double px,py;
	double B_t[N_B][2];
	for(i=0;i<N_B;i++)
	{
		B_t[i][0]=Bk[i][0]*100+x_org;
		B_t[i][1]=Bk[i][1]*(-100)+y_org;
	}
	dc.MoveTo(int(B_t[0][0]),int(B_t[0][1]));
	for(i=0;i<=N;i++)
	{
		m_point.x = long(B_t[i][0]);
		m_point.y = long(B_t[i][1]);
		dc.LineTo(m_point);
	}

	t=1.0/M_B;
	//moveto(B_t[0][0],B_t[0][1]);
	for(int j = 0; j<=N_B-4; j++)
	{
		for(i=1; i<=M_B; i++)
		{
			t1=i*t;
			t2=t1*t1;
			t3=t2*t1;

			f0=(-t3+3*t2-3*t1+1)/6;
			f1=(3*t3-6*t2+4)/6;
			f2=(-3*t3+3*t2+3*t1+1)/6;
			f3=t3/6;

			px=f0*Bk[j][0]+f1*Bk[j+1][0]+f2*Bk[j+2][0]+f3*Bk[j+3][0];
			py=f0*Bk[j][1]+f1*Bk[j+1][1]+f2*Bk[j+2][1]+f3*Bk[j+3][1];
			x=(int)(px*100+x_org);
			y=(int)(py*(-100)+y_org);
			if(n == 0)
				dc.MoveTo(x,y);
			n++;
			m_point.x = x;
			m_point.y = y;
			dc.LineTo(m_point);
		}
	}
}

void CMyView::OnEllipse() 
{
	CEillpise m_Eillpise;//("tuoyuan",this,0);
	m_Eillpise.m_a = m_ea;
	m_Eillpise.m_b = m_eb;
	if(m_Eillpise.DoModal() == IDOK)
	{
		m_ea = m_Eillpise.m_a;
		m_eb = m_Eillpise.m_b;
		Invalidate(TRUE);
	}
	DrawNew = 4;
	Invalidate(TRUE);
}

void CMyView::DrawEllpise()
{
	CClientDC dc(this);
	CPen pen(PS_SOLID,1,RGB(255,0,0));
	dc.SelectObject(&pen);
	CPoint m_point;

	int a = m_ea, b = m_eb, xc = 320, yc = 240;
	long aa = a * a, bb = b * b;
	long twoaa = 2 * aa, twobb = 2 * bb;
	long x = 0, y = b;
	long d;
	long dx = 0;
	long dy = twoaa * y;
	d = long(bb + aa * (-b + 0.25) + 0.5);
	dc.SetPixel(xc + x, yc + y, RGB(255, 0, 0));
	dc.SetPixel(xc + x, yc - y, RGB(255, 0, 0));
	dc.SetPixel(xc - x, yc + y, RGB(255, 0, 0));
	dc.SetPixel(xc - x, yc - y, RGB(255, 0, 0));
	while(dx < dy)
	{
		x++;
		dx += twobb;
		if(d<0)
			d += bb + dx;
		else
		{
			dy -= twoaa;
			d += bb + dx - dy;
			y--;
		}
		dc.SetPixel(xc + x, yc + y, RGB(255, 0, 0));
		dc.SetPixel(xc + x, yc - y, RGB(255, 0, 0));
		dc.SetPixel(xc - x, yc + y, RGB(255, 0, 0));
		dc.SetPixel(xc - x, yc - y, RGB(255, 0, 0));
	}
	d = long(bb * (x + 0.5) * (x + 0.5) + aa * (y - 1)*(y - 1) - aa * bb + 0.5);
	while(y>0)
	{
		y--;
		dy -= twoaa;
		if(d>0)
			d += aa - dy;
		else
		{
			x++;
			dx += twobb;
			d += aa -dy +dx;
		}
	dc.SetPixel(xc + x, yc + y, RGB(255, 0, 0));
	dc.SetPixel(xc + x, yc - y, RGB(255, 0, 0));
	dc.SetPixel(xc - x, yc + y, RGB(255, 0, 0));
	dc.SetPixel(xc - x, yc - y, RGB(255, 0, 0));
	}
}

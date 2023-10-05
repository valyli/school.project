#include <conio.h>
#include <iostream.h>
#include <stdlib.h>
#include <graphics.h>

////////////////////////// Define Graph_2D Class //////////////////////////

class Graph_2D
{
	public:
		double Chg_Matrix[3][3];
//		double a,b,p,c,d,q,l,m,s;
	private:
		const int NO_USE;
		struct Point_XY
		{
			int n;
			double x, y;
			int no_use;
			struct Point_XY *next, *previous;
		};
		Point_XY Init_Point_XY_H, *IXY,
			 New_Point_XY_H, *NXY;
		int Fore_Color,Back_Color;
		enum direct{UP=-1, DOWN=1, LEFT=-1, RIGHT=1};
		direct Level_Cooridinate_Direct,
		       Vertial_Cooridinate_Direct;
		enum bool {FALSE, TRUE};
		bool Pre_Drawed, Drawed, UnDrawed, Aftr_Drawed;
	public:
		Graph_2D(double ox, double oy, int i);
		void Set_ChgM_Std(void);
		void Set_Color(int foreground, int background);
		void Get_Color(int &foreground, int &background);
		void Set_Origin(double x, double y);
		void Get_Origin(double &x, double &y);
		void Set_Level_Direct(direct dx, direct dy);
		void Get_Vertial_Direct(direct &dx, direct &dy);
		bool Pre_Draw(void);
		bool Close_Graph(void);
		bool Draw(void);
		bool UnDraw(void);
		bool Aftr_Draw(void);
		bool ReSet_Point(int n, double x, double y);
		bool Get_Point(int n, double &x, double &y);
		void Insert_Point(int n, double x, double y);
		void Set_Point(int n, double x, double y);
		bool Del_Point(int n);
		~Graph_2D();
	private:
		bool Check_Input_N(int &n);
};

Graph_2D::Graph_2D(double ox=0.0, double oy=0.0, int i=1)
	:NO_USE(i)
{
	Set_ChgM_Std();
/*	a=Chg_Matrix[0][0];
	b=Chg_Matrix[0][1],
	p=Chg_Matrix[0][2],
	c=Chg_Matrix[1][0],
	d=Chg_Matrix[1][1],
	q=Chg_Matrix[1][2],
	l=Chg_Matrix[2][0],
	m=Chg_Matrix[2][1],
	s=Chg_Matrix[2][2];
*/
	Set_Color(WHITE,BLACK);
	Level_Cooridinate_Direct=RIGHT;
	Vertial_Cooridinate_Direct=UP;
	Pre_Drawed=FALSE;
	Drawed=FALSE;
	UnDrawed=FALSE;
	Aftr_Drawed=TRUE;
	Init_Point_XY_H.n=0;
	Init_Point_XY_H.x=ox;
	Init_Point_XY_H.y=oy;
	Init_Point_XY_H.no_use=NO_USE;
	Init_Point_XY_H.next=NULL;
	Init_Point_XY_H.previous=NULL;
	New_Point_XY_H=Init_Point_XY_H;
	IXY=new(Point_XY);
	NXY=new(Point_XY);
	IXY=&Init_Point_XY_H;
	NXY=&New_Point_XY_H;
}

void Graph_2D::Set_ChgM_Std(void)
{
	for(int i=0;i<=2;i++)
		for(int j=0;j<=i;j++)
			if(i==j) Chg_Matrix[i][j]=1.0;
			else Chg_Matrix[i][i]=0.0;
}

void Graph_2D::Set_Color(int foreground, int background)
{
	Fore_Color=foreground;
	Back_Color=background;
}

void Graph_2D::Get_Color(int &foreground, int &background)
{
	foreground=Fore_Color;
	background=Back_Color;
}

void Graph_2D::Set_Origin(double x, double y)
{
	Init_Point_XY_H.x=x;
	Init_Point_XY_H.y=y;
}

void Graph_2D::Get_Origin(double &x, double &y)
{
	x=Init_Point_XY_H.x;
	y=Init_Point_XY_H.y;
}

void Graph_2D::Set_Level_Direct(direct dx, direct dy)
{
	Level_Cooridinate_Direct=dx;
	Vertial_Cooridinate_Direct=dy;
}

void Graph_2D::Get_Vertial_Direct(direct &dx, direct &dy)
{
	dx=Level_Cooridinate_Direct;
	dy=Vertial_Cooridinate_Direct;
}

bool Graph_2D::Pre_Draw(void)
{
	if(Aftr_Drawed==FALSE) return FALSE;
	if(Init_Point_XY_H.n==0) return FALSE;
	IXY=&Init_Point_XY_H;
	IXY=IXY->next;
	NXY=&New_Point_XY_H;
	New_Point_XY_H.n=Init_Point_XY_H.n;
	New_Point_XY_H.x=Init_Point_XY_H.x;
	New_Point_XY_H.y=Init_Point_XY_H.y;
	New_Point_XY_H.no_use=Init_Point_XY_H.no_use;
	NXY->next=new(Point_XY);
	NXY=NXY->next;
	NXY->previous=NULL;
	while(IXY!=NULL)
	{
		NXY->next=new(Point_XY);
		NXY->next->previous=NXY;
		NXY->n=IXY->n;
		NXY->x=(IXY->x)*Chg_Matrix[0][0]+(IXY->y)*Chg_Matrix[1][0]+(IXY->no_use)*Chg_Matrix[2][0];
		NXY->y=(IXY->x)*Chg_Matrix[0][1]+(IXY->y)*Chg_Matrix[1][1]+(IXY->no_use)*Chg_Matrix[2][1];
		NXY->no_use=(IXY->x)*Chg_Matrix[0][2]+(IXY->y)*Chg_Matrix[1][2]+(IXY->no_use)*Chg_Matrix[2][2];
		NXY->x=Init_Point_XY_H.x+Level_Cooridinate_Direct*(NXY->x);
		NXY->y=Init_Point_XY_H.y+Vertial_Cooridinate_Direct*(NXY->y);
		IXY=IXY->next;
		NXY=NXY->next;
	}
	NXY=NXY->previous;
	NXY->next=NULL;
	New_Point_XY_H.previous=NXY;
	NXY->next->previous=NULL;
	delete(NXY->next);
	Pre_Drawed=TRUE;
	return TRUE;
}

bool Graph_2D::Close_Graph(void)
{
	if(Pre_Drawed==FALSE) return FALSE;
	if(New_Point_XY_H.n==0) return FALSE;
	New_Point_XY_H.previous->next=new(Point_XY);
	New_Point_XY_H.previous->next->previous=New_Point_XY_H.previous;
	New_Point_XY_H.previous->next->next=NULL;
	New_Point_XY_H.previous=New_Point_XY_H.previous->next;
	New_Point_XY_H.n++;
	New_Point_XY_H.previous->x=New_Point_XY_H.next->x;
	New_Point_XY_H.previous->y=New_Point_XY_H.next->y;
	New_Point_XY_H.previous->no_use=New_Point_XY_H.next->no_use;
	return TRUE;
}

bool Graph_2D::Draw(void)
{
	if(Pre_Drawed==FALSE) return FALSE;
	if(New_Point_XY_H.n==0 || New_Point_XY_H.n==1)
		return FALSE;
	double X1,Y1,no_use1,X2,Y2,no_use2;
	setcolor(Fore_Color);
	NXY=New_Point_XY_H.next;
	X1=NXY->x;
	Y1=NXY->y;
	no_use1=NXY->no_use;
	while(NXY->next!=NULL)
	{
		NXY=NXY->next;
		X2=NXY->x;
		Y2=NXY->y;
		no_use2=NXY->no_use;
		line((int)X1,(int)Y1,(int)X2,(int)Y2);
		X1=X2;
		Y1=Y2;
		no_use1=no_use2;
	}
	return TRUE;
}

bool Graph_2D::UnDraw(void)
{
	if(Pre_Drawed==FALSE) return FALSE;
	if(New_Point_XY_H.n==0 || New_Point_XY_H.n==1)
		return FALSE;
	double X1,Y1,no_use1,X2,Y2,no_use2;
	setcolor(Back_Color);
	NXY=New_Point_XY_H.next;
	X1=NXY->x;
	Y1=NXY->y;
	no_use1=NXY->no_use;
	while(NXY->next!=NULL)
	{
		NXY=NXY->next;
		X2=NXY->x;
		Y2=NXY->y;
		no_use2=NXY->no_use;
		line((int)X1,(int)Y1,(int)X2,(int)Y2);
		X1=X2;
		Y1=Y2;
		no_use1=no_use2;
	}
	return TRUE;
}

bool Graph_2D::Aftr_Draw(void)
{
	if(Pre_Drawed==FALSE) return FALSE;
	if(New_Point_XY_H.n=0) return FALSE;
	delete(New_Point_XY_H.next);
	New_Point_XY_H.n=0;
	New_Point_XY_H.x=Init_Point_XY_H.x;
	New_Point_XY_H.y=Init_Point_XY_H.y;
	New_Point_XY_H.no_use=NO_USE;
	New_Point_XY_H.next=NULL;
	New_Point_XY_H.previous=NULL;
	Aftr_Drawed=TRUE;
	return TRUE;
}

bool Graph_2D::ReSet_Point(int n, double x, double y)
{
	IXY=&Init_Point_XY_H;
	IXY=IXY->next;
	if(FALSE==Check_Input_N(n) || Init_Point_XY_H.n==0)
		return FALSE;
	while(IXY->n!=n) IXY=IXY->next;
	IXY->x=x;
	IXY->y=y;
	return TRUE;
}

bool Graph_2D::Get_Point(int n, double &x, double &y)
{
	IXY=&Init_Point_XY_H;
	IXY=IXY->next;
	if(FALSE==Check_Input_N(n) || Init_Point_XY_H.n==0)
		return FALSE;
	while(IXY->n!=n) IXY=IXY->next;
	x=IXY->x;
	y=IXY->y;
	return TRUE;
}

void Graph_2D::Insert_Point(int n, double x, double y)
{
	Point_XY *temp;
	IXY=&Init_Point_XY_H;
	temp=new(Point_XY);
	temp->n=n;
	temp->x=x;
	temp->y=y;
	temp->no_use=NO_USE;
	Check_Input_N(n);
	if(Init_Point_XY_H.n==0)
	{
		temp->next=NULL;
		temp->previous=NULL;
		Init_Point_XY_H.next=temp;
		Init_Point_XY_H.previous=temp;
		Init_Point_XY_H.n=1;
	}
	else
	{
		while(IXY->next->n!=n && IXY->next!=NULL)
			IXY=IXY->next;
		if(IXY->next==NULL)
		{
			temp->next=NULL;
			IXY->next=temp;
			temp->previous=IXY;
			Init_Point_XY_H.previous=temp;
		}
		else
		{
			temp->next=IXY->next;
			temp->previous=IXY->next->previous;
			IXY->next->previous=temp;
			IXY->next=temp;
		}
		Init_Point_XY_H.n=Init_Point_XY_H.n+1;
		IXY=IXY->next;
		while(IXY->next!=NULL)
		{
			IXY=IXY->next;
			IXY->n=IXY->n+1;
		}
	}
}

void Graph_2D::Set_Point(int n, double x, double y)
{
	Insert_Point(n, x, y);
}

bool Graph_2D::Del_Point(int n)
{
	Point_XY *temp;
	if(FALSE==Check_Input_N(n) || Init_Point_XY_H.n==0)
		return FALSE;
	IXY=&Init_Point_XY_H;
	if(n==1)
	{
		IXY=IXY->next;
		Init_Point_XY_H.n=0;
		Init_Point_XY_H.next=NULL;
		Init_Point_XY_H.previous=NULL;
		delete(IXY);
		return TRUE;
	}
	while(IXY->n!=n) IXY=IXY->next;
	if(IXY->next==NULL)
	{
		Init_Point_XY_H.previous=IXY->previous;
		IXY->previous->next=NULL;
		IXY->previous=NULL;
		delete(IXY);
		return TRUE;
	}
	IXY->previous->next=IXY->next;
	IXY->next->previous=IXY->previous;
	IXY->next=NULL;
	IXY->previous=NULL;
	delete(IXY);
	return TRUE;
}

Graph_2D::~Graph_2D()
{
	delete(Init_Point_XY_H.next);
	delete(New_Point_XY_H.next);
}

bool Graph_2D::Check_Input_N(int &n)
{
	if(n<1)
	{
		n=1;
		return FALSE;
	}
	if(n>Init_Point_XY_H.n)
	{
		n=Init_Point_XY_H.n+1;
		return FALSE;
	}
	return TRUE;
}

////////////////////////// End Define Graph_2D Class ///////////////////////


void main(void)
{
	int gd=VGA, gm=VGAHI;
	initgraph(&gd,&gm,"c:\\tc\\bgi");
	Graph_2D t1(320,240);
	t1.Set_Point(1,50,50);
	t1.Set_Point(2,50,50);
	t1.Pre_Draw();
	t1.Draw();
	getch();
	t1.UnDraw();
	t1.Aftr_Draw();
	exit(0);
}
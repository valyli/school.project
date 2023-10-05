#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <graphics.h>
#include <iostream.h>

int Back_Color=CYAN, Font_Color=WHITE;
char *Bgi_Path[]={"c:\\tc\\bgi"};
int MaxX, MaxY;
int Origin_X, Origin_Y;
int Step=5;

enum Bool {FALSE,TRUE};

struct Point
{
	int x,y,r;
	struct Point *next;
};

Point Head_P;

int P_Num=20;
int R=100;

Bool Init_Screen(int Gdriver, int Gmode)
{
	initgraph(&Gdriver, &Gmode, *Bgi_Path);
	int errorcode=graphresult();
	if(errorcode!=grOk)
	{
		cprintf("Graphics error: %s\n", grapherrormsg(errorcode));
		getch();
		return FALSE;
	}
	MaxX=getmaxx();
	MaxY=getmaxy();
	Origin_X=(int)(MaxX/2.0)+1;
	Origin_Y=(int)(MaxY/2.0)+1;
	setbkcolor(Back_Color);
	setcolor(Font_Color);
	return TRUE;
}

Bool Auto_Init_Screen(void)
{
	int Gdriver, Gmode;
	detectgraph(&Gdriver, &Gmode);
	if(FALSE==Init_Screen(Gdriver, Gmode)) return FALSE;
	return TRUE;
}

void Quit(void)
{
	Point *p1=Head_P.next, *p2;
	while(p1!=NULL)
	{
		p2=p1;
		p1=p1->next;
		delete(p2);
	}
	exit(0);
}

void Count(void)
{
	float x,y,r;
	Point *p;
	for(int i=1; i<=P_Num; i++)
	{
		x=R*cos(i*2*M_PI/P_Num);
		y=R*sin(i*2*M_PI/P_Num);
		r=abs(x);
		if(i==1)
		{
			Head_P.next=new(Point);
			p=Head_P.next;
			p->x=x;
			p->y=y;
			p->r=r;
			p->next=NULL;
			continue;
		}
		p->next=new(Point);
		if(p->next == NULL) Quit();
		p=p->next;
		p->x=x;
		p->y=y;
		p->r=r;
		p->next=NULL;
	}
}

void Draw(void)
{
	if(P_Num==1) exit(0);
	setcolor(Font_Color);
	Point *p;
	p=Head_P.next;
	for(int i=1; i<P_Num; i++)
	{
		circle(Origin_X+p->x, Origin_Y-p->y, p->r);
		p=p->next;
	}
}

void UnDraw(void)
{
	if(P_Num==1) exit(0);
	setcolor(Back_Color);
	Point *p;
	p=Head_P.next;
	for(int i=1; i<P_Num; i++)
	{
		circle(Origin_X+p->x, Origin_Y-p->y, p->r);
		p=p->next;
	}
}

/*void UnDraw(void)
{
	if(P_Num==1) exit(0);
	setcolor(Back_Color);
	Point *p1, *p2;
	p1=Head_P.next;
	for(int i=1; i<P_Num; i++)
	{
		p2=p1->next;
		for(int j=i+1; j<=P_Num; j++)
		{
			line(Origin_X+p1->x, Origin_Y-p1->y,
				Origin_X+p2->x, Origin_Y-p2->y);
			p2=p2->next;
		}
		p1=p1->next;
	}
}
*/

void UnCount(void)
{
	Point *p1=Head_P.next, *p2;
	while(p1!=NULL)
	{
		p2=p1;
		p1=p1->next;
		delete(p2);
	}
//	delete[](Head_P.next);
}

void Input_Chg(int P_Number, int Radius, int F_Color)
{
	if(P_Number<=1) P_Number=2;
	P_Num=P_Number;
	if(Radius<=0) Radius=0;
	R=Radius;
	Font_Color=F_Color;
}

void Frame(void)
{
	setcolor(YELLOW);
	outtextxy(30,450,"ESC-Exit   F1-Help" );
}

void Help(void)
{
	setcolor(YELLOW);
	outtextxy(50,100,"******** Help ********");
	outtextxy(50,120,"** About Button **");
	outtextxy(50,130,"UpKey, DownKey, LeftKey, RightKey, Space");
	outtextxy(50,180,"** Produce by LiJia **");
	getch();
	cleardevice();
}

void main(void)
{
	char key1,key2;
	if(FALSE==Auto_Init_Screen());
	Input_Chg(25,100,RED);
	Frame();
	Count();
	Draw();
	while(1)
	{
		do
		{
			key1=getch();
			if(key1=='\033') Quit();
			if(key1==' ')
			{
				UnDraw();
				UnCount();
				Input_Chg(P_Num, R, ++Font_Color);
				Count();
				Draw();
			}
		}while(key1!='\000');
		key2=getch();
		if(key2=='\73') Help();
		UnDraw();
		UnCount();
		if(key2=='\113') Input_Chg(P_Num, R+Step, Font_Color);
		if(key2=='\115') Input_Chg(P_Num, R-Step, Font_Color);
		if(key2=='\110') Input_Chg(++P_Num,R,Font_Color);
		if(key2=='\120') Input_Chg(--P_Num,R,Font_Color);
		Frame();
		Count();
		Draw();
	}
	UnCount();
}
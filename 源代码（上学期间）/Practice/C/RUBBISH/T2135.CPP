#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <string.h>

int Back_Color=LIGHTGRAY, Font_Color=BROWN;
char *Bgi_Path[]={"d:\\tc\\bgi"};
int MaxX, MaxY;
int Origin_X, Origin_Y;
int Unit_Size=40;
int x1, y1, x2, y2;
float k;

enum Bool {FALSE,TRUE};

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

void Frame(void)
{
	char string[4];
	setcolor(Font_Color);
	outtextxy(int(MaxX/2)-60,10,"Draw Line Program");
	outtextxy(MaxX-150+10,30,"2001-4-6");
	outtextxy(MaxX-150,10,"LiJia, CNU");
	setcolor(DARKGRAY);
	for(int x=40; x<=MaxX; x+=Unit_Size)
	{
		line(x,40,x,MaxY-40);
		setcolor(BLUE);
		line(x,MaxY-40,x,MaxY-40-5);
		setcolor(Font_Color);
		outtextxy(x-10,MaxY-40+3,gcvt(x-Origin_X,4,string));
		setcolor(DARKGRAY);
	}
	setcolor(DARKGRAY);
	for(int y=40; y<=MaxY; y+=Unit_Size)
	{
		line(40,y,MaxX-40,y);
		setcolor(BLUE);
		line(40,y,40+5,y);
		setcolor(Font_Color);
		outtextxy(40-25,y,gcvt(440-y,4,string));
		setcolor(DARKGRAY);
	}
	setcolor(BLUE);
	line(40,MaxY-40+1,MaxX-40,MaxY-40+1);
	line(40,40,40,MaxY-40);
}

void Input_xy(void)
{
	printf("\n-- Input X1,Y1,X2,Y2 --\n");
	printf("X1:");
	scanf("%d",&x1);
	printf("\n");
	printf("Y1:");
	scanf("%d",&y1);
	printf("\n");
	printf("X2:");
	scanf("%d",&x2);
	printf("\n");
	printf("Y2:");
	scanf("%d",&y2);
	printf("\n");
}

void Draw(void)
{
	char t[20];
	sprintf(t,"%d",x1);
	outtextxy(40,MaxY-20,"X1=");
	outtextxy(40+25,MaxY-20,t);
	sprintf(t,"%d",y1);
	outtextxy(110,MaxY-20,"Y1=");
	outtextxy(110+25,MaxY-20,t);
	sprintf(t,"%d",x2);
	outtextxy(180,MaxY-20,"X2=");
	outtextxy(180+25,MaxY-20,t);
	sprintf(t,"%d",y2);
	outtextxy(250,MaxY-20,"Y2=");
	outtextxy(250+25,MaxY-20,t);
	sprintf(t,"%f",k);
	outtextxy(320,MaxY-20,"k=");
	outtextxy(320+25,MaxY-20,t);

}
void mylineD(void)
{
	int x;
	float y;
	if(x1>=x2)
	{
		x=x1;
		x1=x2;
		x2=x;
		y=y1;
		y1=y2;
		y2=y;
	}
	k=float(y2 - y1) / float(x2 - x1);
	setcolor(RED);
	outtextxy(int(MaxX/2)-60+8,30,"By Differential");
	Draw();
	y=y1;
	for(x=x1+Origin_X; x<=x2+Origin_X; x++)
	{
		putpixel(x,Origin_Y-int(y+0.5),RED);
		y=y+k;
	}
}

void mylineB()
{
	int x,y,dx,dy;
	float e;
	dx=x2-x1;
	dy=y2-y1;
	k=dy/dx;
	setcolor(BLUE);
	outtextxy(int(MaxX/2)-60+8,30,"By Bresenham");
	Draw();
	e=-0.5;x=x1;y=y1;
	for(int i=0;i<=dy;i++)
	{
		putpixel(x+40,Origin_Y-y,BLUE);
		y=y+1;
		e=e+k;
		if(e>=0)
		{
			x+=1;
			e-=1;
		}
	}
}

void main(void)
{
	char key='c';
	char key1;
	Origin_X = 40;
	Origin_Y = MaxY-40;
	while(key!='\033')
	{
		Input_xy();
		if(FALSE==Auto_Init_Screen());
		Origin_X = 40;
		Origin_Y = MaxY-40;
		Frame();
		setcolor(YELLOW);
		outtextxy(MaxX-150,MaxY-20,"Press any key...");
		mylineD();
		getch();
		setcolor(Back_Color);
		setfillstyle(1,Back_Color);
		bar(int(MaxX/2)-60+8,30,int(MaxX/2)-60+150,39);
		bar(40,MaxY-20,MaxX,MaxY);
		setcolor(YELLOW);
		outtextxy(MaxX-150,MaxY-20,"Press ESC to exit");
		mylineB();
		key=getch();
		cleardevice();
		closegraph();
	}
	exit(0);
}
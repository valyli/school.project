// Copyright by LiJia
// Computer Partment, CNU
// 3,16,2000

#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <math.h>

enum Bool {FALSE,TRUE};

int Back_Color=CYAN, Font_Color=WHITE;
char *Bgi_Path[]={"d:\\tc\\bgi"};
int MaxX, MaxY;
double Point[4][3]={{0,0,1},{100,0,1},{100,70,1},{0,70,1}};
	//Input old point of Graphics in to matrix
double Paint[4][3]={{0,0,1},{100,0,1},{100,70,1},{0,70,1}};
	//Save the drawing point in this matrix
int Origin_X, Origin_Y;
double Chg_A=3.1415926/180*10;
int Chg_Aed=0;
int Chg_Xed=0, Chg_Yed=0;
int Step=10;

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
	int x, y;
	int scale_x;    			/* x scale		*/
	float scale_y;                        /* y scale		*/
	char scale_s[4];                      /* string of scale	*/

	setcolor(BLUE);
	line(0,40,639,40);
	outtextxy(250,20,"Equation Plotter");
	line(0,440,639,440);
	outtextxy(30,450,"ESC-Exit   F1-Help" );

	setcolor(DARKGRAY);                      /* frame color		*/
	y=50;                                 /* draw x frame 	*/
	while (y<=430)
	{
		line(20,y,620,y);
		y=y+38;
	}
	x=20;                                 /* draw y frame 	*/
	while(x<=620)
	{
		line(x,50,x,430);
		x=x+75;
	}

	setcolor(RED);                        /* axis color		*/
	line( 20,240,620,240);     		/* draw x axis  	*/
	x=20;                   		/* draw x scale 	*/
	scale_x=-360;
	while(x<=620)
	{
		line(x,235,x,245);
		outtextxy(x-10,250,gcvt(scale_x,4,scale_s));
		x=x+75;
		scale_x = scale_x + 90;
	}

	line(320, 50,320,430);            	/* draw y axis  	*/
	y=50;                          	/* draw y scale 	*/
	scale_y=1.0;
	while(y<=430)
	{
		line(315,y,325,y);
		if(fabs(scale_y)>0.1)              /* float abs function	*/
		outtextxy(280,y,gcvt(scale_y,2,scale_s));
		y=y+38;
		scale_y=scale_y-0.2;
	}
}

void Draw()
{
	int i;
//	char scale_s[5];
//	setcolor(WHITE);
	for(i=1;i<=3;i++)
		line((int)(Origin_X+Paint[i-1][0]),(int)(Origin_Y-Paint[i-1][1]),
			(int)(Origin_X+Paint[i][0]),(int)(Origin_Y-Paint[i][1]));
//	outtextxy(100,100,gcvt(i,5,scale_s));
	i--;
	line((int)(Origin_X+Paint[0][0]),(int)(Origin_Y-Paint[0][1]),
		(int)(Origin_X+Paint[i][0]),(int)(Origin_Y-Paint[i][1]));

}

void Chg_AXY(int Type, int Direct)
{
	if(Type==0) Chg_Aed++;
	if(Type==1)
	{
		if(Direct==1) Chg_Xed++;
		if(Direct==-1) Chg_Xed--;
	}
	if(Type==2)
	{
		if(Direct==1) Chg_Yed++;
		if(Direct==-1) Chg_Yed--;
	}
	for(int i=0; i<=3; i++)
	{
		Paint[i][0]=(Point[i][0]*cos(Chg_A*Chg_Aed)
			-Point[i][1]*sin(Chg_A*Chg_Aed))
			+Chg_Xed*Step;
		Paint[i][1]=(Point[i][0]*sin(Chg_A*Chg_Aed)
			+Point[i][1]*cos(Chg_A*Chg_Aed))
			+Chg_Yed*Step;
	}
}

void help(void)
{
	setcolor(YELLOW);
	outtextxy(50,100,"******** Help ********");
	outtextxy(50,120,"** About Button **");
	outtextxy(50,130,"UpKey, DownKey, LeftKey, RightKey");
	outtextxy(50,180,"** Produce by LiJia **");
	getch();
	cleardevice();
}

void main(void)
{
	char key1,key2;
//	char Press='e';
	if(FALSE==Auto_Init_Screen());
	Frame();
	setcolor(WHITE);
	Draw();
/*	while(Press!='q')
	{
		Press=getch();
		setcolor(BLACK);
		Draw();
		if(Press==' ') Chg_AXY(0,1);
		if(Press=='d') Chg_AXY(1,1);
		if(Press=='a') Chg_AXY(1,-1);
		if(Press=='w') Chg_AXY(2,1);
		if(Press=='s') Chg_AXY(2,-1);
		setcolor(WHITE);
		Draw();
	}
*/
	while(1)
	{
		do
		{
			key1=getch();
			if(key1=='\033') exit(0);
			if(key1==' ')
			{
				setcolor(BLACK);
				Draw();
				Frame();
				Chg_AXY(0,1);
				setcolor(WHITE);
				Draw();
			}
		}while(key1!='\000');
		key2=getch();
		if(key2=='\73') help();
		setcolor(BLACK);
		Draw();
		Frame();
		if(key2=='\115') Chg_AXY(1,1);
		if(key2=='\113') Chg_AXY(1,-1);
		if(key2=='\110') Chg_AXY(2,1);
		if(key2=='\120') Chg_AXY(2,-1);
		setcolor(WHITE);
		Draw();
	}
}

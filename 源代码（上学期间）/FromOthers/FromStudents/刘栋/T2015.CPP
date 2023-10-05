#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

#define N 5
#define M 10

int x_org=320;
int y_org=240;

float p[N+2][2];

float q1[N][2]={{0.0,0.0},{0.4,0.08},{0.8,0.32},{1.2,0.72},{1.6,1.28}};

void init()
{
   int gdriver = VGA, gmode = VGAHI,errorcode;
   initgraph(&gdriver,&gmode, "d:\\tc\\bgi");
   /* read result of initialization */
   errorcode = graphresult();
   if (errorcode != grOk)  /* an error occurred */
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1);             /* return with error code */
   }
   setbkcolor(CYAN);
   setcolor(BLUE);
}

void frame()
{
  int x,y;                              /* work variables 	*/
  int x_max,y_max;                      /* max number of x & y  */
  int scale_x;    			/* x scale		*/
  float scale_y;                        /* y scale		*/
  char scale_s[4];                      /* string of scale	*/

  x_max=639;                            /* VGA max number of x  */
  y_max=479;                            /* VGA max number of y  */

  rectangle(0,0,x_max,y_max);   	/* draw rectangle 	*/
  line(0,40,639,40);
  outtextxy(250,20,"pao wu yang tiao qu xian");
  line(0,440,639,440);
  outtextxy(30,450,"E-exit   H-help" );

  setcolor(GREEN);                      /* frame color		*/
  y=50;                                 /* draw x frame 	*/
  while (y<=430)
  { line(20,y,620,y);
    y=y+10;
  }
  x=20;                                 /* draw y frame 	*/
  while (x<=620)
  { line(x,50,x,430);
    x=x+10;
  }

  setcolor(RED);                        /* axis color		*/
  line(20,240,620,240);     		/* draw x axis  	*/
  x = 20;                   		/* draw x scale 	*/
  scale_x = -3;
  while (x <= 620)
  {
    line(x,235,x,245);
    outtextxy(x-10,250,gcvt(scale_x,4,scale_s));
    x=x+100;
    scale_x = scale_x + 1;
  }

  line(320, 50,320,430);            	/* draw y axis  	*/
  line(315,50,325,50);
  line(315,430,325,430);
  y = 140;                          	/* draw y scale 	*/
  scale_y = 1;
  while (y <= 430)
  {
    line(315,y,325,y);
    if (fabs(scale_y)>0.1)              /* float abs function	*/
      outtextxy(280,y,gcvt(scale_y,2,scale_s));
    y=y+100;
    scale_y = scale_y - 1;
  }
}

void paowu(float q[N][2])
{
  int i,j;
  float px,py;
  int ix,iy;
  float t,t2,t3;
  float f1,f2,f3,f4;
  char msg[10];

  setcolor(BLUE);
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
  moveto(ix,iy);
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
      lineto(ix,iy);
    }
    ix = (int)(p[i+2][0]*(100)+x_org);
    iy = (int)(p[i+2][1]*(-100)+y_org);
    lineto(ix,iy);
//    circle(ix,iy,2);
//    sprintf(msg, " (%.2f, %.2f)", p[i+2][0], p[i+2][1]);
//    outtextxy(ix+15, iy+15, msg);
  }
}

void help()
{
   outtextxy(25,40,"This program draw a parsp line");
   outtextxy(25,70,"Press E to exit this program");
}

void main()
{
  char ch;

  init();
  frame();
  paowu(q1);
  while(1)
  {
    ch=getch();

    if((ch=='e') || (ch=='E')) break;
    if((ch=='h') || (ch=='H')) help();
  }
  closegraph();
  exit(0);
}
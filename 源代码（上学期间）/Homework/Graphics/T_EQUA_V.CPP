/*
    Only For Backform

    Source Code From:
    t_equatn.c
    Equation Plotter
    This program is a demonstration of Equation Plotter.
    Use VGA.
    Ge qing-ping   97.9.14 pm 4:00

    Change By LiJia
      form .c to .cpp (to classes)
*/

#include <graphics.h>
#include <stdlib.h>
//#include <iomanip.h>
#include <conio.h>
#include <math.h>
#define PI 3.14159

//for InitScreen
#define Auto -1
#define BGI_PATH "c:\\tc30\\bgi"
//end InitScreen
void InitScreen(int Gdriver,                 //if Auto run DETECT
		int Gmode,
		int BackColor=BLACK,
		int FontColor=WHITE)
{
 //  void far detectgraph(int far *graphdriver, int far *graphmode);
  // int gdriver = Gdriver, gmode = Gmode, errorcode;
   if(Gdriver==Auto) Gdriver=DETECT;
   initgraph(&Gdriver,&Gmode,BGI_PATH);
   /* read result of initialization */
   int errorcode = graphresult();
   if (errorcode != grOk)  /* an error occurred */
   {
      cprintf("Graphics error: %s\n", grapherrormsg(errorcode));
      cprintf("Press any key to halt:");
      getch();
      exit(1);             /* return with error code */
   }
   setbkcolor(BackColor);
   setcolor(FontColor);
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
  outtextxy(250,20,"Equation Plotter");
  line(0,440,639,440);
  outtextxy(30,450,"E-exit   H-help" );

  setcolor(GREEN);                      /* frame color		*/
  y=50;                                 /* draw x frame 	*/
  while (y<=430)
  { line(20,y,620,y);
    y=y+38;
  }
  x=20;                                 /* draw y frame 	*/
  while (x<=620)
  { line(x,50,x,430);
    x=x+75;
  }

  setcolor(RED);                        /* axis color		*/
  line( 20,240,620,240);     		/* draw x axis  	*/
  x = 20;                   		/* draw x scale 	*/
  scale_x = -360;
  while (x <= 620)
  {
    line(x,235,x,245);
    outtextxy(x-10,250,gcvt(scale_x,4,scale_s));
    x=x+75;
    scale_x = scale_x + 90;
  }

  line(320, 50,320,430);            	/* draw y axis  	*/
  y = 50;                          	/* draw y scale 	*/
  scale_y = 1.0;
  while (y <= 430)
  {
    line(315,y,325,y);
    if (fabs(scale_y)>0.1)              /* float abs function	*/
      outtextxy(280,y,gcvt(scale_y,2,scale_s));
    y=y+38;
    scale_y = scale_y -0.2;
  }

}

void main()
{
   InitScreen(VGA,VGAHI,GREEN,BLUE);
   frame();
   //closegraph();
}

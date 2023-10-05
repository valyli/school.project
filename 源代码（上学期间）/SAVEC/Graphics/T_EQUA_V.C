/*
    t_equatn.c
    Equation Plotter
    This program is a demonstration of Equation Plotter.
    Use VGA.
    Ge qing-ping   97.9.14 pm 4:00
*/

#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#define PI 3.14159

void init();
void frame();
void drawequation();

void main()
{
   init();
   frame();
   drawequation();
   closegraph();
}

/*            ******* init *******             */
void init()
{
   int gdriver = VGA, gmode = VGAHI,errorcode;
   initgraph(&gdriver,&gmode, "c:\\tc30\\bgi");
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
} /* end of init() */


/*            ******* frame *******             */
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

} /* end of frame() */

/*            ******* help *******             */
void help()
{
   outtextxy(25,40,"This program is a demonstration of Equation Plotter");
   outtextxy(25,70,"Press E to exit this program");
} /* end of help() */

/*            ******* draw equation *******             */
void drawequation()
{
  int     color,i,j  	 ;		/* woke vabriables	*/
  int     xi,yi          ;		/* int x,y   ,for draw  */
  float   xf,yf          ; 		/* float x,y ,for count */
  float   x_relative     ;              /* relative value of x  */
  float   x_arc          ;    		/* arc of x		*/
  char    ch		 ;

  outtextxy(480,60,"y = sin x ");
  xf = 20.0;                		/* draw from 20 to 620	*/
  while (xf <= 620.0 )
  {
     for (i=1;i<= 20000;i++)  ;           /* delay time		*/
     x_relative = xf-320.0;             /* 320 means x=0	*/
     x_arc=2.0*PI/300.0*x_relative;  	/* count arc		*/
					/* 2*PI=360=300 points  */
     yf = sin(x_arc);                   /* count sin x      	*/
     yf = (-yf)*190.0+240.0;            /* '-' means Display's plus
					   is diffrent from axis'plus */
					/* 240 means y=0 ; 	*/
					/* 190 means 1/2 Vpp 	*/
     xi = (int)(xf);   			/* change float to int 	*/
     yi = (int)(yf); 		        /* change float to int  */
     putpixel(xi,yi,RED);               /* draw equation	*/
     xf = xf+0.1;
  }
     while(1)
     { ch=getch();
       if ((ch=='e')||(ch=='E'))        /* exit 		*/
	 break;
       if ((ch=='h')||(ch=='H'))        /* help 		*/
	 help();
     }
} /* end drawequation() */

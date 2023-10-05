#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#define PI 3.14159
#define step 4

typedef struct
{int x,y;
}pos;

typedef struct
{pos A,B,C,D;
}Ra;

void init();
void frame();
void rectangle(Ra);
void draw(Ra &);
void W(Ra &);
void S(Ra &);
void A(Ra &);
void D(Ra &);
void rotate(pos &,pos,double);
void L(Ra &);
void R(Ra &);
void help();

Ra r;

void main()
{
   //printf("Please input the position of point A:");
   //scanf("%d,%d",&r.A.x,&r.A.y);
   //printf("Please input the position of point B:");
   //scanf("%d,%d",&r.B.x,&r.B.y);
   //printf("Please input the position of point C:");
   //scanf("%d,%d",&r.C.x,&r.C.y);
   //printf("Please input the position of point D:");
   //scanf("%d,%d",&r.D.x,&r.D.y);
   r.A.x=200;  r.A.y=200;  r.B.x=230; r.B.y=200;
   r.C.x=200;  r.C.y=230;  r.D.x=230; r.D.y=230;

   printf("Initating,wait...");

   init();
   frame();
   draw(r);
   closegraph();
}

void rectangle(Ra r)
{
    line(r.A.x, r.A.y, r.B.x, r.B.y);
    line(r.A.x, r.A.y, r.C.x, r.C.y);
    line(r.B.x, r.B.y, r.D.x, r.D.y);
    line(r.C.x, r.C.y, r.D.x, r.D.y);

}

/*            ******* init *******             */
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
  int scale_x;    			/* x scale		*/
  float scale_y;                        /* y scale		*/
  char scale_s[4];                      /* string of scale	*/

  line(0,40,639,40);
  outtextxy(250,20,"Rotating Rectangle");
  line(0,440,639,440);
  setcolor(RED);
  outtextxy(30,450,"W-Up  S-Down  A-Left  D-Right  L-Turn Left  R-Turn Right E-exit  H-help" );

  line( 20,240,620,240);     		/* draw x axis  	*/
  x = 20;                   		/* draw x scale 	*/
  scale_x = -320;
  while (x <= 620)
  {
    line(x,235,x,245);
    outtextxy(x-10,250,gcvt(scale_x,4,scale_s));
    x=x+75;
    scale_x = scale_x + 80;
  }

  line(320, 50,320,430);            	/* draw y axis  	*/
  y = 50;                          	/* draw y scale 	*/
  scale_y =240;
  while (y <= 430)
  {
    line(315,y,325,y);
    if (fabs(scale_y)>0.1)              /* float abs function	*/
      outtextxy(280,y,gcvt(scale_y,3,scale_s));
    y=y+38;
    scale_y = scale_y-48;
  }

}

void W (Ra &r)
{
   r.A.y-=step;
   r.B.y-=step;
   r.C.y-=step;
   r.D.y-=step;

}

void S (Ra &r)
{
   r.A.y+=step;
   r.B.y+=step;
   r.C.y+=step;
   r.D.y+=step;

}

void A (Ra &r)
{
   r.A.x-=step;
   r.B.x-=step;
   r.C.x-=step;
   r.D.x-=step;

}

void D (Ra &r)
{
   r.A.x+=step;
   r.B.x+=step;
   r.C.x+=step;
   r.D.x+=step;

}

void brmul(double *a,double *b,int m,int n,int k,double *c)
  { int i,j,l,u;
    for (i=0; i<=m-1; i++)
    for (j=0; j<=k-1; j++)
      { u=i*k+j; c[u]=0.0;
	for (l=0; l<=n-1; l++)
	  c[u]=c[u]+a[i*n+l]*b[l*k+j];
      }

  }

void rorate(pos &p,pos base,double arc)
{
     double position[3],T[3][3];

     position[0]=p.x;
     position[1]=p.y;
     position[2]=1;

     T[][]
}



void L(Ra &r)
{

}

void R(Ra &r)
{

}

void draw(Ra &r)
{
    char ch;

    setcolor(BLUE);
    rectangle(r);

    while(1)
     { ch=getch();
       if ((ch=='e')||(ch=='E'))        /* exit 		*/
	 break;
       setcolor(CYAN);
       rectangle(r);

       if ((ch=='w')||(ch=='W'))        /* up   		*/
	  W(r);
       if ((ch=='s')||(ch=='S'))        /* down 		*/
	  S(r);
       if ((ch=='a')||(ch=='A'))        /* left 		*/
	  A(r);
       if ((ch=='d')||(ch=='D'))        /* right		*/
	  D(r);
       setcolor(BLUE);
       frame();
       setcolor(BLUE);
       rectangle(r);
       if ((ch=='h')||(ch=='H'))        /* help 		*/
	 help();
     }
}

void help()
{
   outtextxy(25,40,"Press W to move the rectangle up and S to down, A to left, D to right");
   outtextxy(25,50,"Press L to turn left and press R to turn right");
   outtextxy(25,60,"Press E to exit this program");
}
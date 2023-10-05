#include <math.h>
#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include <conio.h>
#define IE 10
#define JE 10
border_s(ia,is,js,ds,li,lj,ln,lp)
unsigned char ia[IE][JE];
int is,js,ds,li[],lj[],ln,*lp;
{
  static char ip[]={0,-1,-1,-1,0,1,1,1},
	      jp[]={1,1,0,-1,-1,-1,0,1};
  int i,j,iw,jw,nb,n,nc;
  i=iw=is; j=jw=js;
  n=(ds+4)&7; ds=-1; nb=-1;
  nc=ia[i-1][j-1]+ia[i-1][j]+ia[i-1][j+1]+ia[i][j-1]+ia[i][j+1]+ia[i+1][j-1]+ia[i+1][j]+ia[i+1][j+1];
  if(nc>0)
  { do {
       li[*lp]=i=iw; lj[*lp]=j=jw; ia[iw][jw]=3;
       (*lp)++;
	n=(n+4)&7;
	do {
	 n=(n+1)&7;
	 iw=i+ip[n]; jw=j+jp[n];
	 }while(ia[iw][jw]==0);
	 if(ds<0)
	 { if(nb<0) nb=n;
	   else ds=nb;
	   }
	   if(*lp>=ln)
	   { *lp=-1;
	     printf("error");
	     }
	   } while((i!=is)||(j!=js)||(n!=ds));
	   }
	   else {
	   li[*lp]=is; lj[*lp]=js;ia[i][j]=2;
	   (*lp)++;
	   }
	   li[*lp]=lj[*lp]=-1;
	   (*lp)++;
	  printf("error");
	}

void border(ia,li,lj,ln,lp)
unsigned char ia[IE][JE];
int li[],lj[],ln,*lp;
{
   int i,j,il,jl,ds,nc;
   il=IE-1;jl=JE-1;*lp=0;
   for(i=0;i<IE;i++)
     ia[i][0]=ia[i][jl]=0;
   for(j=0;j<JE;j++)
     ia[0][j]=ia[il][j]=0;
   for(i=1;i<il;i++)
     { for(j=1;j<jl;j++)
       { if(ia[i][j]==1)
	 { nc=ia[i][j+1]&ia[i-1][j]&ia[i][j-1]&ia[i+1][j];
	   if(nc==0)
	   { if(ia[i+1][j]==0) ds=6;
	     else if(ia[i][j-1]==0) ds=4;
	     else if(ia[i-1][j]==0) ds=2;
	     else if(ia[i][j+1]==0) ds=0;
	     border_s(ia,i,j,ds,li,lj,ln,lp);
	     }
	   }
	 }
       }
       for(i=1;i<il;i++)
       { for(j=1;j<jl;j++)
	 { if(ia[i][j]>0) ia[i][j]=1;
	  }
	 }
     }
int main(void)
{
   /* request auto detection */
   int gdriver = DETECT, gmode, errorcode;
   //int xmax, ymax;

   /* initialize graphics and local variables */
   initgraph(&gdriver, &gmode, "c:\\tc\\bgi");

   /* read result of initialization */
   errorcode = graphresult();
   /* an error occurred */
   if (errorcode != grOk)
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1);
   }
   setbkcolor(2);
   setcolor(getmaxcolor());
   unsigned char ia[IE][JE]={3,3,3,3,3,3,3};
   int li[]={1,2,3,4,4,3,2,1,-1},lj[]={2,1,1,2,3,4,4,3,-1},ln=10;
   int *lp;
   border(ia,li,lj,ln,lp);

  /* clean up */
   getch();
   closegraph();
   return 0;
}

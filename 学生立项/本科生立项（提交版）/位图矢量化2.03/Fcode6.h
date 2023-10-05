/*  FCODE6.CPP     2001.8.17
    Ge qing-ping
    main() - fcode() - border() - border_s()
    Write fcode() function.
    Use struct code to replays li,lj,ln,lp
*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Plotter.h"

#define IE 800 // image high (hang)
#define JE 800 // image width(lie )
#define N 10000 // freeman code length

/*struct code_struct
{ int x;
  int y;
};
*/
void border_s(unsigned char ia[IE][JE],int is,int js
			  ,int ds,int li[],int lj[],int ln, int* lp)
{
  static char ip[]={0,-1,-1,-1,0,1,1,1},     // X increase
	      jp[]={1,1,0,-1,-1,-1,0,1};     // Y increase
  int i,j,iw,jw,nb,n,nc;
  i=iw=is; j=jw=js;
  n=(ds+4)&7; ds=-1; nb=-1;
  nc=ia[i-1][j-1]+ia[i-1][j]+ia[i-1][j+1]    // calculate nc
    +ia[i  ][j-1]             +ia[i][j+1]
    +ia[i+1][j-1]+ia[i+1][j]+ia[i+1][j+1];
  if(nc>0)                 // if nc < 0 then it is isolated point,pass.
  { do                     // if nc > 0 then it is not isolated,process it.
    {  li[*lp]=i=iw;
       lj[*lp]=j=jw;
       ia[iw][jw]=3;       // set the start point to 3.
       (*lp)++;
       n=(n+4)&7;
/*  search the next point  */
       do
       { n=(n+1)&7;        // turn around
	 iw=i+ip[n]; jw=j+jp[n];
       }while(ia[iw][jw]==0);
/*  memorize direction     */
       if(ds<0)
       { if(nb<0) nb=n;
	 else ds=nb;
	}
/*  border code length error */
       if(*lp>=ln)
       { *lp=-1;
	 goto error;
       }
    } while((i!=is)||(j!=js)||(n!=ds)); // not the start point.
  }
  else      /* 4.delete the isolated point,mark it to 2.*/
  {  li[*lp]=is; lj[*lp]=js;ia[i][j]=2;
     (*lp)++;
  }
  li[*lp]=lj[*lp]=-1;  	 // 7. write end flag -1 into border code.
  (*lp)++;
  //printf("\n\nStart point is (%d,%d)\n",is,js);
  error:;
} /* end border_s() */

void border(unsigned char ia[IE][JE],int li[],int lj[],
			int ln,int* lp)
{
   int i,j,il,jl,ds,nc;
   il=IE-1;jl=JE-1;*lp=0;
/*  1 set the edge of image to 0 */
   for(i=0;i<IE;i++)            // hang
     ia[i][0]=ia[i][jl]=0;
   for(j=0;j<JE;j++)            // lie
     ia[0][j]=ia[il][j]=0;
/*   2.search the start point of border */
   for(i=1;i<il;i++)            // X  (hang)
    {for(j=1;j<jl;j++)          // Y  (lie)
       { if(ia[i][j]==1)        // if value is 1,it my be the start point.
	 { nc=ia[i][j+1]&ia[i-1][j]&ia[i][j-1]&ia[i+1][j];
	   if(nc==0)  // 5.nc is 0 means one direction is 0,it is border.
	   { if(ia[i+1][j]==0) ds=6;     //           ia[i-1][j]
	     else if(ia[i][j-1]==0) ds=4;// ia[i][j-1]     *    ia[i][j+1]
	     else if(ia[i-1][j]==0) ds=2;//           ia[i+1][j]
	     else if(ia[i][j+1]==0) ds=0;
		    // 3.define the direction of searching.

	     border_s(ia,i,j,ds,li,lj,ln,lp); // call subroutine border_s()
	   }// ia is image array
	 }  // i,j is the start point.
       }    // li,lj is the line code,ln is it's length,lp is it's pointer.
   }
   for(i=1;i<il;i++)
      for(j=1;j<jl;j++)
	 if(ia[i][j]>0) ia[i][j]=1;  // convert image to binary image(0&1)
				     // delete isolated point 2
				     // delete start point 3
} /* end border() */

void searchcode(unsigned char ia[IE][JE], Coordinates code[N])
{
   int li[N]={0}, lj[N]={0}, ln=N;    	// ln is length
   int *lp;          			// line code pointer

   lp = new int;
   *lp = 0;
   border(ia,li,lj,ln,lp);
   for (int i=0;i<N;i++)
   { 
	 code[i].x=li[i];
     code[i].y=lj[i];
   }
} /* end serchcode() */

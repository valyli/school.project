#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define ERROR 0
#define OK 1
typedef int Status;

typedef struct {int x;int y; }PosType;
typedef struct
{  int       ord;        //ÎÍ¨µÀ¿éÔÚÂ·¾¶ÉÏµÄ"ĞòºÅ"
   PosType  seat;       //¡ÎÍ¨µÀ¿éÔÚÃÔ¹¬ÖĞµÄ"×ø±êÎ»ÖÃ"
   int       di;        // ¡Î´Ó´ËÍ¨µÀ¿é×ßÏòÏÂÒ»Í¨µÀ¿éµÄ"·½Ïò"
}SElemType;             //¡ÎÕ»µÄÔªËØÀàĞÍ
typedef int* MazeType;

typedef struct
{SElemType  *base;
 SElemType  *top;
}SqStack;

static int maze[20][20];
static int endmaze[20][20];
int m,n;

Status InitStack(SqStack &s)
{s.base=(SElemType *)malloc(100*sizeof(SElemType));
 s.top=s.base;
}
Status GetTop(SqStack s, SElemType &e)
{ if(s.top==s.base) return ERROR;
  e=*(s.top-1);
  return OK;
}
Status Push(SqStack &s,SElemType e)
{*s.top++=e;
// printf("%d------%d,%d--%d\n",e.ord,e.seat.x,e.seat.y,e.di); getche();
 return OK;
}
Status Pop(SqStack &s,SElemType &e)
{ if(s.top==s.base) return ERROR;
  e=*(--s.top);
  return OK;
}
Status StackEmpty(SqStack s)
{ if(s.top==s.base) return OK;
  else return ERROR;
}
Status Pass(PosType seat)
{if(maze[seat.x][seat.y]==0) return OK;
 else return ERROR;
}
void FootPrint(PosType seat)
{maze[seat.x][seat.y]=2;  //step in
}
void MarkPrint(PosType seat)
{maze[seat.x][seat.y]=99;
}
void found(SqStack &s)
{SElemType e;
  while(!StackEmpty(s))
   {Pop(s,e);
    endmaze[e.seat.x][e.seat.y]=e.ord;
   }
}
Status compare(PosType one,PosType two)
{ if(one.x==two.x &&one.y==two.y) return OK; else return ERROR; }

void NextPos(PosType &pos, int di)
{switch(di)
 {case 1: pos.y=pos.y+1; break;
  case 2: pos.x=pos.x+1; break;
  case 3: pos.y-=1; break;
  case 4: pos.x-=1;
 }
}
Status MazePath (PosType start, PosType end)
{// ¡ÎÈôÃÔ¹¬mazeÖĞ´æÔÚ´ÓÈë¿Ústartµ½³ö¿ÚendµÄÍ¨µÀ,ÔòÇóµÃÒ»Ìõ´æ·ÅÔÚÕ»ÖĞ
 // ¡Î(´ÓÕ»µ×µ½Õ»¶¥),²¢·µ»ØTRUE;·ñÔò·µ»ØFALSE
 SqStack S; PosType curpos;
 int curstep; SElemType e;
 InitStack(S); curpos = start;    // ¡ÎÉè¶¨"µ±Ç°Î»ÖÃ"Îª"Èë¿ÚÎ»ÖÃ"
 curstep = 1;                     // ¡ÎÌ½Ë÷µÚÒ»²½
 do
 {if(Pass(curpos))
   {                   //¡Îµ±Ç°Î»ÖÃ¿ÉÒÔÍ¨¹ı,¼´ÊÇÎ´Ôø×ßµ½¹ıµÄÍ¨µÀ¿é
       FootPrint(curpos);               //¡ÎÁôÏÂ×ã¼£
       e.ord=curstep;     e.seat.x=curpos.x;
       e.seat.y=curpos.y; e.di=1;
       Push(S,e);                       //¡Î¼ÓÈëÂ·¾¶
       if(compare(curpos,end)) {found(S); return(OK);}    //¡Îµ½´ïÖÕµã(³ö¿Ú)
       NextPos(curpos,1);      //¡ÎÏÂÒ»Î»ÖÃÊÇµ±Ç°Î»ÖÃµÄ¶«ÁÚ
       curstep ++;                      //¡ÎÌ½Ë÷ÏÂÒ»²½
   }//if
  else    //µ±Ç°Î»ÖÃ²»ÄÜÍ¨¹ı
   {if(!StackEmpty(S))
	{ Pop(S,e);
	  while (e.di== 4&&!StackEmpty(S))
	    { MarkPrint(e.seat);   Pop(S,e);}   //ÁôÏÂ²»ÄÜÍ¨¹ıµÄ±ê¼Ç,²¢ÍË»ØÒ»²½
	  if(e.di<4)
	   { e.di++; curstep=e.ord+1;
	     Push (S,e);            //¡Î»»ÏÂÒ»¸ö·½ÏòÌ½Ë÷
	     curpos.x=e.seat.x; curpos.y=e.seat.y;
	     NextPos(curpos, e.di); //¡ÎÉè¶¨µ±Ç°Î»ÖÃÊÇ¸ÃĞÂ·½ÏòÉÏµÄÏàÁÚ¿ì
	   }//if
	}//if
   }//else
  }while(!StackEmpty(S));
 return(ERROR);
}//MazePath
void main()
{FILE *fp;
 PosType start,end;
 int i,j;
 fp=fopen("a:ex2_7.dat","rb");
 fscanf(fp,"%d%d",&m,&n);
 fscanf(fp,"%d%d",&start.y,&start.x);
 fscanf(fp,"%d%d",&end.y,&end.x);
 for(i=1; i<=n; i++)
  for(j=1; j<=m; j++)
   fscanf(fp,"%d",&maze[i][j]);
 fclose(fp);
 for(i=1; i<=n; i++) maze[i][0]=1;
 for(i=0; i<20; i++) maze[0][i]=1;
 for(i=1; i<=n; i++) for (j=m+1; j<20; j++) maze[i][j]=1;
 for(i=n+1; i<20; i++) for (j=0; j<20; j++) maze[i][j]=1;
 for(i=0; i<n; i++)
  {for(j=0; j<m; j++)  printf("%d ",maze[i][j]);
   printf("\n");
  }      getche();
 MazePath(start,end);
 printf("\n");
 for(i=1; i<=n; i++)
  {for (j=1; j<=m; j++)
    if(endmaze[i][j]) printf("%3d",endmaze[i][j]);
    else printf("%3d",0);
   printf("\n");
  }
}




#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define ERROR 0
#define OK 1
typedef int Status;

typedef struct {int x;int y; }PosType;
typedef struct
{  int       ord;        //�ͨ������·���ϵ�"���"
   PosType  seat;       //��ͨ�������Թ��е�"����λ��"
   int       di;        // �δӴ�ͨ����������һͨ�����"����"
}SElemType;             //��ջ��Ԫ������
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
{// �����Թ�maze�д��ڴ����start������end��ͨ��,�����һ�������ջ��
 // ��(��ջ�׵�ջ��),������TRUE;���򷵻�FALSE
 SqStack S; PosType curpos;
 int curstep; SElemType e;
 InitStack(S); curpos = start;    // ���趨"��ǰλ��"Ϊ"���λ��"
 curstep = 1;                     // ��̽����һ��
 do
 {if(Pass(curpos))
   {                   //�ε�ǰλ�ÿ���ͨ��,����δ���ߵ�����ͨ����
       FootPrint(curpos);               //�������㼣
       e.ord=curstep;     e.seat.x=curpos.x;
       e.seat.y=curpos.y; e.di=1;
       Push(S,e);                       //�μ���·��
       if(compare(curpos,end)) {found(S); return(OK);}    //�ε����յ�(����)
       NextPos(curpos,1);      //����һλ���ǵ�ǰλ�õĶ���
       curstep ++;                      //��̽����һ��
   }//if
  else    //��ǰλ�ò���ͨ��
   {if(!StackEmpty(S))
	{ Pop(S,e);
	  while (e.di== 4&&!StackEmpty(S))
	    { MarkPrint(e.seat);   Pop(S,e);}   //���²���ͨ���ı��,���˻�һ��
	  if(e.di<4)
	   { e.di++; curstep=e.ord+1;
	     Push (S,e);            //�λ���һ������̽��
	     curpos.x=e.seat.x; curpos.y=e.seat.y;
	     NextPos(curpos, e.di); //���趨��ǰλ���Ǹ��·����ϵ����ڿ�
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




#include<stdio.h>                  //Pratice P18 2.22
#include<stdlib.h>
#include<conio.h>
#define LEN sizeof(LNode)

typedef int ElemType;
typedef struct LNode
{ElemType data;
 struct LNode *next;
};
typedef LNode *LinkList;

void creat_list(LinkList L)
{int i;
 LinkList p;
 p=L;
 for(i=0;i<=9;i++)
 {p->next=(LinkList)malloc(LEN);
  p=p->next;
  p->data=i;
 }
 p->next=NULL;
 return;
}

void back_list(LinkList L)
{LinkList p,p1,p2;
 p=L->next;
 p1=p->next;
 p->next=NULL;
 while(1)
 {p2=p1->next;
  p1->next=p;
  p=p1;
  p1=p2;
  if(p2==NULL) break;
 }
 L->next=p;
 return;
}

void print_list(LinkList L)
{LinkList p;
 p=L->next;
 while(p!=NULL)
 {cprintf("%d\n\r",p->data);
  p=p->next;
 }
}

void main(void)
{LinkList L;
 clrscr();
 L=(LinkList)malloc(LEN);
 creat_list(L);
 window(1,1,40,25);
 gotoxy(1,1);cprintf("The list is:\n\r");
 print_list(L);
 getch();
 back_list(L);
 window(40,1,80,25);
 gotoxy(1,1);cprintf("The back forward list is:\n\r");
 print_list(L);
 getch();
}
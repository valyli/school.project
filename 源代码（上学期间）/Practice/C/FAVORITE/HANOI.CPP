#include<stdio.h>
#include<stdlib.h>
#include<process.h>
void move(char x,char y)
{
 printf("%c-->%c\n",x,y);
}
void hanoi(int n,char one,char two,char three)
{
 if(n==1)move(one,three);
 else
 {
  hanoi(n-1,one,three,two);
  move(one,three);
  hanoi(n-1,two,one,three);
 }
}
void main()
{
 int m;
 system("cls");
 printf("Input the number of diskes:");
 scanf("%d",&m);
 printf("The step to moving %3d diskes:\n",m);
 hanoi(m,'A','B','C');
}


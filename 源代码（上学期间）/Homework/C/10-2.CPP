#include<stdio.h>
#include<string.h>
void main()
{char p1[20],p2[20],p3[20];
 char *a[3]={p1,p2,p3},*p;
 int i,j;
 printf("Input three words:\n");
 for(i=0;i<=2;i++) gets(a[i]);
 for(i=1;i>=0;i--)
 {for(j=0;j<=i;j++)
  {if(strcmp(a[j],a[j+1])>0)
   {p=a[j];a[j]=a[j+1];a[j+1]=p;}
  }
 }
 printf("Out put is :\n%s\n%s\n%s\n",a[0],a[1],a[2]);
}
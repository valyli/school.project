#include<stdio.h>
#include<math.h>

void main()
{int i,j,na,num;
 unsigned long sn=0,sna=0;
 printf("Input how much of the number: ");scanf("%d",&na);printf("\n");
 printf("Input the number: ");scanf("%d",&num);printf("\n");
 for(i=1;i<=na;i++)
 {sna=0;
  for(j=0;j<i;j++) sna=sna+num*pow(10,j);
  sn=sn+sna;
  printf("%lu+",sna);
 }
printf("\b=");
printf("%lu\n",sn);
}
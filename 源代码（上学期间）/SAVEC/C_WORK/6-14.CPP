#include<stdio.h>
#define N 10
#define M 30

void main()
{int d=1,i,k;
 i=1;
 for(;i<=N;i+=d)
 {for(k=1;k<=N-i+M;k++) printf(" ");
  for(k=1;k<=2*i-1;k++) printf("*");
  printf("\n");
  if(i==N) d=-d;
  if(i==0) break;
 }
}
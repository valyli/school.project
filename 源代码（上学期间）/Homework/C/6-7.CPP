#include<stdio.h>
#include<math.h>

void main()
{int i,j,k;
 for(i=1;i<=1000;i++)
 {k=0;
  for(j=1;j<i;j++) if(i%j==0) k=k+j;
  if(k==i)
  {printf("%d its factors are ",i);
   for(j=1;j<i;j++) if(i%j==0) printf("%d,",j);
   printf("\b \n");
  }
 }
}
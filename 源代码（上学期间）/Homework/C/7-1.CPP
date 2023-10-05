#include<stdio.h>
void main()
{int static a[100];
 int i,j;
 for(i=0;i<=99;i++)
 {for(j=1;j<=i;j++)
  {if((i+1)%j==0 && j!=1)
   {a[i]=1;
    break;
   }
  }
 }
 j=0;
 for(i=0;i<=99;i++)
 {if(a[i]==0)
  {printf("%-5d",i+1);
   j++;
   if(j%5==0) printf("\n");
  }
 }
 printf("\n\n");
}
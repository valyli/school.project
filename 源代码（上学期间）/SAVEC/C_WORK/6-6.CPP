#include<stdio.h>
#include<math.h>

main()
{int i,j,sum,temp;
 for(i=100;i<=999;i++)
 {sum=0;
  temp=i;
  for(j=1;j<=3;j++)
  {sum=sum+pow(temp%10,3);
   temp=(int)(temp/10);
  }
  if(sum==i) printf("%d\n",i);
 }
}
#include<stdio.h>
#define N 10
void main()
{int a[N];
 int i,j,k;
 for(i=0;i<N;i++) scanf("%d",&a[i]);
 for(i=0;i<N;i++)
 {for(j=i;j<N;j++)
  {if(a[i]<a[j])
   {k=a[i];
    a[i]=a[j];
    a[j]=k;
   }
  }
 }
 for(i=0;i<N;i++) printf("%d,",a[i]);
}
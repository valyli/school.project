#include<stdio.h>
#define N 10

int eat(int n)
{int f;
 if(n==1) f=1;
 else f=2*(eat(n-1)+1);
 return(f);
}

void main()
{printf("%d",eat(N));
}

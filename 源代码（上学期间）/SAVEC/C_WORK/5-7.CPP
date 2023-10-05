#include<stdio.h>
#define N 10
long int a[N];
void input()
{loop:
 printf("Please input a positive integer number in 9 bits: ");
 scanf("%ld",&a[0]);
 if(a[0]<0)
 {printf("Your inputed number is spill over! Try again.");
  goto loop;
 }
}
void backforward(void)
{int i;
 for(i=1;i<=N-1;i++)
 {if(a[0]<10){a[i]=a[0];a[0]=i;break;}
  a[i]=a[0]%10;
  a[0]=(long int)(a[0]/10);
 }
}
void output(void)
{int i;
 printf("The number of bits: %d\n",a[0]);
 printf("The backformation of it: ");
 for(i=1;i<=a[0];i++) printf("%d",a[i]);
 printf("\n");
}
void main(void)
{input();
 backforward();
 output();
}
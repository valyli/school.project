#include<stdio.h>

void main()
{int i=1;
 char A,B,C;
 for(A='X';A<='Z';A++)
  for(B='X';B<='Z';B++)
   for(C='X';C<='Z';C++)
    if(A!='X'&&C!='X'&&C!='Z')
    {printf("%d.\n",i++);
     printf("A VS %c\n",A);
     printf("B VS %c\n",B);
     printf("C VS %c\n",C);
     printf("\n");
    }
}
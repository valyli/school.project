#include<stdio.h>
#include<conio.h>
void main()
{char a1,a2;
 while(a1!='\033' && a2!='\033')
 {do
  {a1=getch();
   if(a1!='\000') break;
   a2=getch();
   if(a2!='\120' || a2!='\110') break;
  }while(a1!='\000');
  if(a1=='\000' && a2=='\110')
  {printf("shang");
  }
  else if(a1=='\000' && a2=='\120')
  {printf("xia");
  }
 }
}
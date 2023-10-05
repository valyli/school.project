# include <stdio.h>
# include <graphics.h>
# include <conio.h>
# include <string.h>
# include <stdlib.h>

# define LINEWIDTH 6
# define WORDWIDTH 3
# define TEXTCOLOR_C 15
# define TEXTCOLOR_E 10

char hzk_file[8];

void p_cword(int qu,int wei,int &x,int &y)
{unsigned char word [32];
 FILE *fp_hzk;
 long int i,j,t,k;//,col=0;
 if ((fp_hzk=fopen (hzk_file,"rb" ))==NULL)
 {printf ("cannot open input file.\n");
  return;
 }
  fseek (fp_hzk,(long)(qu*94+wei)*sizeof(word),0);
  fread(word,sizeof(word),1,fp_hzk);
//  if(!((k-n*94)%10)) col++;
  for (i=0;i<16;i++)
   for (j=0;j<2;j++)
    for(t=0;t<8;t++)
     if (word[i*2+j]&(0x80>>t))
     putpixel(x+j*8+t,y+i,TEXTCOLOR_C);//(((k-n*94)%10)*20+j*8+t,i+col*30,11);
 fclose(fp_hzk);
//getch();
}

void p_eword(int &x,int y,unsigned char qu)
{setcolor(TEXTCOLOR_E);
 switch(qu)
 {case '0':outtextxy(x,y+6,"0");break;
  case '1':outtextxy(x,y+6,"1");break;
  case '2':outtextxy(x,y+6,"2");break;
  case '3':outtextxy(x,y+6,"3");break;
  case '4':outtextxy(x,y+6,"4");break;
  case '5':outtextxy(x,y+6,"5");break;
  case '6':outtextxy(x,y+6,"6");break;
  case '7':outtextxy(x,y+6,"7");break;
  case '8':outtextxy(x,y+6,"8");break;
  case '9':outtextxy(x,y+6,"9");break;
  case 'a':outtextxy(x,y+6,"a");break;
  case 'b':outtextxy(x,y+6,"b");break;
  case 'c':outtextxy(x,y+6,"c");break;
  case 'd':outtextxy(x,y+6,"d");break;
  case 'e':outtextxy(x,y+6,"e");break;
  case 'f':outtextxy(x,y+6,"f");break;
  case 'g':outtextxy(x,y+6,"g");break;
  case 'h':outtextxy(x,y+6,"h");break;
  case 'i':outtextxy(x,y+6,"i");break;
  case 'j':outtextxy(x,y+6,"j");break;
  case 'k':outtextxy(x,y+6,"k");break;
  case 'l':outtextxy(x,y+6,"l");break;
  case 'm':outtextxy(x,y+6,"m");break;
  case 'n':outtextxy(x,y+6,"n");break;
  case 'o':outtextxy(x,y+6,"o");break;
  case 'p':outtextxy(x,y+6,"p");break;
  case 'q':outtextxy(x,y+6,"q");break;
  case 'r':outtextxy(x,y+6,"r");break;
  case 's':outtextxy(x,y+6,"s");break;
  case 't':outtextxy(x,y+6,"t");break;
  case 'u':outtextxy(x,y+6,"u");break;
  case 'v':outtextxy(x,y+6,"v");break;
  case 'w':outtextxy(x,y+6,"w");break;
  case 'x':outtextxy(x,y+6,"x");break;
  case 'y':outtextxy(x,y+6,"y");break;
  case 'z':outtextxy(x,y+6,"z");break;
  case 'A':outtextxy(x,y+6,"A");break;
  case 'B':outtextxy(x,y+6,"B");break;
  case 'C':outtextxy(x,y+6,"C");break;
  case 'D':outtextxy(x,y+6,"D");break;
  case 'E':outtextxy(x,y+6,"E");break;
  case 'F':outtextxy(x,y+6,"F");break;
  case 'G':outtextxy(x,y+6,"G");break;
  case 'H':outtextxy(x,y+6,"H");break;
  case 'I':outtextxy(x,y+6,"I");break;
  case 'J':outtextxy(x,y+6,"J");break;
  case 'K':outtextxy(x,y+6,"K");break;
  case 'L':outtextxy(x,y+6,"L");break;
  case 'M':outtextxy(x,y+6,"M");break;
  case 'N':outtextxy(x,y+6,"N");break;
  case 'O':outtextxy(x,y+6,"O");break;
  case 'P':outtextxy(x,y+6,"P");break;
  case 'Q':outtextxy(x,y+6,"Q");break;
  case 'R':outtextxy(x,y+6,"R");break;
  case 'S':outtextxy(x,y+6,"S");break;
  case 'T':outtextxy(x,y+6,"T");break;
  case 'U':outtextxy(x,y+6,"U");break;
  case 'V':outtextxy(x,y+6,"V");break;
  case 'W':outtextxy(x,y+6,"W");break;
  case 'X':outtextxy(x,y+6,"X");break;
  case 'Y':outtextxy(x,y+6,"Y");break;
  case 'Z':outtextxy(x,y+6,"Z");break;
  case ' ':outtextxy(x,y+6," ");break;
  case '!':outtextxy(x,y+6,"!");break;
  case '"':outtextxy(x,y+6,"\"");break;
  case '#':outtextxy(x,y+6,"#");break;
  case '$':outtextxy(x,y+6,"$");break;
  case '%':outtextxy(x,y+6,"%");break;
  case '&':outtextxy(x,y+6,"&");break;
  case '\'':outtextxy(x,y+6,"'");break;
  case '(':outtextxy(x,y+6,"(");break;
  case ')':outtextxy(x,y+6,")");break;
  case '*':outtextxy(x,y+6,"-");break;
  case '+':outtextxy(x,y+6,"+");break;
  case ',':outtextxy(x,y+6,",");break;
  case '-':outtextxy(x,y+6,"-");break;
  case '.':outtextxy(x,y+6,".");break;
  case '/':outtextxy(x,y+6,"/");break;
  case ':':outtextxy(x,y+6,":");break;
  case ';':outtextxy(x,y+6,";");break;
  case '<':outtextxy(x,y+6,"<");break;
  case '=':outtextxy(x,y+6,"=");break;
  case '>':outtextxy(x,y+6,">");break;
  case '?':outtextxy(x,y+6,"?");break;
  case '@':outtextxy(x,y+6,"@");break;
  case '[':outtextxy(x,y+6,"[");break;
  case ']':outtextxy(x,y+6,"]");break;
  case '\\':outtextxy(x,y+6,"\\");break;
  case '^':outtextxy(x,y+6,"^");break;
  case '_':outtextxy(x,y+6,"_");break;
  case '`':outtextxy(x,y+6,"`");break;
  case '{':outtextxy(x,y+6,"{");break;
  case '}':outtextxy(x,y+6,"}");break;
  case '|':outtextxy(x,y+6,"|");break;
  case '~':outtextxy(x,y+6,"~");break;
  default :break;
 }
 x+=8+WORDWIDTH;
 return;
}

void p_map(int x,int y,char name[])
{FILE *fp;
 int basic_x=x;
 unsigned char qu,wei;
 if((fp=fopen(name,"r"))==NULL)
 {printf("cannot open file\n");
  return;
 }
 while(!feof(fp))
 { //  fread(&qu,1,1,fp);
  while(!feof(fp))
  {fread(&qu,1,1,fp);
   if(qu>=0x80) break;
   else if(qu=='\n')
   {y=y+16+LINEWIDTH;
    x=basic_x;//printf("%c",qu);
   }
   else  p_eword(x,y,qu);
  }
  if(feof(fp)) break;
  fread(&wei,1,1,fp);
//  if(a=='\n') break;
  qu=qu-0x20-0x80-1;wei=wei-0x20-0x80-1;
  p_cword(qu,wei,x,y);
  x=x+16+WORDWIDTH;
 }
 if(qu!='\n')
 {setcolor(RED);
//  outtextxy(x-10,y+6,"Û");
 }
 fclose(fp);
 return;
}

void clear_map(void)
{setfillstyle(1,BLACK);
 bar(0,0,639,479);
}

void draw_map(void)
{setfillstyle(6,RED);
 bar(0,0,639,479);
 setcolor(YELLOW);
 rectangle(215,20,420,75);
 setfillstyle(6,12);
 bar(216,21,419,74);
}

void draw_table(void)
{int x,y;
 setfillstyle(6,1);
 bar(39,83,599,452);
 setcolor(1);
 rectangle(38,82,600,453);
 for(y=82+22;y<450;y+=22)
 {line(41,y,600,y);
 }
 line(151,82,151,450);
 line(314,82,314,450);
 line(429,82,429,450);
}

void main(int argc,char *argv[])
{int gd=EGA,gm=VGAHI;
 initgraph(&gd,&gm,"");
 argc=2;
 if(strcmp(argv[1],"?")==0)
 {strcpy(hzk_file,"hzk16");
  p_map(0,0,"readme.ini");//printf("");
  getch();
  cleardevice();
  closegraph();
  exit(0);
 }
 else if(strcmp(argv[1],"f")==0 || strcmp(argv[1],"F")==0) strcpy(hzk_file,"hzk16f");
 else strcpy(hzk_file,"hzk16");
 draw_map();
 p_map(45,40,"1.txt");
 getch();
 clear_map();
 draw_map();
 p_map(40,40,"2.txt");
 getch();
 draw_map();
 draw_table();
 p_map(40,40,"3.txt");
 getch();
 cleardevice();
 closegraph();
 exit(0);
}
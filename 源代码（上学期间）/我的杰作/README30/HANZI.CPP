# include <iostream.h>
# include <stdio.h>
# include <graphics.h>
# include <conio.h>
# include <stdlib.h>
typedef unsigned char word [32];

//# define n 7

void  main()
{       long int n;
	cin>>n;
	FILE *fp;
	long int i,j,t,k,col=0;
	word one;
	int gd=VGA,gm=VGAHI;
	initgraph(&gd,&gm,"c:\\tc\\bgi");
	if ((fp=fopen ("a:\\hzk16","rb" ))==NULL)
	{
	fprintf (stderr,"cannot open input file.\n");
	return;
	}
	for (k=n*94;k<n*94+94;k++)
	{
		fseek (fp,k*sizeof(word),SEEK_SET);
		fread(one,sizeof(word),1,fp);
		if(!((k-n*94)%10)) col++;
		for (i=0;i<16;i++)
		for (j=0;j<2;j++)
		for(t=0;t<8;t++)
		if (one [i*2+j]&(0x80>>t))
		putpixel (((k-n*94)%10)*20+j*8+t,i+col*30,11);
	}
	fclose(fp);
	getch();

}

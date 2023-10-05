//
//	Make by LiJia
//	3,8,2000
//

//////////////////!! MUST NEED IN PROGRAMME////////////////////////
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0

typedef int Status;

int Show_c_e=0;		//0,show nothing code; 1,show compress codes;
			//2,show extract codes; 3,show all codes;
char file_from[50], file_to[50];	//Save the filename in this

FILE *fp_from, *fp_to;		//Save the filepoint in this
//////////////////END MUST NEED//////////////////////////////

//////////////////Open files for compress function/////////////////////
Status open_files_compress(void)
{
	if((fp_from=fopen(file_from,"rb"))==NULL)
	{
		printf("Cannot open the Source file!\n\r");
		printf("May be it is not exsit on your disk or path.\n\r");
		return FALSE;
	}
	if((fp_to=fopen(file_to,"wb+"))==NULL)
	{
		printf("Cannot build a new file!\n\r");
		fclose(fp_from);
		return FALSE;
	}
	return TRUE;
}
////////////////////////End open files////////////////////////////////

//////////////////////Open files for the extract function///////////////
Status open_files_extract(void)
{
	if((fp_from=fopen(file_from,"rb"))==NULL)
	{
		printf("Cannot open the Source file!\n\r");
		printf("May be it is not exsit on your disk or path.\n\r");
		return FALSE;
	}
	if((fp_to=fopen(file_to,"wb+"))==NULL)
	{
		printf("Cannot build a new file!\n\r");
		fclose(fp_from);
		return FALSE;
	}
	return TRUE;
}
//////////////////////End open files//////////////////////////////////

/////////////COMPRESS START/////////////////////////////////////
Status compress()
{
	unsigned int same_size=0;
	unsigned char same_char='ÿ';
	unsigned char load_char;
	unsigned char flag='ÿ';
	while(fread(&load_char,sizeof(unsigned char),1,fp_from)!=0)
	{
		if(Show_c_e==1 || Show_c_e==3)     //Show codes when compress
			printf("%c",load_char);
		if(same_char!=load_char && same_size==0)
		{
			fwrite(&load_char,sizeof(unsigned char),1,fp_to);
			same_char=load_char;
		}
		else if(same_char==load_char)
		{
			same_size++;
		}
		else
		{
			if(same_char==flag)
			{
				fwrite(&flag,sizeof(unsigned char),1,fp_to);
				fwrite(&same_char,sizeof(unsigned char),1,fp_to);
			}
			else
			{
				fwrite(&flag,sizeof(unsigned char),1,fp_to);
				fwrite(&same_size,sizeof(unsigned int),1,fp_to);
				fwrite(&load_char,sizeof(unsigned char),1,fp_to);
			}
			same_char=load_char;
			same_size=0;
		}
		if(load_char==flag)
		{
			if(1==ftell(fp_from) || same_size!=0)
				fwrite(&load_char,sizeof(unsigned char),1,fp_to);
			fwrite(&load_char,sizeof(unsigned char),1,fp_to);
			same_size=0;
		}
	}
	if(same_size!=0) fwrite(&same_size,sizeof(unsigned int),1,fp_to);
	return TRUE;
}
////////////Compress End///////////////////////////////////////////

/////////// Extra start/////////////////////////////////////////////
Status extract(void)
{
	unsigned int same_size=0;
	unsigned char same_char;
	unsigned char load_char;
	unsigned char flag='ÿ';
	unsigned int t_f_same;
	rewind(fp_from);
	while(fread(&load_char,sizeof(unsigned char),1,fp_from)!=0)
	{
		if(Show_c_e==2 || Show_c_e==3)      //Show codes when extract
			printf("%c",load_char);
		if(load_char!=flag)
		{
			fwrite(&load_char,sizeof(unsigned char),1,fp_to);
			same_char=load_char;
		}
		else
		{
			fread(&load_char,sizeof(unsigned char),1,fp_from);
			if(load_char==flag)
			{
				fwrite(&load_char,sizeof(unsigned char),1,fp_to);
				continue;
			}
			else fseek(fp_from,-1,1);
			fread(&same_size,sizeof(unsigned int),1,fp_from);
			for(t_f_same=1;t_f_same<=same_size;t_f_same++)
			{
				fwrite(&same_char,sizeof(unsigned char),1,fp_to);
			}
		}
	}
	return TRUE;
}
////////////Extra End//////////////////////////////////////////////////////

Status close_files(void)
{
	if(fclose(fp_from)==EOF) return FALSE;
	if(fclose(fp_to)==EOF) return FALSE;
	return TRUE;
}

void Input_filename(void)
{
	cprintf("\n\rInput Source filename: ");
	scanf("%s",file_from);
	cprintf("\n\rInput Target filename: ");
	scanf("%s",file_to);
}

void main(void)
{
	char user_want, user_w_show=0;
/////////////////////START MAIN MENU////////////////////////////////
	textcolor(GREEN);	//Set Menu color;

	do
	{
		clrscr();
		cprintf("\n\r1. Compress file\n\r");
		cprintf("2. Extract file\n\r");
		cprintf("3. Show the code (Will be slow anf beep)\n\r");
		cprintf("0. Exit\n\r");
		cprintf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\r****************************  Produced by LiJia  ****************************\n\r");
		user_want=getch();
		clrscr();
		if(user_want=='1')
		{
			cprintf("******Type the filename which you want to compress******\n\r");
			Input_filename();
			if(FALSE==open_files_compress())
			{
				getch();
				continue;
			}
			if(FALSE==compress()) exit(0);
			if(FALSE==close_files()) exit(0);
		}
		if(user_want=='2')
		{
			cprintf("******Type the filename which you want to extract******\n\r");
			Input_filename();
			if(FALSE==open_files_extract())
			{
				getch();
				continue;
			}
			if(FALSE==extract()) exit(0);
			if(FALSE==close_files()) exit(0);
		}
		if(user_want=='3')
		{
			clrscr();
			cprintf("0. No code will show\n\r");
			cprintf("1. Show codes when compress\n\r");
			cprintf("2. Show codes when extract\n\r");
			cprintf("3. Show all of codes\n\r");
			user_w_show=getch();
			user_w_show=user_w_show-48;
			if(0<=user_w_show && user_w_show<=3)
				Show_c_e=user_w_show;
		}
	}while(user_want!='0');
	exit(0);
}

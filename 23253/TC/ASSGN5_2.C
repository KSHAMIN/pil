/*=====================================================================
 Assignment 5    (using int86x,int86)
 Title :	    Delete a file, Create a directory
 Problem Statement: Write menu driven program in C using int86,int86x,intdos,intdosx
					functions for implementing following operations on file.
					1. To delete a file
					2. To create a directory
 

===================================================================== */

#include<dos.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

char dirname[50];
char filename[20];
union REGS inreg,outreg;
struct SREGS segreg;

void CRDIR()
{
	printf("\nEnter the directory name:\n");
	scanf("%s",dirname);

	inreg.h.ah=0x39;//load the function to create directory
	inreg.x.dx=FP_OFF(dirname);
	segreg.ds=FP_SEG(dirname);

	int86x(0X21,&inreg,&outreg,&segreg);
	if(outreg.x.cflag)
		printf("\nERROR IN CREATING DIRECTORY\n");
		else
		printf("\nDIRECTORY IS CREATED\n");
}
void DELFILE()
{
	printf("\nEnter the filename to delete:\n");
	scanf("%s",filename);

	inreg.h.ah=0x41;//del file
	inreg.x.dx=FP_OFF(filename);

	int86(0x21,&inreg,&outreg);
	if(outreg.x.cflag)
		printf("\nERROR!!!\n");
	else
		printf("\n\FILE IS DELETED!!!");
}

void copy()
{
	union REGS i,o;
	struct SREGS sr;
	char far(fname1[128]);
	char far(fname2[128]);
	char far(buffer[256]);
	int h1,h2;
	clrscr();

	//*******************opening file 1 for reading content******
	printf("\nEnter File1 Name to be copied:");
	gets(fname1);
	i.h.ah=0X3D;
	i.x.dx=FP_OFF(fname1);
	sr.ds=FP_SEG(fname1);
	i.h.al=0X00;
	intdosx(&i,&o,&sr);
	h1=o.x.ax;
	if(o.x.cflag==0)
	{
		printf("\n\n\t %s File1 reading!!!",fname1);
	}
	else
	{
		printf("\nFile1 not reading!!!");
	}
	//*********************creating file 2********************
	printf("\n\nEnter new File2 name to be created:");
	gets(fname2);
	i.h.ah=0X3C;
	i.x.dx=fname2;
	i.x.cx=0X00;
	intdosx(&i,&o,&sr);
	if(o.x.cflag==0)
	{
		printf("\n\t%s File2 created!!!",fname2);
	}
	//*********************open file 2 in write mode**********
	i.h.ah=0X3D;
	i.x.dx=FP_OFF(fname2);
	sr.ds=FP_SEG(fname2);
	i.h.al=0X01;

	intdosx(&i,&o,&sr);
	h2=o.x.ax;
	if(o.x.cflag==0)
	{
		printf("\n\t%s File2 has opened in write mode",fname2);
	}
	//****** reading data from file 1 *******
	i.h.ah=0X3F;
	i.x.bx=h1;
	i.x.cx=0XFF;
	i.x.dx=FP_OFF(buffer);
	sr.ds=FP_SEG(buffer);
	intdosx(&i,&o,&sr);
	if(o.x.cflag==0)
	{
		printf("\n\t%s File1 reading!!!",fname1);
		printf("\n\t%u No of bytes reading",o.x.ax);
	}
	//**************************writing data to file 2*******
	i.h.ah=0X40;
	i.x.bx=h2;
	i.x.cx=0XFF;
	i.x.dx=FP_OFF(buffer);
	sr.ds=FP_SEG(buffer);
	intdosx(&i,&o,&sr);
	if(o.x.cflag==0)
	{
		printf("\n\t%s File1 writing!!!",fname1);
		printf("\n\t%u No of bytes writing",o.x.ax);
	}
	i.h.ah=0X3E;
	i.x.bx=h1;
	intdos(&i,&o);
	i.h.ah=0X3E;
	i.x.bx=h2;
	intdos(&i,&o);
	getch();
}

int main()
{
	void CRDIR();
	void DELFILE();

	char *file;
	char *dir;
	int ch,t;
	clrscr();

	do{
		printf("\n\nFile Operations\n1.Create a directory\n2.Delete a file\n3.COPY\n4.Exit\n\nEnter your choice:=>");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:CRDIR();
				break;
			case 2:DELFILE();
				break;
			case 3:copy();
				break;
			case 4: exit(1);

		default:printf("\nInvalid choice\n");
		}
		printf("\nDo you want to continue?(1/0)");
		scanf("%d",&t);
	}while(t==1);

	getch();
	return 0;
}

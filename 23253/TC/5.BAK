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
	printf("\nEnter directory name:\n");
	scanf("%s",dirname);

	inreg.h.ah = 0x39;
	inreg.x.dx = FP_OFF(dirname);
	segreg.ds = FP_SEG(dirname);

	int86x(0x21,&inreg,&outreg,&segreg);
	if(outreg.x.cflag)
		printf("\nERROR IN CREATING THE FILE\n");
	else
		printf("\nDIRECTORY IS CREATED\n");
}

void DELFILE()
{
	printf("\nEnter the filename to delete:\n");
	scanf("%s",filename);

	inreg.h.ah = 0x41;
	inreg.x.dx = FP_OFF(filename);

	int86x(0x21,&inreg,&outreg);
	if(outreg.x.cflag)
		printf("\nERROR!!!\n");
	else
		printf("\nFILE IS CREATED!!\n");
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
		printf("\n\nFile Operations\n1)Create a directory\n2)Delete a file\n3)Exit\n");
		printf("\nEnter your choice:");
		scanf("%d",&ch);
		switch(ch)
		{
		case 1:
			CRDIR();
			break;
		case 2:
			DELFILE();
			break;
		case 3:
			exit(1);

		default:printf("\nInvalid Choice!\n");
		}
		printf("\nDo you want to continue?(1/0)");
		scanf("%d",&t);
	}while(t==1);
	getch();
	return 0;
}
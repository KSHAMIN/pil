#include <dos.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <graphics.h>
#include <alloc.h>
#include <string.h>



int    GraphDriver;		/* The Graphics device driver		*/
int    GraphMode;		/* The Graphics mode value		*/
double AspectRatio;		/* Aspect ratio of a pixel on the screen*/
int    MaxX, MaxY;		/* The maximum resolution of the screen */
int    X,Y, X_min, X_max, Y_min, Y_max, Ln_nos, Flag;
void far *MEM[100];
char ch;
struct Line
{
	int X1, Y1, X2, Y2;
	int Pt_1[4],Pt_2[4];
	float m;
}L[100];

/*									*/
/*	Function prototypes				*/
/*									*/

void Initialize(void);
void Draw_Cursor(void);
void Get_Cursor(int Xc1,int Yc1,int Xc2,int Yc2);
void Set_Cursor(int Xc1,int Yc1);
void Move_Cursor();

/*									*/
/*	M A I N    Function 7			*/
/*									*/


void main(void)
{
	Initialize();
	X=5;
	Y=5;
	Draw_Cursor();
	Get_Cursor(X,Y,X+10,Y+10);

	X_min = 125 ;
	X_max = MaxX-125;
	Y_min = 100;
	Y_max = MaxY-100;

	setcolor(WHITE);
	rectangle(X_min,Y_min,X_max,Y_max);

	Ln_nos = 0;

	do{
		Flag = 0;
		Move_Cursor();
		L[Ln_nos].X1 = X+5;
		L[Ln_nos].Y1 = Y+5;
		putpixel(L[Ln_nos].X1,L[Ln_nos].Y1,BLUE);
		setcolor(MAGENTA);
		Flag = 1;
		Move_Cursor();
		L[Ln_nos].X2 = X+5;
		L[Ln_nos].Y2 = Y+5;
		setcolor(MAGENTA);
		line(L[Ln_nos].X1,L[Ln_nos].Y1,L[Ln_nos].X2,L[Ln_nos].Y2);
	}while(ch!=27);
}


/*									*/
/*	INITIALIZE: Initializes the graphics system and reports 	*/
/*	any errors which occured.					*/
/*									*/

void Initialize(void)
{
  int xasp, yasp;			/* Used to read the aspect ratio*/
  GraphDriver = DETECT; 		/* Request auto-detection	*/
  initgraph( &GraphDriver, &GraphMode, "" );

  MaxX = getmaxx();
  MaxY = getmaxy();			/* Read size of screen		*/
  MaxY = MaxY - 15;
  getaspectratio( &xasp, &yasp );	/* read the hardware aspect	*/
  AspectRatio = (double)xasp / (double)yasp; /* Get correction factor	*/
  setcolor(BLUE);
  rectangle(0,0,MaxX, MaxY);
	settextstyle(2,0,4);
	setcolor(LIGHTGREEN);
	outtextxy(5,MaxY+2,"F1-               F2-                F3-                    F4-            F5-               Esc- ");
	setcolor(YELLOW);
	outtextxy(25,MaxY+2,"Inside Lines");
	setcolor(LIGHTRED);
	outtextxy(132,MaxY+2,"Outside Lines");
	outtextxy(247,MaxY+2,"Lines for Clipping");
	outtextxy(385,MaxY+2,"Clip Lines");
	outtextxy(475,MaxY+2,"Reset Screen");
	outtextxy(590,MaxY+2,"Exit");
}

void Draw_Cursor(void)
{
	setcolor(YELLOW);
	line(5,10,15,10);
	line(10,5,10,15);
}


void Get_Cursor(int Xc1,int Yc1,int Xc2,int Yc2)
{
	*MEM=farmalloc(sizeof(imagesize(Xc1,Yc1,Xc2,Yc2)));
	getimage(Xc1,Yc1,Xc2,Yc2,MEM);
}


void Set_Cursor(int Xc1,int Yc1)
{
	putimage(Xc1,Yc1,MEM,XOR_PUT);
}


void Move_Cursor()
{
   do{
	  ch = getche();
	  if(ch==0)
	  ch = getche();
	  putimage(X,Y,MEM,XOR_PUT);
	  settextstyle(2,0,4);
	  setcolor(YELLOW);
	  switch(ch)
	  {
		case 71: {
					X= X - 10;
					break;
				 }
		case 72: {
					Y--;
					break;
				 }
		case 73: {
					Y = Y - 10;
					break;
				 }
		case 75: {
					X--;
					break;
				 }
		case 77: {
					X++;
					break;
				 }
		case 79: {
					X = X + 10;
					break;
				 }
		case 80: {
					Y++;
					break;
				 }
		case 81: {
					Y = Y + 10;
					break;
				 }
		case 27: {
					closegraph();
					exit(0);
				 }
		case 59: {
					setcolor(YELLOW);
					outtextxy(25,MaxY+2,"Inside Lines");
					setcolor(LIGHTRED);
					outtextxy(132,MaxY+2,"Outside Lines");
					outtextxy(247,MaxY+2,"Lines for Clipping");
					outtextxy(385,MaxY+2,"Clip Lines");
					outtextxy(475,MaxY+2,"Reset Screen");
					outtextxy(590,MaxY+2,"Exit");
					break;
				 }
		case 60: {
					setcolor(YELLOW);
					outtextxy(132,MaxY+2,"Outside Lines");
					setcolor(LIGHTRED);
					outtextxy(25,MaxY+2,"Inside Lines");
					outtextxy(247,MaxY+2,"Lines for Clipping");
					outtextxy(385,MaxY+2,"Clip Lines");
					outtextxy(475,MaxY+2,"Reset Screen");
					outtextxy(590,MaxY+2,"Exit");
					break;
				 }
		case 61: {
					setcolor(YELLOW);
					outtextxy(247,MaxY+2,"Lines for Clipping");
					setcolor(LIGHTRED);
					outtextxy(25,MaxY+2,"Inside Lines");
					outtextxy(132,MaxY+2,"Outside Lines");
					outtextxy(385,MaxY+2,"Clip Lines");
					outtextxy(475,MaxY+2,"Reset Screen");
					outtextxy(590,MaxY+2,"Exit");
					break;
				 }
		case 62: {
					setcolor(YELLOW);
					outtextxy(385,MaxY+2,"Clip Lines");
					setcolor(LIGHTRED);
					outtextxy(25,MaxY+2,"Inside Lines");
					outtextxy(132,MaxY+2,"Outside Lines");
					outtextxy(247,MaxY+2,"Lines for Clipping");
					outtextxy(475,MaxY+2,"Reset Screen");
					outtextxy(590,MaxY+2,"Exit");
					break;
				 }

		case 63: {  closegraph();
					main();
					break;
				  }
	  }
	  if(X<0)
		X=0;
	  if(X>MaxX-10)
		X = MaxX-10;
	  if(Y<0)
		Y=0;
	  if(Y>MaxY-10)
		Y = MaxY-10;
	  putimage(X,Y,MEM,XOR_PUT);
   }while(ch!=13);
}


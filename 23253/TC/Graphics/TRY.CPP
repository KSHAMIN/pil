#include <dos.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <graphics.h>
#include <alloc.h>
#include <string.h>

#define sgn(x) ((x<0)?-1:((x>0)?1:0)) /* macro to return the sign of a number */


int    GraphDriver;		/* The Graphics device driver		*/
int    GraphMode;		/* The Graphics mode value		*/
double AspectRatio;		/* Aspect ratio of a pixel on the screen*/
int    MaxX, MaxY;		/* The maximum resolution of the screen */
long int    X,Y,X1,X2,Y1,Y2;
int    Algo;
void far *MEM[100];
char ch;

/*									*/
/*	Function prototypes				*/
/*									*/

void Initialize(void);
void Draw_Axis(void);
void Draw_Cursor(void);
void Get_Cursor(int Xc1,int Yc1,int Xc2,int Yc2);
void Set_Cursor(int Xc1,int Yc1);
void Move_Cursor();
void Show_XY(int x, int y);
void Show_Pts(int x, int y);
void DDA_Line(int X1,int Y1,int X2, int Y2);
void Bresenham_Line(int X1,int Y1,int X2, int Y2);
void Circle(int X1,int Y1,int X2, int Y2);
void Plot_Circle_Pts(int x, int y, int Color);
int Sign(float xa,float xb);

/*									*/
/*	M A I N    Function 7			*/
/*									*/


void main(void)
{
	Initialize();
	Draw_Axis();
	X=5;
	Y=5;
	Draw_Cursor();
	Get_Cursor(X,Y,X+10,Y+10);
	do{
		Move_Cursor();
		X1=X+5;
		Y1=Y+5;
		putpixel(X1,Y1,LIGHTRED);
		setcolor(MAGENTA);
		circle(X1,Y1,4);
		Show_Pts(X1,Y1);
		Move_Cursor();
		X2=X+5;
		Y2=Y+5;
		putpixel(X2,Y2,LIGHTRED);
		setcolor(MAGENTA);
		circle(X2,Y2,4);
		Show_Pts(X2,Y2);
		setcolor(LIGHTGREEN);
		switch(Algo)
		{
			case 1 : {
						DDA_Line(X1,Y1,X2,Y2);
						break;
					 }
			case 2 : {
						Bresenham_Line(X1,Y1,X2,Y2);
						break;
					 }
			case 3 : {
						Circle(X1,Y1,X2,Y2);
						break;
					 }
		}

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

}

void Draw_Axis()
{
	int i;
	char *str;
	setcolor(BLUE);
	rectangle(0,0,MaxX, MaxY);
	setcolor(BLUE);
	line(0,MaxY/2,MaxX,MaxY/2);
	line(MaxX/2,0,MaxX/2,MaxY);
	settextstyle(0,0,0);
	setcolor(LIGHTGREEN);
	outtextxy(480,MaxY+2,"X-      : Y-      ");
	settextstyle(2,0,4);
	setcolor(LIGHTGREEN);
	outtextxy(5,MaxY+2,"F1-          F2-                  F3-        F4-              Esc- ");
	setcolor(YELLOW);
	Algo=1;
	outtextxy(25,MaxY+2,"DDA Line");
	setcolor(LIGHTRED);
	outtextxy(105,MaxY+2,"Bresenham's Line");
	outtextxy(230,MaxY+2,"Circle");
	outtextxy(297,MaxY+2,"Reset Screen");
	outtextxy(405,MaxY+2,"Exit");
	setcolor(CYAN);
/*	for(i=19;i<MaxX-19;i=i+50)
		line(i,MaxY/2-3,i,MaxY/2+3);
	for(i=32;i<MaxY-31;i=i+50)
		line(MaxX/2-3,i,MaxX/2+3,i);
	for(i=19;i<MaxX-19;i=i+50)
	{
		flushall();
		itoa(i-319,str,10);
		setcolor(BROWN);
		outtextxy(i-5,MaxY/2+4,str);
	}
	for(i=32;i<MaxY-31;i=i+50)
	{
		flushall();
		itoa(232-i,str,10);
		setcolor(BROWN);
		outtextxy(MaxX/2+5,i-6,str);
	}
	Show_XY(5,5);*/
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
		case 62: {
					cleardevice();
					Draw_Axis();
					break;
				 }
		case 59: {
					outtextxy(25,MaxY+2,"DDA Line");
					setcolor(LIGHTRED);
					outtextxy(105,MaxY+2,"Bresenham's Line");
					outtextxy(230,MaxY+2,"Circle");
					Algo=1;
					break;
				 }
		case 60: {
					outtextxy(105,MaxY+2,"Bresenham's Line");
					setcolor(LIGHTRED);
					outtextxy(25,MaxY+2,"DDA Line");
					outtextxy(230,MaxY+2,"Circle");
					Algo=2;
					break;
				 }
		case 61: {
					outtextxy(230,MaxY+2,"Circle");
					setcolor(LIGHTRED);
					outtextxy(25,MaxY+2,"DDA Line");
					outtextxy(105,MaxY+2,"Bresenham's Line");
					Algo=3;
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
	  Show_XY(X,Y);
   }while(ch!=13);
}

void Show_XY(int x, int y)
{
	  char *str;
	  setfillpattern(0,BLACK);
	  bar(480,MaxY+2,MaxX,MaxY+15);
	  settextstyle(0,0,0);
	  setcolor(LIGHTGREEN);
	  outtextxy(480,MaxY+2,"X-      : Y-      ");
	  setcolor(LIGHTRED);
	  settextstyle(0,0,0);
	  itoa(x-314,str,10);
	  outtextxy(510,MaxY+2,str);
	  itoa(227-y,str,10);
	  outtextxy(590,MaxY+2,str);
}

void Show_Pts(int x, int y)
{
	  char str[12],*str1=NULL;
	  flushall();
	  setcolor(LIGHTMAGENTA);
	  settextstyle(2,0,4);
	  strcat(str,"(");
	  itoa(x-319,str1,10);
	  strcat(str,str1);
	  strcat(str,",");
	  itoa(232-y,str1,10);
	  strcat(str,str1);
	  strcat(str,")");
	  outtextxy(x+5,y,str);
}


void DDA_Line(int X1,int Y1,int X2, int Y2)
{
	int dx,dy,steps,k,Color;
	float x_inc,y_inc,x,y;

	do{
		Color=random(15);
	}while(Color==0);

	dx = X2 - X1;
	dy = Y2 - Y1;
	if(abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	x_inc = float(dx)/float(steps);
	y_inc = float(dy)/float(steps);
	x = X1;
	y = Y1;
	putpixel(x,y,Color);
	for(k=1; k!=steps; k++)
	{
		x = x + x_inc;
		y = y + y_inc;
		putpixel(x,y,Color);
		delay(10);
	}
}

void Circle(int X1,int Y1,int X2, int Y2)
{
	int x, y, p, Color;
	long int radius,a,b;

	do{
		Color=random(15);
	}while(Color==0);

	x = 0;
	if(X1 == X2)
		radius = abs(Y1 - Y2);
	else
	{
		if(Y1 == Y2)
			radius = abs(X1 - X2);
		else
		{
			a=(X1-X2);
			a=a*a;
			b=(Y1-Y2);
			b=b*b;
			radius = sqrt(a+b);
		}
	}
	y = radius;
	Plot_Circle_Pts(x,y,Color);
	p = 1 - radius;
	while(x < y)
	{
		if(p < 0)
		{
			x = x + 1;
			p = p + (2 * x) + 1;
		}
		else
		{
			x = x + 1;
			y = y - 1;
			p = p + (2 * (x - y)) + 1;
		}
		Plot_Circle_Pts(x,y,Color);
		delay(10);
	}
}

void Plot_Circle_Pts(int x, int y, int Color)
{
	putpixel(X1 + x, Y1 + y, Color);
	putpixel(X1 + x, Y1 - y, Color);
	putpixel(X1 - x, Y1 + y, Color);
	putpixel(X1 - x, Y1 - y, Color);
	putpixel(X1 + y, Y1 + x, Color);
	putpixel(X1 + y, Y1 - x, Color);
	putpixel(X1 - y, Y1 + x, Color);
	putpixel(X1 - y, Y1 - x, Color);
}

void Bresenham_Line(int X1,int Y1,int X2,int Y2)
{
  int i,dx,dy,sdx,sdy,dxabs,dyabs,x,y,px,py;

  dx=X2-X1;      /* the horizontal distance of the line */
  dy=Y2-Y1;      /* the vertical distance of the line */
  dxabs=abs(dx);
  dyabs=abs(dy);
  sdx=sgn(dx);
  sdy=sgn(dy);
  x=dyabs>>1;
  y=dxabs>>1;
  px=X1;
  py=Y1;


  if (dxabs>=dyabs) /* the line is more horizontal than vertical */
  {
	for(i=0;i<dxabs;i++)
	{
	  y+=dyabs;
	  if (y>=dxabs)
	  {
		y-=dxabs;
		py+=sdy;
	  }
	  px+=sdx;
	  putpixel(px,py,LIGHTGREEN);
	}
  }
  else /* the line is more vertical than horizontal */
  {
	for(i=0;i<dyabs;i++)
	{
	  x+=dxabs;
	  if (x>=dyabs)
	  {
		x-=dyabs;
		px+=sdx;
	  }
	  py+=sdy;
	  putpixel(px,py,LIGHTGREEN);
	}
  }
}

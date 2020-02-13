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
int    X,Y,X1,X2,Y1,Y2,XX[50],YY[50],Vertex,Sx,Sy;;
int    Algo;
void far *MEM[100];
char ch;

struct edge
{
	int x1,y1,x2,y2,flag;
};

/*									*/
/*	Function prototypes				*/
/*									*/

void Initialize(void);
void Draw_Axis(void);
void Draw_Cursor(void);
void Get_Cursor(int Xc1,int Yc1,int Xc2,int Yc2);
void Set_Cursor(int Xc1,int Yc1);
int Move_Cursor(void);
void Repostion_Cursor(void);
void Show_XY(int x, int y);
void Show_Pts(int x, int y);
void Plot_Circle_Pts(int x, int y, int Color);
void Boundry_Fill(int x, int y,int Fill_Color, int Bndry_Color);
void Flood_Fill(int x, int y,int Fill_Color, int Old_Color);
void Scan_Line_Fill(void);

/*									*/
/*	M A I N    Function 7			*/
/*									*/


void main(void)
{
	int ans,i;
	Initialize();
	Draw_Axis();
	X=5;
	Y=5;
	Draw_Cursor();
	Get_Cursor(X,Y,X+10,Y+10);
	do{
		Repostion_Cursor();
		setfillpattern(0,BLACK);
		bar(460,1,MaxX-2,15);
		settextstyle(2,0,4);
		setcolor(LIGHTGREEN);
		outtextxy(500,1,"Press Esc to End Polgon");
		Vertex = -1;
		do{
			ans = Move_Cursor();
			Vertex = Vertex + 1;
			if(ans == 0)
			{
				XX[Vertex] = X + 5;
				YY[Vertex] = Y + 5;
				putpixel(X+5,Y+5,BLUE);
			}
			else
			{
				XX[Vertex] = XX[0];
				YY[Vertex] = YY[0];
			}
			if(Vertex>0)
			{
				setcolor(LIGHTRED);
				line(XX[Vertex],YY[Vertex],XX[Vertex-1],YY[Vertex-1]);
			}
		}while(ans==0);

		Repostion_Cursor();

		setcolor(LIGHTGREEN);
		for(i=0;i!=Vertex;i++)
		{
			line(XX[i],YY[i],XX[i+1],YY[i+1]);
			delay(200);
		}

		switch(Algo)
		{
			case 1 : {
						setfillpattern(0,BLACK);
						bar(500,1,MaxX-2,15);
						Scan_Line_Fill();
						break;
					 }
			case 2 : {
						setfillpattern(0,BLACK);
						bar(500,1,MaxX-2,15);
						setcolor(LIGHTRED);
						outtextxy(460,1,"Plot Seed Point in the Polygon");
						Move_Cursor();
						Sx = X + 5;
						Sy = Y + 5;
						Set_Cursor(X,Y);
						Repostion_Cursor();
						Boundry_Fill(Sx,Sy,11,10);
						getch();
						break;
					 }
			case 3 : {
						setcolor(LIGHTGREEN);
						for(i=0;i!=Vertex;i++)
						{
							setcolor(i+1);
							line(XX[i],YY[i],XX[i+1],YY[i+1]);
						}

						setfillpattern(0,BLACK);
						bar(500,1,MaxX-2,15);
						setcolor(LIGHTRED);
						outtextxy(460,1,"Plot Seed Point in the Polygon");
						Move_Cursor();
						Sx = X + 5;
						Sy = Y + 5;
						Set_Cursor(X,Y);
						Repostion_Cursor();
						Flood_Fill(Sx,Sy,13,0);
						getch();
						break;

					 }
		}
	}while(ch!=68);
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
	outtextxy(5,MaxY+2,"F1-           F2-              F3-           F4-              F10- ");
	setcolor(YELLOW);
	Algo=1;
	outtextxy(25,MaxY+2,"Scan Line");
	setcolor(LIGHTRED);
	outtextxy(110,MaxY+2,"Boundry Fill");
	outtextxy(210,MaxY+2,"Flood Fill");
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
	putimage(Xc1,Yc1,MEM,XOR_PUT);
}


void Set_Cursor(int Xc1,int Yc1)
{
	putimage(Xc1,Yc1,MEM,XOR_PUT);
}


int Move_Cursor(void)
{
   do{
	  ch = getche();
	  if(ch==0)
	  ch = getche();
	  Set_Cursor(X,Y);
	  settextstyle(2,0,4);
	  setcolor(YELLOW);
	  switch(ch)
	  {
		case 27: {
					return(1);
				 }
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
		case 59: {
					outtextxy(25,MaxY+2,"Scan Line");
					setcolor(LIGHTRED);
					outtextxy(110,MaxY+2,"Boundry Fill");
					outtextxy(210,MaxY+2,"Flood Fill");
					Algo=1;
					break;
				 }
		case 60: {
					outtextxy(110,MaxY+2,"Boundry Fill");
					setcolor(LIGHTRED);
					outtextxy(25,MaxY+2,"Scan Line");
					outtextxy(210,MaxY+2,"Flood Fill");
					Algo=2;
					break;
				 }
		case 61: {
					outtextxy(210,MaxY+2,"Flood Fill");
					setcolor(LIGHTRED);
					outtextxy(25,MaxY+2,"Scan Line");
					outtextxy(110,MaxY+2,"Boundry Fill");
					Algo=3;
					break;
				 }
		case 62: {
					closegraph();
					main();
					break;
				 }

		case 68: {
					closegraph();
					exit(0);
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
	  Set_Cursor(X,Y);
	  Show_XY(X,Y);
   }while(ch!=13);
   return(0);
}

void Repostion_Cursor(void)
{
	X = 100;
	Y = 100;
	putimage(X,Y,MEM,OR_PUT);
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


void Boundry_Fill(int x, int y,int Fill_Color, int Bndry_Color)
{
	int Current_Color;

	Current_Color = getpixel(x,y);
	if((Current_Color!=Fill_Color)&&(Current_Color!=Bndry_Color))
	{
		putpixel(x,y,Fill_Color);
		delay(5);
		if(getpixel(x+1,y) != Fill_Color)
			Boundry_Fill(x+1 , y   , Fill_Color , Bndry_Color);
		if(getpixel(x+1,y+1) != Fill_Color)
			Boundry_Fill(x+1 , y+1 , Fill_Color , Bndry_Color);
		if(getpixel(x+1,y-1) != Fill_Color)
			Boundry_Fill(x+1 , y-1 , Fill_Color , Bndry_Color);
		if(getpixel(x-1,y) != Fill_Color)
			Boundry_Fill(x-1 , y   , Fill_Color , Bndry_Color);
		if(getpixel(x-1,y+1) != Fill_Color)
			Boundry_Fill(x-1 , y+1 , Fill_Color , Bndry_Color);
		if(getpixel(x-1,y-1) != Fill_Color)
			Boundry_Fill(x-1 , y-1 , Fill_Color , Bndry_Color);
		if(getpixel(x,y+1) != Fill_Color)
			Boundry_Fill(x   , y+1 , Fill_Color , Bndry_Color);
		if(getpixel(x,y-1) != Fill_Color)
			Boundry_Fill(x   , y-1 , Fill_Color , Bndry_Color);
	}
}


void Flood_Fill(int x, int y,int Fill_Color, int Old_Color)
{
	int Current_Color;

	Current_Color = getpixel(x,y);
	if(Current_Color==Old_Color)
	{
		putpixel(x,y,Fill_Color);
		delay(5);
		Flood_Fill(x+1 , y   , Fill_Color , Old_Color);
		Flood_Fill(x+1 , y+1 , Fill_Color , Old_Color);
		Flood_Fill(x+1 , y-1 , Fill_Color , Old_Color);
		Flood_Fill(x-1 , y   , Fill_Color , Old_Color);
		Flood_Fill(x-1 , y+1 , Fill_Color , Old_Color);
		Flood_Fill(x-1 , y-1 , Fill_Color , Old_Color);
		Flood_Fill(x   , y+1 , Fill_Color , Old_Color);
		Flood_Fill(x   , y-1 , Fill_Color , Old_Color);
	}
}

void Scan_Line_Fill(void)
{
	struct edge ed[50],temped;
	int i,j,k,x[50],y[50],ymax=0,ymin=480,yy,temp,color;
	float dx,dy,m[50],x_int[50],inter_x[50];

	do
	{
		color=random(15);
	}while((color==15)||(color==0));


	for(i=0;i!=Vertex;i++)
	{
		if(YY[i] > ymax)
			ymax = YY[i];
		if(YY[i] < ymin)
			ymin = YY[i];
		ed[i].x1 = XX[i];
		ed[i].y1 = YY[i];
	}

	for(i=0;i<Vertex-1;i++)
	{
		ed[i].x2 = ed[i+1].x1;
		ed[i].y2 = ed[i+1].y1;
		ed[i].flag = 0;
	}
	ed[i].x2 = ed[0].x1;
	ed[i].y2 = ed[0].y1;
	ed[i].flag = 0;

	for(i=0;i!=Vertex;i++)
	{
		if(ed[i].y1 < ed[i].y2)
		{
			temp = ed[i].x1;
			ed[i].x1 = ed[i].x2;
			ed[i].x2 = temp;
			temp = ed[i].y1;
			ed[i].y1 = ed[i].y2;
			ed[i].y2 = temp;
		}
	}

	setcolor(color);
	for(i=0;i<Vertex;i++)
	{
		line(ed[i].x1,ed[i].y1,ed[i].x2,ed[i].y2);
		delay(200);
	}

	for(i=0 ; i < Vertex-1 ; i++)
	{
		for(j=0 ; j < Vertex-1 ; j++)
		{
			if(ed[j].y1 < ed[j+1].y1)
			{
				temped = ed[j];
				ed[j] = ed[j+1];
				ed[j+1] = temped;
			}

			if(ed[j].y1 == ed[j+1].y1)
			{
				temped = ed[j];
				ed[j] = ed[j+1];
				ed[j+1] = temped;
			}
			if(ed[j].y2 == ed[j+1].y2)
			{
				if(ed[j].x1 < ed[j+1].x1)
				{
					temped = ed[j];
					ed[j] = ed[j+1];
					ed[j+1] = temped;
				}
			}
		}
	}

	for(i=0;i<Vertex;i++)
	{
		dx = ed[i].x2 - ed[i].x1;
		dy = ed[i].y2 - ed[i].y1;
		if(dy == 0)
			m[i] = 0;
		else
			m[i] = dx/dy;
		inter_x[i]=ed[i].x1;
	}

	yy=ymax;
	while(yy > ymin)
	{
		for(i=0; i<Vertex;i++)
		{
			if(yy > ed[i].y2 && yy <= ed[i].y1)
				ed[i].flag = 1;
			else
				ed[i].flag = 0;
		}

		j=0;
		for(i=0; i<Vertex; i++)
		{
			if(ed[i].flag==1)
			{
				if(yy == ed[i].y1)
				{
					x_int[j]=ed[i].x1;
					j++;
				}
				else
				{
					x_int[j]=inter_x[i] + (-m[i]);
					inter_x[i] = x_int[j];
					j++;
				}
			}
		}

		for(i=0; i<Vertex; i++)
		{
			for(k=0;k<j-1;k++)
			{
				if(x_int[k]>x_int[k+1])
				{
					temp = x_int[k];
					x_int[k] = x_int[k+1];
					x_int[k+1] = temp;
				}
			}
		}

		setcolor(color);
		for(i=0 ; i<j ; i=i+2)
			line(x_int[i],yy,x_int[i+1],yy);

		yy--;
		delay(100);
	}
	getch();
}
#include<graphics.h>
#include<conio.h>
void main()
{
 int GraphDriver, GraphMode;
 GraphDriver = DETECT; 		/* Request auto-detection	*/
 initgraph( &GraphDriver, &GraphMode, "" );
 setdefaulttextstyle();
 outtextxy(200,120,"Hello World~!@#$%^&*()0987654321`");
 getch();
 closegraph();
 exit(0);
}
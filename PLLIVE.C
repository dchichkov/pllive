#include <stdlib.h>
#include <graphics.h>
#include<dos.h>
unsigned   SEG_BUF,OFF_BUF;
extern void ALLPL(void);
extern void ALLPP(void);
void rewin(void);
void swiitch(int,int,int);
void strelka(void);
void och(void);
void livese(void);
void ntch(void);
main()
{
union REGS r;
int     grdr = EGA;
int     grmod = ATT400C0;
initgraph(&grdr, &grmod,"");
cleardevice();
setbkcolor(0);
setfillstyle(1,WHITE);
setcolor(WHITE);
r.x.ax=0xd;
int86(0x10,&r,&r);

r.x.ax=4;
int86(0x33,&r,&r);

r.x.ax=1;
int86(0x33,&r,&r);

r.h.ah=0x10;
r.h.al=1;
r.h.bh=0;
int86(0x10,&r,&r);

strelka();
closegraph();
}

void strelka(void)
{
int a,l,x,y;
union REGS r;
x=0;y=0;
r.x.ax=4;
r.x.cx=0;
r.x.dx=0;
int86(0x33,&r,&r);
while(1)
 {
  r.x.ax=3;
  int86(0x33,&r,&r);
  x=r.x.cx;
  y=r.x.dx;
   if(kbhit())
    {
     l=getch();
     if(l==0)  l=getch();
     if(l==27) return;
     swiitch(l,x,y);
    }
  }
}


void och(void)
{
int y;
int c;
c=getcolor();
setcolor(0);
for(y=0;y<100;y++)
 line(0,y,640,y);
setcolor(c);
}




void swiitch(int bb,int x,int y)
{
union REGS r;
r.x.ax=4;
r.x.cx=350;
r.x.dx=200;
int86(0x33,&r,&r);
 switch(bb)
          {
          case 32 :
	   r.x.ax=0x0c0d;
	   r.h.bl=0;
	   r.x.cx=x/2;
	   r.x.dx=y;
	   int86(0x10,&r,&r);
	   break;
          case 59 : och();break;
          case 60 : ntch();break;
          case 72 :if(y>0) y--;  break;
          case 80 :if(y<200) y++;break;
          case 75 :if(x>0) x--;  break;
          case 77 :if(x<350) x++;break;
          case 13 :livese();break;
          default:break;
          }
r.x.ax=4;
r.x.cx=x;
r.x.dx=y;
int86(0x33,&r,&r);
}

void livese(void)
{
long a;
char far *bufer;
bufer=malloc(64000);
if(bufer==0) {closegraph();exit(0);}
SEG_BUF=FP_SEG(bufer);
OFF_BUF=FP_OFF(bufer);
setmem(bufer,64000,0);
while(!kbhit())
 {
  ALLPL();
  ALLPP();
 }
free(bufer);
}

void ntch(void)
{
union REGS r;
int x,y;
if(kbhit()) getch();
while(!kbhit())
 {
 putpixel(random(640),random(200),13);
 }
}
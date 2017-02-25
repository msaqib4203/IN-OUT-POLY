#include<graphics.h>
#include<iostream>
using namespace std;
void ucbutton_design(int x2,int y2, int x1,int y1, char *str){
	setcolor(8);
	setlinestyle(0,1,3);
	line(x1,y1,x2,y1);
	line(x1,y1,x1,y2);
	setcolor(8);
	line(x1+2,y2,x2,y2);
	line(x2,y2,x2,y1+2);
	setfillstyle(1,15);
	setbkcolor(15);
	bar(x2-3,y2-3,x1+3,y1+3);
	setcolor(8);
	settextstyle(8,0,2);
      settextjustify(1,1);
	outtextxy((x1+x2)/2,(y1+y2+2)/2,str);
	setcolor(8);
	setlinestyle(0,1,1);
	rectangle(x2-2,y2-2,x1+2,y1+2);
	rectangle(x2,y2,x1,y1);
}



void refresh(){
ucbutton_design(25,25,1245,545,"");
setbkcolor(WHITE);
ucbutton_design(750,630,650,580,"MARK");
ucbutton_design(900,630,800,580,"CLEAR");
setbkcolor(BLACK);
setcolor(WHITE);
outtextxy(200,615,"POINT POSITION: ");
outtextxy(200,645,"STATUS: ");
}
/*int main(){

int gd = DETECT, gm, x, y, color, angle = 0;
   initgraph(&gd, &gm, "C:\\TC\\BGI");
refresh();
getch();
closegraph();

return 0;
}*/

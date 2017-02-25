#include<iostream>
#include<graphics.h>
#include"mydesign.h"
using namespace std;

/**
 *Structure for a point
 */
struct block{
    int x,y;
    block* next;
}*head=NULL,*temp,*tail=NULL;

/**
 * Structure for a line
 */
struct myLine{
    int x1,y1,x2,y2;
    myLine* next;
}*headL=NULL,*tempL,*tailL = NULL;

/**
 *Globals
 */
int X = -1;
int Y = -1;
bool doneDrawing = false;
bool Drawing = true;
int pointx,pointy;
int cutCount = 0;
/**
 *Function to add line
 */
void addLine(int X1,int Y1,int X2,int Y2){
    tempL = new myLine;
    tempL->x1 = X1;
    tempL->y1 = Y1;
    tempL->x2 = X2;
    tempL->y2 = Y2;
    tempL->next = NULL;
    if(headL == NULL){
        headL = tempL;
        tailL = tempL;
    }
    else{
        tailL->next = tempL;
        tailL = tempL;
    }
}

void removeAll(){
    headL = NULL;
    doneDrawing = false;
    head = NULL;
    tail = NULL;
    tailL = NULL;
    clearmouseclick(WM_LBUTTONUP);
    delay(50);
    setfillstyle(1,0);
    bar(240,630,350,650);
    bar(290,600,400,620);
    ucbutton_design(25,25,1245,545,"");
    ucbutton_design(750,630,650,580,"MARK");
}
void repaint(){
    if(Drawing)
    setcolor(0);
    if(head == NULL)
        return;
    if(head->next == NULL){
            if(Drawing)
        circle(head->x,head->y,1);
        return;
    }
    temp = head;
    if(Drawing)
        setlinestyle(0,1,3);
    while(temp->next!=NULL){
            if(Drawing)
        line(temp->x,temp->y,temp->next->x,temp->next->y);
        addLine(temp->x,temp->y,temp->next->x,temp->next->y);
        temp = temp->next;
    }
    if(doneDrawing){
        if(Drawing)
        line(tail->x,tail->y,head->x,head->y);
        addLine(tail->x,tail->y,head->x,head->y);
    }
}


void askInput(){
int n;
Drawing = false;
cout<<"No. of Points ";
cin>>n;
while(1){
    if(n<3)
    cout<<"Require atleast 3 points !";
    else
       break;
    cin>>n;
}
int x,y;
for(int i=1;i<=n;i++){
    cout<<"Point "<<i<<": ";
    cin>>x>>y;
    if(head == NULL){
        head = new block;
        head->x = x;
        head->y = y;
        head->next = NULL;
        tail = head;
    }
    else{
        temp = new block;
        temp->x = x;
        temp->y = y;
        temp->next = NULL;
        tail->next = temp;
        tail = temp;
                        }
}
cout<<"Enter Point Location To Be Checked : ";
cin>>pointx>>pointy;
doneDrawing = true;

}

int main(){
    /** Initialize Graphics **/
int gd = DETECT, gm, x, y, color, angle = 0;
    cout<<"1.Input points"<<endl<<"2.Draw Figure"<<endl;
    int c;
    cin>>c;
    if(c == 1)
      askInput();
    else if(c  == 2)
        cout<<"Opening Drawing Panel....";
    else{
        cout<<"Invalid Choice";
        return 0 ;
    }
/** Init graphics */
if(Drawing){
    initgraph(&gd, &gm, "C:\\TC\\BGI");
    delay(5000);
    refresh();
}
    while(!kbhit()){ // Overall Loop
        switch(doneDrawing){
            case false:
                while(!kbhit()){ // Drawing Loop
                    X = mousex();
                    Y = mousey();
                    /**
                    *Add Points
                    */
                    if(ismouseclick(WM_LBUTTONUP)&& X>25 && X<1245 && Y<545 && Y>25){
                        delay(100);
                        clearmouseclick(WM_LBUTTONUP);
                        delay(100);
                        if(head == NULL){
                            head = new block;
                            head->x = X;
                            head->y = Y;
                            head->next = NULL;
                            tail = head;
                        }
                        else{
                            temp = new block;
                            temp->x = X;
                            temp->y = Y;
                            temp->next = NULL;
                            tail->next = temp;
                            tail = temp;
                        }
                        headL = NULL;
                        repaint();
                    }
                    /** Ok Clicked*/
                    else if(ismouseclick(WM_LBUTTONUP)&& X>650 && X<750 && Y<630 && Y>580){
                        doneDrawing = true;
                        clearmouseclick(WM_LBUTTONUP);
                        delay(50);
                        headL = NULL;
                        repaint();
                        setfillstyle(1,11);
                        bar(650,580,750,630);
                        break;
                    }
                    else if(ismouseclick(WM_LBUTTONUP) && X < 900 && Y < 630 && X > 800 && Y > 580){
                        removeAll();
                    }
            }
            break;
            case true:

                headL = NULL;
                if(!Drawing)
                repaint();
                bool validPoint = false;
                if(Drawing){
                    repaint();
                delay(500);
                }
                int oldx=0,oldy=0;

                while(!kbhit()){//Point Loop

                        if(Drawing){
                    pointx = mousex();
                    pointy = mousey();
                        }
                        /** Clear Buuton Pressed*/
                    if(Drawing && ismouseclick(WM_LBUTTONUP) && pointx < 900 && pointy < 630 && pointx > 800 && pointy > 580){
                        removeAll();
                        break;
                    }
                    /** Panel Clicked*/
                    else if(Drawing && ismouseclick(WM_LBUTTONUP)&& pointx>25 && pointx<1245 && pointy<545 && pointy>25){
                        delay(100);
                        validPoint = true;
                        clearmouseclick(WM_LBUTTONUP);
                        delay(100);
                        setcolor(15);
                        circle(oldx,oldy,2);
                        setcolor(0);
                        circle(pointx,pointy,2);
                        oldx = pointx;
                        oldy = pointy;
                    }
                    if(validPoint || !Drawing){
/** locate point*/
                        tempL = headL;
                        if(tempL == NULL)
                            cout<<"Head is NULL";
                        cutCount = 0;
                    bool onLine = false;
                bool isVertex = false;
                        bool hasymax=false,hasymin = false,hasxmin = false,hasxmax = false;
                        while(tempL!=NULL){

                            int x1 = tempL->x1;
                            int y1 = tempL->y1;
                            int x2 = tempL->x2;
                            int y2 = tempL->y2;
                            double invSlope = (x2*1.0 - x1*1.0)/(y2 - y1);
                            int x = (invSlope*(pointy - y1)+x1);
                            if((x>=x1 && x<=x2)||(x<=x1 && x>=x2)){
                                if(x > pointx){
                                    cutCount++;
                                    hasxmax = true;
                                }
                                    else if (x < pointx){
                                hasxmin  = true;
                                }
                                if(x == pointx ){
                                    onLine = true;
                                hasxmax = true;
                                hasxmin = true;
                                }
                            }
                            invSlope = 1/invSlope;
                             int y = (invSlope*(pointx - x1)+y1);
                            if((y>=y1 && y<=y2)||(y<=y1 &&y>=y2)){
                                if(y > pointy){
                                    hasymax = true;
                                }if(y < pointy){
                                hasymin  = true;
                                }
                                if(y == pointy){
                                    hasymax = true;
                                    hasymin = true;
                                    onLine = true;
                                }
                            }
                            tempL = tempL->next;
                        }
                        /**Check for vertex*/
                        temp = head;
                        while(temp!=NULL){
                            if(pointx == temp->x && pointy == temp->y)
                                isVertex = true;
                            temp = temp->next;
                        }
                        if(Drawing){/** Patch panels*/
                            setcolor(15);
                            setfillstyle(1,0);
                            bar(240,630,350,650);
                            bar(290,600,400,620);
                            char strx[10],stry[10];
                            itoa(pointx,strx,10);
                            itoa(pointy,stry,10);
                            setbkcolor(0);
                            setcolor(15);
                            /** Display result in BGI*/
                            if(isVertex)
                                outtextxy(290,645,"A Vertex");
                            else if(onLine && hasymax && hasxmax && hasymin && hasxmin)
                                outtextxy(290,645,"On Line");
                            else if(!(hasymax && hasxmax && hasymin && hasxmin))
                                outtextxy(290,645,"Outside");
                        else if(cutCount%2!=0)
                            outtextxy(290,645,"Inside");
                        else
                            outtextxy(290,645,"Outside");
                        outtextxy(340,615,strcat(strcat(strx," "),stry));
                        delay(50);
                        pointx = -1;
                        }else{
                             /** Display result in Console*/
                            if(isVertex)
                                cout<<"A Vertex";
                             else if(onLine && hasymax && hasxmax && hasymin && hasxmin)
                              cout<<"On Line";
                            else if(!(hasymax && hasxmax && hasymin && hasxmin))
                                cout<<"Outside";
                        else if(cutCount%2!=0)
                            cout<<"Inside";
                        else
                            cout<<"Outside";
                            cout<<endl<<"Enter X Y for another point"<<endl;
                    cin>>pointx>>pointy;
                        }
                    }

                }//end of loc loop
        }//end of switch
    }//end of main loop

    getch();
    closegraph();

    return 0;
}

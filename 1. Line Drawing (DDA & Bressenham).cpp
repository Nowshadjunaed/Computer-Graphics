#include<bits/stdc++.h>
#include<graphics.h>
#include<windows.h>


using namespace std;
typedef pair<int,int> pii;

const int WINDOW_W  = 800, WINDOW_H = 600;

pii convertPixel(int x,int y)
{
    x += WINDOW_W/2;
    y = -y;
    y += WINDOW_H/2;
    return {x,y};
}
void drawAxis()
{
    for(int i=0;i<WINDOW_H;i++)
    {
        putpixel(400,i,WHITE);
    }
    for(int i=0;i<WINDOW_W;i++)
    {
        putpixel(i,300,WHITE);
    }
}
void drawPixel(int x,int y,int col)
{
    pii p = convertPixel(x,y);
    putpixel(p.first,p.second,col);
}

void DDA(int x1,int y1,int x2,int y2)
{
    int dx = x2-x1;
    int dy = y2-y1;
    double m = double(dy)/dx;
    double xin,yin;
    int tot;
    if(dx==0)
    {
        if(y1>y2) swap(y1,y2);
        for(int i=y1;i<=y2;i++) drawPixel(x1,i,YELLOW);
        return ;
    }
    else if(dy==0)
    {
        if(x1>x2) swap(x1,x2);
        for(int i=x1;i<=x2;i++) drawPixel(i,y1,YELLOW);
        return ;
    }

    if(abs(dx)>=abs(dy))
    {
        if(x1>x2)
        {
            swap(x1,x2);
            swap(y1,y2);
        }
        xin = 1;
        yin = m;
        tot = x2-x1+1;
    }
    else
    {
        if(y1>y2)
        {
            swap(x1,x2);
            swap(y1,y2);
        }
        yin = 1;
        xin = 1.0/m;
        tot = y2-y1 + 1;

    }
    double x = x1;
    double y = y1;
    for(int i=1;i<=tot;i++)
    {
        drawPixel(round(x),round(y),YELLOW);
        x += xin;
        y += yin;
    }
}
void Bressenham(int x1,int y1,int x2,int y2)
{
    int dx = x2-x1;
    int dy = y2-y1;
    int c1 = 2*(dy-dx);
    int c2 = 2*dy;
    int d = 2*dy-dx;
    for(int i=x1;i<=x2;i++)
    {
        drawPixel(i,y1,GREEN);
        if(d>=0) d += c1;
        else d += c2;
        if(d>=0) y1 += 1;
    }
}
int main()
{

    initwindow(WINDOW_W,WINDOW_H);

    drawAxis();


    DDA(20, 30, 150, 100);
    Bressenham(40, 50, 170, 120);
    getchar();

    return  0;
}

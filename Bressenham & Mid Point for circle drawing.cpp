
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


void Bressenham(int r,int centerX,int centerY)
{
    int d = 3-2*r;
    int tot = round(double(r)/sqrt(2.0));
    int y = round(sqrt(double(r*r-0)));

    for(int i=0;i<=tot;i++)
    {


        drawPixel(i+centerX,y+centerY,GREEN);
        drawPixel(i+centerX,-y+centerY,GREEN);
        drawPixel(-i+centerX,y+centerY,GREEN);
        drawPixel(-i+centerX,-y+centerY,GREEN);

        drawPixel(y+centerX,i+centerY,GREEN);
        drawPixel(-y+centerX,i+centerY,GREEN);
        drawPixel(y+centerX,-i+centerY,GREEN);
        drawPixel(-y+centerX,-i+centerY,GREEN);

        if(d<0) d += 4*i+6;
        else d+= 4*i-4*y+10;
        if(d>0) y -= 1;

    }
}

void MidPoint(int r,int centerX,int centerY)
{
    double D = 5.0/4.0 - r;
    int d = round(D);
    int tot = round(double(r)/sqrt(2.0));
    int y = round(sqrt(double(r*r-0)));

    for(int i=0;i<=tot;i++)
    {


        drawPixel(i+centerX,y+centerY,YELLOW);
        drawPixel(i+centerX,-y+centerY,YELLOW);
        drawPixel(-i+centerX,y+centerY,YELLOW);
        drawPixel(-i+centerX,-y+centerY,YELLOW);

        drawPixel(y+centerX,i+centerY,YELLOW);
        drawPixel(-y+centerX,i+centerY,YELLOW);
        drawPixel(y+centerX,-i+centerY,YELLOW);
        drawPixel(-y+centerX,-i+centerY,YELLOW);

        if(d<=0) d += 2*i+3;
        else d += 2*i-2*y+5;
        if(d>0) y -= 1;

    }
}
int main()
{

    initwindow(WINDOW_W,WINDOW_H);

    drawAxis();


    Bressenham(100,200,150);
    MidPoint(130,200,150);
    getchar();

    return  0;
}

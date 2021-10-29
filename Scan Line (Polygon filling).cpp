#include<bits/stdc++.h>
#include<windows.h>
#include<graphics.h>
using namespace std;

struct PT
{
    double x, y;
    PT(){}
    PT(double a, double b)
    {
        x = a;
        y = b;
    }

    bool operator < (const PT &p)const
    {
        return x < p.x;
    }
};

struct EDGE
{
    double y_min, y_max,x_with_y_min,m_inv;

    EDGE(){}
    EDGE(double a, double b, double c, double d)
    {
        y_min = a;
        y_max = b;
        x_with_y_min = c;
        m_inv = d;
    }

    bool operator < (const EDGE &p)const
    {
        return y_min < p.y_min;
    }
};
const int WINDOW_W = 800, WINDOW_H = 600;

void drawAxis()
{
    for(int i=0; i<WINDOW_H; i++) putpixel(WINDOW_W/2, i, WHITE);
    for(int i=0; i<WINDOW_W; i++) putpixel(i, WINDOW_H/2, WHITE);
}

PT convertPixel(PT p)
{
    p.x += WINDOW_W/2;
    p.y = -p.y;
    p.y += WINDOW_H/2;

    return p;
}

void drawPixel(PT p, int color)
{
    delay(0.1);
    p = convertPixel(p);
    putpixel((int)(p.x+0.5), (int)(p.y+0.5), color);
}

void drawLine(PT a, PT b,int col)
{

    if(a.y == b.y)
    {
        if(a.x>b.x) swap(a,b);
        for(int x = a.x; x <= b.x; x++)
        {
            drawPixel(PT(x, a.y), col);
        }
    }

    ///vertical

    else if(a.x == b.x)
    {
        if(a.y > b.y) swap(a, b);
        for(int y = a.y; y <= b.y; y++)
        {
            drawPixel(PT(a.x, y), col);
        }
    }

    else
    {
        double m = (double)(b.y-a.y)/(double)(b.x-a.x);
        double m_inv  = 1.0/m;
        if(fabs(m)<=1.0)
        {
            if(a.x>b.x) swap(a,b);
            while(a.x<=b.x)
            {
                drawPixel(a,col);
                a.x+=1;
                a.y+=m;
            }
        }
        else
        {
            if(a.y>b.y) swap(a,b);
            while(a.y<=b.y)
            {
                drawPixel(a,col);
                a.x += m_inv;
                a.y+=1;
            }
        }

    }
}

void drawPolygon(vector<PT> points,int col)
{
    int n = points.size();
    for(int i=0; i<n; i++)
    {
        drawLine(points[i], points[(i+1)%n],col);
    }
}

void scanLine(vector<PT> points,int color)
{
    vector<EDGE> edges;

    int n=points.size();
    double st = 1e15, en = -1e15;
    unordered_map<double, int>mp;
    for(int i=0;i<n;i++)
    {
        PT a = points[i];
        PT b = points[(i+1)%n];

        if(a.y==b.y) continue;

        EDGE temp;
        temp.y_min = min(a.y,b.y);
        temp.y_max = max(a.y,b.y);
        temp.x_with_y_min = (a.y<b.y)? a.x : b.x;
        temp.m_inv = (b.x-a.x)/(b.y-a.y);

        st = min(st, temp.y_min);
        en = max(en, temp.y_max);

        mp[temp.y_min] = 1;

        edges.push_back(temp);
    }
    sort(edges.begin(),edges.end());
    n = edges.size();

    for(int i=0;i<n;i++)
    {
        if(mp[edges[i].y_max]) edges[i].y_max--;
    }
    for(double y = st; y<= en;y++)
    {
        vector<PT> int_points;
        for(int i=0;i<n;i++)
        {
            if(y>= edges[i].y_min && y <= edges[i].y_max)
            {
                PT tmp;
                tmp.x = edges[i].x_with_y_min;
                tmp.y = y;
                edges[i].x_with_y_min += edges[i].m_inv;
                int_points.push_back(tmp);
            }
        }

        sort(int_points.begin(),int_points.end());

        for(int i=0;i<int_points.size()-1;i+=2)
        {
            drawLine(int_points[i],int_points[i+1],RED);
        }
    }
}


int main()
{
    initwindow(WINDOW_W, WINDOW_H);
    drawAxis();

    vector<PT> poly;

    poly.push_back(PT(-140, -40));
    poly.push_back(PT(-60, 60));
    poly.push_back(PT(0, 20));
    poly.push_back(PT(-40, -60));
    poly.push_back(PT(100, -80));
    poly.push_back(PT(120, 40));
    poly.push_back(PT(160, 100));
    poly.push_back(PT(-160, 160));

    drawPolygon(poly,YELLOW);


    scanLine(poly,RED);

    getchar();

    return 0;
}

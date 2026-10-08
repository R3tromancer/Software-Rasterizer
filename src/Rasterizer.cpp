#include "Rasterizer.h"
#include "Framebuffer.h"
#include "Color.h"

#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <math.h>


void drawLine(
    Framebuffer& framebuffer,
    int x0,
    int y0,
    int x1,
    int y1,
    Color color
)
{
    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);

    int sx = (x1 > x0) ? 1 : -1;
    int sy = (y1 > y0) ? 1 : -1;

    int error = dx - dy;

    while(true)
    {
        framebuffer.setPixel(x0, y0, color);

        if(x0 == x1 && y0 == y1)
        {
            break;
        }

        int doubledError = 2 * error;

        if (doubledError > -dy)
        {
            error -= dy;
            x0 += sx;
        }

        if(doubledError < dx)
        {
            error += dx;
            y0 += sy;
        }

    }
   /*  DDA floating point line algo
   
    int dx = x1 - x0;
    int dy = y1 - y0;

    int steps = std::max(std::abs(dx), std::abs(dy));

    if(steps == 0)
    {
        framebuffer.setPixel(x0, y0, color);
    }

    double xStep = static_cast<double>(dx) / steps;
    double yStep = static_cast<double>(dy) / steps;

    double x = x0;
    double y = y0;

    for (int i = 0; i <= steps; ++i)
    {
        int pixelX = static_cast<int>(std::round(x));
        int pixelY = static_cast<int>(std::round(y));

        framebuffer.setPixel(pixelX, pixelY, color);

        x += xStep;
        y += yStep;
    } */
}

/*  empty triangle algo

    void drawTriangle(
    Framebuffer& framebuffer,
    int x0,
    int y0,
    int x1,
    int y1,
    int x2,
    int y2,
    Color color
)
{
    drawLine(framebuffer, x0, y0, x1, y1, color);
    drawLine(framebuffer, x1, y1, x2, y2, color);
    drawLine(framebuffer, x2, y2, x0, y0, color);
}
 */

 static long long edgeFunction(
    int ax,
    int ay,
    int bx,
    int by,
    int px,
    int py
 )
 {
    return
    static_cast<long long>((bx - ax) * (py - ay)) 
    -
    static_cast<long long>((px - ax) * (by - ay));
 }


 void drawTriangle(
    Framebuffer& framebuffer,
    int x0,
    int y0,
    int x1,
    int y1,
    int x2,
    int y2,
    Color color
 )
 {
    int MinX = std::min({x0, x1, x2});
    int MaxX = std::max({x0, x1, x2});
    int MinY = std::min({y0, y1, y2});
    int MaxY = std::max({y0, y1, y2});

    MinX = std::max(MinX, 0);
    MaxX = std::min(MaxX, framebuffer.getWidth() - 1);
    MinY = std::max(MinY, 0);
    MaxY = std::min(MaxY, framebuffer.getHeight() - 1);

    long long checkABP = edgeFunction(x0, y0, x1, y1, MinX, MinY);
    int dx01 = x1 - x0;
    int dy01 = y1 - y0;

    //checkABP1x = checkABP - dy01;
    //checkABP1y = checkABP + dx01;

    long long checkBCP = edgeFunction(x1, y1, x2, y2, MinX, MinY);
    int dx12 = x2 - x1;
    int dy12 = y2 - y1;
    
    //checkBCP1x = checkBCP - dy12;
    //checkBCP1y = checkBCP + dx12;


    long long checkCPA = edgeFunction(x2, y2, x0, y0, MinX, MinY);

    int dx20 = x0 - x2;
    int dy20 = y0 - y2;    

    //checkCPA1x = checkCPA - dy20;
   // checkCPA1y = checkCPA + dx20;


   long long edge0 = checkABP;
   long long edge1 = checkBCP;
   long long edge2 = checkCPA;

    for (int y = MinY; y <= MaxY; ++y)
    {
        checkABP += y * dx01;
        checkBCP += y * dx12;
        checkCPA += y * dx20;


        for (int x = MinX; x <= MaxX; ++x)
        {
            bool isAllCheckPos = 
            (checkABP >= 0 && checkBCP >= 0 && checkCPA >= 0);

            bool isAllCheckNeg = 
            (checkABP <= 0 && checkBCP <= 0 && checkCPA <= 0);

            if(isAllCheckPos || isAllCheckNeg)
            {
                framebuffer.setPixel(x, y, color);
            }

            checkABP -= dy01;
            checkBCP -= dy12;
            checkCPA -= dy20;
        
        }

        checkABP = edge0;
        checkBCP = edge1;
        checkCPA = edge2;
    }
 }
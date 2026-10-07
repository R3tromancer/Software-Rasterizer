#include "Rasterizer.h"
#include "Framebuffer.h"
#include "Color.h"

#include <cstdlib>
#include <algorithm>


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
   /*  int dx = x1 - x0;
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

/* void drawTriangle(
    Framebuffer framebuffer,
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
} */


static long long edgeFunction(
    int ax,
    int ay,
    int bx,
    int by,
    int px,
    int py
)
{
    return static_cast<long long>(bx - ax) * (py - ay)
         - static_cast<long long>(by - ay) * (px - ax);
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
    int minX = std::min({x0, x1, x2});
    int maxX = std::max({x0, x1, x2});
    int minY = std::min({y0, y1, y2});
    int maxY = std::max({y0, y1, y2});

    minX = std::max(minX, 0);
    maxX = std::min(maxX, framebuffer.getWidth() - 1);
    minY = std::max(minY, 0);
    maxY = std::min(maxY, framebuffer.getHeight() - 1);

    for (int y = minY; y <= maxY; ++y)
    {
        for (int x = minX; x <= maxX; ++x)
        {
            long long edge0 =
                edgeFunction(x0, y0, x1, y1, x, y);

            long long edge1 =
                edgeFunction(x1, y1, x2, y2, x, y);

            long long edge2 =
                edgeFunction(x2, y2, x0, y0, x, y);

            bool allPositive =
                edge0 >= 0 &&
                edge1 >= 0 &&
                edge2 >= 0;

            bool allNegative =
                edge0 <= 0 &&
                edge1 <= 0 &&
                edge2 <= 0;

            if (allPositive || allNegative)
            {
                framebuffer.setPixel(x, y, color);
            }
        }
    }
}
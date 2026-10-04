#include "Rasterizer.h"
#include "Framebuffer.h"
#include "Color.h"

#include <cstdlib>


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
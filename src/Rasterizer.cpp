#include "Rasterizer.h"
#include "Framebuffer.h"
#include "Color.h"

#include <cmath>
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
    }
}
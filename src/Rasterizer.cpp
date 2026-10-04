#include "Rasterizer.h"
#include "Framebuffer.h"
#include "Color.h"

#include <cmath>

void drawLine(
    Framebuffer& framebuffer,
    int x0,
    int y0,
    int x1,
    int y1,
    Color color
)
{
    if (x0 > x1)
    {
        int temp = x0;
        x0 = x1;
        x1 = temp;

        temp = y0;
        y0 = y1;
        y1 = temp;
    }

    if (x0 == x1)
    {
        for (int i = y0; i < y1; ++i)
        {
            framebuffer.setPixel(x0, i, color);
        }

        return;
    }

    double slope =
    static_cast<double>(y1 - y0)
    /
    static_cast<double>(x1 - x0);

    for (int x = x0; x <= x1; ++x)
    {
        double y = y0 + (x - x0) * slope;
        int pixelY = static_cast<int>(std::round(y));
        framebuffer.setPixel(x, pixelY, color);
    }


}
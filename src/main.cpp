//F7 build
//ctrl shift f5 run without debugging
#include <iostream>


#include "Framebuffer.h"
#include "Rasterizer.h"

int main()
{
    Framebuffer framebuffer(200, 150);

    Color red = {255, 0, 0};
    Color green = {0, 255, 0};
    Color blue = {0, 0, 255};
    Color white = {255, 255, 255};
    Color black = {0, 0, 0};

    framebuffer.clear(black);

    drawLine(framebuffer, 70, 20, 90, 130, white);

    if (framebuffer.savePPM("output.ppm"))
        {
            std::cout << "Framebuffer saved successfully.\n";
        }

        else
        {
            std::cout << "Framebuffer save failed.\n";
        }

    return 0;
}
//F7 build
//ctrl shift f5 run without debugging
#include <iostream>
# include "Framebuffer.h"

int main()
{
    Framebuffer framebuffer(8, 6);

    Color red = {255, 0, 0};
    Color green = {0, 255, 0};
    Color blue = {0, 0, 255};
    Color white = {255, 255, 255};
    Color black = {0, 0, 0};

    framebuffer.clear(black);

    framebuffer.setPixel(2, 0, red);
    framebuffer.setPixel(2, 1, red);
    framebuffer.setPixel(2, 2, red);
    framebuffer.setPixel(2, 3, blue);
    framebuffer.setPixel(2, 4, blue);
    framebuffer.setPixel(2, 5, blue);

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
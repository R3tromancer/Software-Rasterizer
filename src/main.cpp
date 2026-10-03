//F7 build
//ctrl shift f5 run without debugging
#include <iostream>
# include "Framebuffer.h"

int main()
{
    Framebuffer framebuffer(4, 3);

    Color red = {255, 0, 0};
    Color green = {0, 255, 0};
    Color blue = {0, 0, 255};

    framebuffer.setPixel(0, 0, green);
    framebuffer.setPixel(3, 1, blue);
    framebuffer.setPixel(1, 2, red);

    if (framebuffer.savePPM("output.ppm"))
        {
            std::cout << "Framebuffer saved successfully.\n";
        }

        else
        {
            std::cout << "Framebuffer save failed.\n";
        }

    Color result = framebuffer.getPixel(1, 2);

    std::cout << "R: " << static_cast<int>(result.r) << '\n';
    std::cout << "G: " << static_cast<int>(result.g) << '\n';
    std::cout << "B: " << static_cast<int>(result.b) << '\n';


    std::cout << "Hello, Reza!" << std::endl;

    return 0;
}
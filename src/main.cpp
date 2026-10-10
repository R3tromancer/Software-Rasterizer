#include "Color.h"
#include "Display.h"
#include "Framebuffer.h"
#include "Rasterizer.h"
#include "math/Geometry2D.h"

#include <iostream>

int main()
{
    constexpr int width = 800;
    constexpr int height = 600;

    Framebuffer framebuffer(width, height);
    Display display(width, height);

    Color black{0, 0, 0};
    Color white{255, 255, 255};

    geometry2d::BarycentricCoordinates weights{};

    bool valid =
        geometry2d::tryCalculateBarycentricCoordinates(
            1, 1,
            5, 1,
            3, 4,
            3, 2,
            weights);

    if (valid)
    {
        std::cout << weights.alpha << '\n';
        std::cout << weights.beta << '\n';
        std::cout << weights.gamma << '\n';
    }
    else
    {
        std::cout << "Degenerate triangle\n";
    }

    while (display.isRunning())
    {
        display.processEvents();

        framebuffer.clear(black);

        drawTriangle(
            framebuffer,
            300, 100,
            600, 150,
            350, 450,
            white);

        drawTriangle(
            framebuffer,
            100, 500,
            400, 50,
            250, 300,
            white);

        display.present(framebuffer);
    }

    return 0;
}
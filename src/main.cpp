#include "Color.h"
#include "Display.h"
#include "Framebuffer.h"
#include "Rasterizer.h"
#include "math/Geometry2D.h"

#include <iostream>
#include <cmath>

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
            3, 3,
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

    std::cout << "Sum: "
              << weights.alpha + weights.beta + weights.gamma
              << '\n';

    const Color colorA{255, 0, 0};
    const Color colorB{0, 255, 0};
    const Color colorC{0, 0, 255};

    const Color testA{255, 0, 0};
    const Color testB{0, 255, 0};
    const Color testC{0, 0, 255};

    const Color centerColor = interpolateColor(
        testA, testB, testC,
        1.0 / 3.0,
        1.0 / 3.0,
        1.0 / 3.0);

    std::cout
        << static_cast<int>(centerColor.r) << ' '
        << static_cast<int>(centerColor.g) << ' '
        << static_cast<int>(centerColor.b) << '\n';

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
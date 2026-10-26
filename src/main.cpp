#include "Color.h"
#include "Display.h"
#include "Framebuffer.h"
#include "Rasterizer.h"
#include "math/Geometry2D.h"
#include "math/Vec3.h"
#include "math/Mat3.h"

#include <iostream>
#include <cmath>
#include <cassert>

int main()
{
    const Mat3 identity = identityMat3();
    const Vec3 original{2.0f, -3.0f, 5.0f};

    const Vec3 unchanged = identity * original;

    assert(unchanged.x == original.x);
    assert(unchanged.y == original.y);
    assert(unchanged.z == original.z);
    constexpr int width = 800;
    constexpr int height = 600;

    const Vec2 a{200.0f, 100.0f};
    const Vec2 b{600.0f, 150.0f};
    const Vec2 c{350.0f, 450.0f};

    Framebuffer framebuffer(width, height);
    Display display(width, height);

    Color black{0, 0, 0};
    Color white{255, 255, 255};

    geometry2d::BarycentricCoordinates weights{};

    const Vec3 f{1.0f, 2.0f, 3.0f};
    const Vec3 g{4.0f, 5.0f, 6.0f};

    const Vec3 sum = f + g;
    assert(sum.x == 5.0f && sum.y == 7.0f && sum.z == 9.0f);

    const Vec3 difference = g - f;
    assert(difference.x == 3.0f &&
           difference.y == 3.0f &&
           difference.z == 3.0f);

    const Vec3 scaled = f * 2.0f;
    assert(scaled.x == 2.0f &&
           scaled.y == 4.0f &&
           scaled.z == 6.0f);

    assert(dot(g, f) == 32.0f);

    assert(std::abs(length(f) - std::sqrt(14.0f)) < 1e-5f);
    assert(std::abs(length(normalize(f)) - 1.0f) < 1e-5f);

    bool valid =
        geometry2d::tryCalculateBarycentricCoordinates(
            200, 100,
            600, 150,
            350, 450,
            350, 200,
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

    Color point = interpolateColor(colorA, colorB, colorC, weights.alpha,
                                   weights.beta, weights.gamma);

    std::cout
        << static_cast<int>(point.r) << ' '
        << static_cast<int>(point.g) << ' '
        << static_cast<int>(point.b) << '\n';

    while (display.isRunning())
    {
        display.processEvents();

        framebuffer.clear(black);

        drawTriangle(
            framebuffer,
            {100, 500},
            {400, 50},
            {500, 300},
            point);

        drawTriangleInterpolated(
            framebuffer,
            a, b, c,
            colorA,
            colorB,
            colorC);

        display.present(framebuffer);
    }

    return 0;
}
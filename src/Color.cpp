#include "Color.h"

#include <cmath>
#include <algorithm>



Color interpolateColor(
    Color colorA,
    Color colorB,
    Color colorC,
    double alpha, // could be exchanged with barycentric type
    double beta,
    double gamma
)
{
    const double redChannel = 
    alpha * colorA.r +
    beta * colorB.r +
    gamma * colorC.r;
    const uint8_t red =
        static_cast<uint8_t>(
            std::clamp(std::lround(redChannel), 0L, 255L));

    const double greenChannel = 
    alpha * colorA.g +
    beta * colorB.g +
    gamma * colorC.g;
    const uint8_t green = 
        static_cast<uint8_t>(
            std::clamp(std::lround(greenChannel), 0L, 255L));

    const double blueChannel =
    alpha * colorA.b +
    beta * colorB.b +
    gamma * colorC.b;
    const uint8_t blue = 
        static_cast<uint8_t>(
            std::clamp(std::lround(blueChannel), 0L, 255L));

    return {red, green, blue};

}
#pragma once

#include <cstdint>

struct Color
{
    std::uint8_t r;
    std::uint8_t g;
    std::uint8_t b;
};

Color interpolateColor(
    Color colorA,
    Color colorB,
    Color colorC,
    double alpha, // could be exchanged with barycentric type
    double beta,
    double gamma
);

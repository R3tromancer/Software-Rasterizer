#pragma once
#include "math/Vec2.h"

class Framebuffer;

struct Color;

void drawLine(
    Framebuffer& framebuffer,
    int x0,
    int y0,
    int x1,
    int y1,
    Color color
);

void drawLine(
    Framebuffer& framebuffer,
    const Vec2& a,
    const Vec2& b,
    Color color
);

void drawTriangle(
    Framebuffer& framebuffer,
    const Vec2& a,
    const Vec2& b,
    const Vec2& c,
    Color color
);

void drawTriangleInterpolated(
    Framebuffer& framebuffer,
    const Vec2& a,
    const Vec2& b,
    const Vec2& c,
    Color colorA, Color colorB, Color colorC
);
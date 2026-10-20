#include "Rasterizer.h"
#include "Framebuffer.h"
#include "Color.h"
#include "math/Geometry2D.h"

#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cmath>

void drawLine(
    Framebuffer &framebuffer,
    int x0,
    int y0,
    int x1,
    int y1,
    Color color)
{
    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);

    int sx = (x1 > x0) ? 1 : -1;
    int sy = (y1 > y0) ? 1 : -1;

    int error = dx - dy;

    while (true)
    {
        framebuffer.setPixel(x0, y0, color);

        if (x0 == x1 && y0 == y1)
        {
            break;
        }

        int doubledError = 2 * error;

        if (doubledError > -dy)
        {
            error -= dy;
            x0 += sx;
        }

        if (doubledError < dx)
        {
            error += dx;
            y0 += sy;
        }
    }
    /*  DDA floating point line algo

     int dx = x1 - x0;
     int dy = y1 - y0;

     int steps = std::max(std::abs(dx), std::abs(dy));

     if(steps == 0)
     {
         framebuffer.setPixel(x0, y0, color);
     }

     double xStep = static_cast<double>(dx) / steps;
     double yStep = static_cast<double>(dy) / steps;

     double x = x0;
     double y = y0;

     for (int i = 0; i <= steps; ++i)
     {
         int pixelX = static_cast<int>(std::round(x));
         int pixelY = static_cast<int>(std::round(y));

         framebuffer.setPixel(pixelX, pixelY, color);

         x += xStep;
         y += yStep;
     } */
}

/*  empty triangle algo

    void drawTriangle(
    Framebuffer& framebuffer,
    int x0,
    int y0,
    int x1,
    int y1,
    int x2,
    int y2,
    Color color
)
{
    drawLine(framebuffer, x0, y0, x1, y1, color);
    drawLine(framebuffer, x1, y1, x2, y2, color);
    drawLine(framebuffer, x2, y2, x0, y0, color);
}
 */

void drawTriangle(
    Framebuffer &framebuffer,
    const Vec2 &a,
    const Vec2 &b,
    const Vec2 &c,
    Color color)
{

    const double signedArea = geometry2d::edgeFunction(a, b, c);
    if (signedArea == 0)
    {
        return;
    }

    int minX = std::max(
        0, static_cast<int>(std::ceil(std::min({a.x, b.x, c.x}))));

    int maxX = std::min(
        framebuffer.getWidth() - 1,
        static_cast<int>(std::floor(std::max({a.x, b.x, c.x}))));

    int minY = std::max(
        0, static_cast<int>(std::ceil(std::min({a.y, b.y, c.y}))));

    int maxY = std::min(
        framebuffer.getHeight() - 1,
        static_cast<int>(std::floor(std::max({a.y, b.y, c.y}))));

    const Vec2 firstSample{
        static_cast<float>(minX),
        static_cast<float>(minY)};

    double edge0Start =
        geometry2d::edgeFunction(a, b, firstSample);

    double edge1Start =
        geometry2d::edgeFunction(b, c, firstSample);

    double edge2Start =
        geometry2d::edgeFunction(c, a, firstSample);

    const double edge0XStep = -(b.y - a.y);
    const double edge0YStep = b.x - a.x;

    const double edge1XStep = -(c.y - b.y);
    const double edge1YStep = c.x - b.x;

    const double edge2XStep = -(a.y - c.y);
    const double edge2YStep = a.x - c.x;

    double edge0 = edge0Start;
    double edge1 = edge1Start;
    double edge2 = edge2Start;

    for (int y = minY; y <= maxY; ++y)
    {
        for (int x = minX; x <= maxX; ++x)
        {
            bool isAllCheckPos =
                (edge0Start >= 0 && edge1Start >= 0 && edge2Start >= 0);

            bool isAllCheckNeg =
                (edge0Start <= 0 && edge1Start <= 0 && edge2Start <= 0);

            if (isAllCheckPos || isAllCheckNeg)
            {
                framebuffer.setPixel(x, y, color);
            }

            edge0Start += edge0XStep;
            edge1Start += edge1XStep;
            edge2Start += edge2XStep;
        }

        edge0Start = edge0;
        edge1Start = edge1;
        edge2Start = edge2;

        edge0 += edge0YStep;
        edge1 += edge1YStep;
        edge2 += edge2YStep;
    }
}

void drawTriangleInterpolated(
    Framebuffer &framebuffer,
    const Vec2& a,
    const Vec2& b,
    const Vec2& c,
    Color color0, Color color1, Color color2)
{

    const double signedArea = geometry2d::edgeFunction(a, b, c);
    if (signedArea == 0)
    {
        return;
    }

    int minX = std::max(
        0, static_cast<int>(std::ceil(std::min({a.x, b.x, c.x}))));

    int maxX = std::min(
        framebuffer.getWidth() - 1,
        static_cast<int>(std::floor(std::max({a.x, b.x, c.x}))));

    int minY = std::max(
        0, static_cast<int>(std::ceil(std::min({a.y, b.y, c.y}))));

    int maxY = std::min(
        framebuffer.getHeight() - 1,
        static_cast<int>(std::floor(std::max({a.y, b.y, c.y}))));

    const Vec2 firstSample{
        static_cast<float>(minX),
        static_cast<float>(minY)};

    double edge0Start =
        geometry2d::edgeFunction(a, b, firstSample);

    double edge1Start =
        geometry2d::edgeFunction(b, c, firstSample);

    double edge2Start =
        geometry2d::edgeFunction(c, a, firstSample);

    const double edge0XStep = -(b.y - a.y);
    const double edge0YStep = b.x - a.x;

    const double edge1XStep = -(c.y - b.y);
    const double edge1YStep = c.x - b.x;

    const double edge2XStep = -(a.y - c.y);
    const double edge2YStep = a.x - c.x;

    double edge0 = edge0Start;
    double edge2 = edge2Start;
    double edge1 = edge1Start;

    for (int y = minY; y <= maxY; ++y)
    {
        for (int x = minX; x <= maxX; ++x)
        {
            bool isAllCheckPos =
                (edge0Start >= 0 && edge1Start >= 0 && edge2Start >= 0);

            bool isAllCheckNeg =
                (edge0Start <= 0 && edge1Start <= 0 && edge2Start <= 0);

            if (isAllCheckPos || isAllCheckNeg)
            {
                geometry2d::BarycentricCoordinates weights{};
                weights.alpha = static_cast<double>(edge1Start) / signedArea;
                weights.beta = static_cast<double>(edge2Start) / signedArea;
                weights.gamma = static_cast<double>(edge0Start) / signedArea;

                Color color = interpolateColor(color0, color1, color2,
                weights.alpha, weights.beta, weights.gamma);

                framebuffer.setPixel(x, y, color);
            }

            edge0Start += edge0XStep;
            edge1Start += edge1XStep;
            edge2Start += edge2XStep;
        }

        edge0Start = edge0;
        edge1Start = edge1;
        edge2Start = edge2;

        edge0 += edge0YStep;
        edge1 += edge1YStep;
        edge2 += edge2YStep;
    }
}
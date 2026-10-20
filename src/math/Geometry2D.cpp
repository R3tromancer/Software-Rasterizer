
#include "Geometry2D.h"

namespace geometry2d
{
    long long edgeFunction(
        int ax, int ay,
        int bx, int by,
        int px, int py)
    {
        return
            (static_cast<long long>(bx) - ax) * (py - ay)
            -
            (static_cast<long long>(by) - ay) * (px - ax);
    }

    double edgeFunction(
        const Vec2& a,
        const Vec2& b,
        const Vec2& p)
    {
        const double abx = static_cast<double>(b.x) - a.x;
        const double aby = static_cast<double>(b.y) - a.y;
        const double apx = static_cast<double>(p.x) - a.x;
        const double apy = static_cast<double>(p.y) - a.y;

        return abx * apy - aby * apx;
    }

    bool tryCalculateBarycentricCoordinates(
        int ax, int ay,
        int bx, int by,
        int cx, int cy,
        int px, int py,
        BarycentricCoordinates& result)
    {
        const long long area =
            edgeFunction(ax, ay, bx, by, cx, cy);

        if (area == 0)
            return false;

        result.alpha = static_cast<double>(
            edgeFunction(bx, by, cx, cy, px, py)) / area;

        result.beta = static_cast<double>(
            edgeFunction(cx, cy, ax, ay, px, py)) / area;

        result.gamma = static_cast<double>(
            edgeFunction(ax, ay, bx, by, px, py)) / area;

        return true;
    }

    bool tryCalculateBarycentricCoordinates(
        const Vec2& a,
        const Vec2& b,
        const Vec2& c,
        const Vec2& p,
        BarycentricCoordinates& result)
    {
        const double area = edgeFunction(a, b, c);

        if (area == 0.0)
            return false;

        result.alpha = edgeFunction(b, c, p) / area;
        result.beta  = edgeFunction(c, a, p) / area;
        result.gamma = edgeFunction(a, b, p) / area;

        return true;
    }
}

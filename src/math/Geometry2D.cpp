#include "Geometry2D.h"


namespace geometry2d
{
    long long edgeFunction(
        int ax, int ay,
        int bx, int by,
        int px, int py
    )
    {
        return 
        static_cast<long long>((bx - ax) * (py - ay))
        -
        static_cast<long long>((by - ay) * (px - ax));
    }

    bool tryCalculateBarycentricCoordinates(
        int ax, int ay,
        int bx, int by,
        int cx, int cy,
        int px, int py,
        BarycentricCoordinates& result
    )
    {
        long long area = edgeFunction(ax, ay, bx, by, cx, cy);

        if (area == 0)
        {
            return false;
        }

        result.alpha = static_cast<double>(
            edgeFunction(bx, by, cx, cy, px, py)) / area;
        result.beta  = static_cast<double>(
            edgeFunction(cx, cy, ax, ay, px, py)) / area;

        result.gamma = static_cast<double>(
            edgeFunction(ax, ay, bx, by, px, py)) / area;

        return true;

    }
}
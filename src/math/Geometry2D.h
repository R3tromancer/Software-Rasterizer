#pragma once
#include "Vec2.h"


namespace geometry2d
{
    long long edgeFunction(
        int ax, int ay,
        int bx, int by,
        int cx, int cy
    );

    double edgeFunction(
        const Vec2& a,
        const Vec2& b,
        const Vec2& p
    );


    struct BarycentricCoordinates
    {
        double alpha;
        double beta;
        double gamma;
    };

    bool tryCalculateBarycentricCoordinates(
        int ax, int ay,
        int bx, int by,
        int cx, int cy,
        int px, int py,
        BarycentricCoordinates& result
    );

    bool tryCalculateBaryCentricCoordinates(
        const Vec2& a,
        const Vec2& b,
        const Vec2& c,
        const Vec2& p,
        BarycentricCoordinates& result
    );

}
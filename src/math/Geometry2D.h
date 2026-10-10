#pragma once


namespace geometry2d
{
    long long edgeFunction(
        int ax, int ay,
        int bx, int by,
        int cx, int cy
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
        BarycentricCoordinates& bcResult
    );

}
#include "Geometry2D.h"


namespace geometry2D
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
}
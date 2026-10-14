#include "Vec2.h"


Vec2 operator-(const Vec2& a, const Vec2& b)
{
    return {a.x - b.x , a.y - b.y};
}
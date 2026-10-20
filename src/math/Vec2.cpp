#include "Vec2.h"
#include <cmath>
#include <stdexcept>

Vec2 operator-(const Vec2& a, const Vec2& b)
{
    return {a.x - b.x , a.y - b.y};
}

Vec2 operator+(const Vec2& a, const Vec2& b)
{
    return {a.x + b.x , a.y + b.y};
}

float dot(const Vec2& a, const Vec2& b)
{
    return a.x * b.x + a.y * b.y;
}

float length(const Vec2& vec)
{
    return std::sqrt(dot(vec, vec));
}

Vec2 operator/(const Vec2& vec, float scalar)
{
    if(scalar == 0)
    {
        throw std::invalid_argument("Cannot divide a vector by zero");
    }

    return {vec.x / scalar, vec.y / scalar};
}

Vec2 normalize(const Vec2& vec)
{
    const float magnitude = length(vec);
    
    if(magnitude == 0)
    {
        throw std::invalid_argument("Cannot normalize a zero vector");
    }

    return vec / magnitude;
}
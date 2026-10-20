#include "Vec3.h"

#include <cmath>
#include <stdexcept>

Vec3 operator+(const Vec3& a, const Vec3& b)
{
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

Vec3 operator-(const Vec3& a, const Vec3& b)
{
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

Vec3 operator*(const Vec3& vec, float scalar)
{
    return {vec.x * scalar, vec.y * scalar, vec.z * scalar};
}

Vec3 operator*(float scalar, const Vec3& vec)
{
    return vec * scalar;
}

Vec3 operator/(const Vec3& vec, float scalar)
{
    if (scalar == 0)
    {
        throw std::invalid_argument("Cannot divide by zero");
    }

    return {vec.x / scalar, vec.y / scalar, vec.z / scalar};
}

float dot (const Vec3& a, const Vec3& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float length (const Vec3& vec)
{
    return std::sqrt(dot(vec, vec));
}


Vec3 normalize(const Vec3& vec)
{
    return vec / length(vec);
}


Vec3 cross(const Vec3& a, const Vec3& b)
{
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}



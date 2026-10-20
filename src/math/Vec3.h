#pragma once


struct Vec3
{
    float x;
    float y;
    float z;
};

Vec3 operator+(const Vec3& a, const Vec3& b);
Vec3 operator-(const Vec3& a, const Vec3& b);
Vec3 operator*(const Vec3& vec, float scalar);
Vec3 operator*(float scalar, const Vec3& vec);
Vec3 operator/(const Vec3& vec, float scalar);
float   dot   (const Vec3& a, const Vec3& b);
float length  (const Vec3& vec);
Vec3 normalize(const Vec3& vec);
Vec3 cross(const Vec3& a, const Vec3& b);
#pragma once

#include "Vec3.h"

struct Mat3
{
    float m[3][3];
};

Mat3 identityMatrix();

Vec3 operator*(const Mat3& matrix, const Vec3& vector);
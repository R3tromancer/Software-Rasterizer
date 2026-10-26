#include "Mat3.h"
#include <cmath>

Mat3 identityMat3()
{
    Mat3 result{};

    result.m[0][0] = 1.0f;
    result.m[1][1] = 1.0f;
    result.m[2][2] = 1.0f;

    return result;

}

Mat3 rotationZ(float radians)
{
    const float cosine = std::cos(radians);
    const float sine = std::sin(radians);

    Mat3 result{};

    result.m[0][0] = cosine;
    result.m[0][1] = -sine;

    result.m[1][0] = sine;
    result.m[1][1] = cosine;

    result.m[2][2] = 1.0f;

    return result;
}


Vec3 operator*(const Mat3& matrix, const Vec3& vector)
{
    return {
            matrix.m[0][0] * vector.x
          + matrix.m[0][1] * vector.y
          + matrix.m[0][2] * vector.z,

            matrix.m[1][0] * vector.x
          + matrix.m[1][1] * vector.y
          + matrix.m[1][2] * vector.z,

            matrix.m[2][0] * vector.x
          + matrix.m[2][1] * vector.y
          + matrix.m[2][2] * vector.z
    };
}
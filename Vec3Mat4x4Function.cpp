#include "Vec3Mat4x4Function.h"
#include <assert.h>
Matrix4x4 MakeTranslateMatrix(const Vector3& translate)
{
   
    return Matrix4x4({
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        translate.x,translate.y,translate.z,1
        });
}
Matrix4x4 MakeScaleMatrix(const Vector3& scale)
{
    return Matrix4x4({
        scale.x,0,0,0,
        0,scale.y,0,0,
        0,0,scale.z,0,
        0,0,0,1
        });
}
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix)
{
    Vector3 result{};
    result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
    result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
    result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
    float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];
    assert(w != 0);

    result.x /= w;
    result.y /= w;
    result.z /= w;
    return result;
}

Matrix4x4 MakeRotateXYZMatrix(const Vector3& rotate)
{
    Matrix4x4 mXYZ = Multiply(MakeRotateXMatrix(rotate.x), Multiply(MakeRotateYMatrix(rotate.y), MakeRotateZMatrix(rotate.z)));
    return mXYZ;
}

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate)
{

    Matrix4x4 resultMatrix{};
    Matrix4x4 rotateMatrix=MakeRotateXYZMatrix(rotate);

    resultMatrix.m[0][0] = scale.x * rotateMatrix.m[0][0];
    resultMatrix.m[0][1] = scale.x * rotateMatrix.m[0][1];
    resultMatrix.m[0][2] = scale.x * rotateMatrix.m[0][2];

    resultMatrix.m[1][0] = scale.y * rotateMatrix.m[1][0];
    resultMatrix.m[1][1] = scale.y * rotateMatrix.m[1][1];
    resultMatrix.m[1][2] = scale.y * rotateMatrix.m[1][2];

    resultMatrix.m[2][0] = scale.z * rotateMatrix.m[2][0];
    resultMatrix.m[2][1] = scale.z * rotateMatrix.m[2][1];
    resultMatrix.m[2][2] = scale.z * rotateMatrix.m[2][2];

    resultMatrix.m[3][0] = translate.x;
    resultMatrix.m[3][1] = translate.y;
    resultMatrix.m[3][2] = translate.z;
    resultMatrix.m[3][3] = 1;
    return resultMatrix;
}

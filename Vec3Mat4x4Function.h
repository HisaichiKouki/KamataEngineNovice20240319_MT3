#pragma once
#include "Vector3Math.h"
#include "Matrix4x4Function.h"

Matrix4x4 MakeTranslateMatrix(const Vector3& translate);
Matrix4x4 MakeScaleMatrix(const Vector3& scale);

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);
Matrix4x4 MakeRotateXYZMatrix(const Vector3& rotate);
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

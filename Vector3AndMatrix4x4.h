#pragma once
#include <Novice.h>
#include <Vector3.h>
#include <Matrix4x4.h>
#include<cmath>


static const int kColumWidth = 60;
static const int kRowHeight = 20;

/// <summary>
/// tangentの逆数 cosf(a)/sinf(a)
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns></returns>
float cotf(float a);

//Vector3Math
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

Vector3 Add(const Vector3& v1, const Vector3& v2);
Vector3 Subtract(const Vector3& v1, const Vector3& v2);
Vector3 Multiply(float scalar, const Vector3& v);
float Dot(const Vector3& v1, const Vector3& v2);
float Length(const Vector3& v);
float Length(const Vector3& v1,const Vector3& v2);
Vector3 Normalize(const Vector3& v);

Vector3 Cross(const Vector3& v1, const Vector3& v2);

//Matrix4x4Function
struct Matrix4x8
{
	float e[4][8];

};

void Matrix4x4ScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);

Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 Inverse(const Matrix4x4& m);
Matrix4x4 Transpose(const Matrix4x4& m);
Matrix4x4 MakeIdentity4x4();

Matrix4x4 MakeRotateXMatrix(float radian);
Matrix4x4 MakeRotateYMatrix(float radian);
Matrix4x4 MakeRotateZMatrix(float radian);

Matrix4x4 MakeRotateXYZMatrix(float radianX, float radianY, float radianZ);

//Vec3Mat4x4Function
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);
Matrix4x4 MakeScaleMatrix(const Vector3& scale);

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);
Matrix4x4 MakeRotateXYZMatrix(const Vector3& rotate);
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

//透視射影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

//正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

//ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

Vector3 TransformNomal(const Vector3& v, const Matrix4x4& m);

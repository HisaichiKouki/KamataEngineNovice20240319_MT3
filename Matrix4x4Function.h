#pragma once
#include <Novice.h>
#include<cmath>
#include "Matrix4x4.h"

struct Matrix4x8
{
	float e[4][8];

};

static const int kRowheight = 20;
static const int kColWidth = 60;

void Matrix4x4ScreenPrintf(int x, int y, const Matrix4x4& matrix,const char* label);

Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 Inverse(const Matrix4x4& m);
Matrix4x4 Transpose(const Matrix4x4& m);
Matrix4x4 MakeIdentity4x4();

Matrix4x4 MakeRotateXMatrix(float radian);
Matrix4x4 MakeRotateYMatrix(float radian);
Matrix4x4 MakeRotateZMatrix(float radian);

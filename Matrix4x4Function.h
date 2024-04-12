#pragma once
#include <Novice.h>
struct Matrix4x4
{
	float m[4][4];
};

static const int kRowheight = 20;
static const int kColWidth = 60;

void Matrix4x4ScreenPrintf(int x, int y, const Matrix4x4& matrix,const char* label);

Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
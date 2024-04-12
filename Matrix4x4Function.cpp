#include "Matrix4x4Function.h"

void Matrix4x4ScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label)
{
	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			Novice::ScreenPrintf(x + col * kColWidth, y + (row + 1) * kRowheight, "%6.02f", matrix.m[row][col]);
		}
	}

}

Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 resultMatrix = {};
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			resultMatrix.m[row][col] = m1.m[row][col] + m2.m[row][col];

		}
	}
	return resultMatrix;
}

Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 resultMatrix = {};
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			resultMatrix.m[row][col] = m1.m[row][col] - m2.m[row][col];

		}
	}
	return resultMatrix;
}

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 resultMatrix = {};
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{			
			for (int z = 0; z < 4; z++)
			{
				resultMatrix.m[row][col] += m1.m[row][z] * m2.m[z][col];
			}
		}
	}
	return resultMatrix;
}

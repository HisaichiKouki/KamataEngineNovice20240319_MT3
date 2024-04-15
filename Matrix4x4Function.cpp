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

Matrix4x4 Inverse(const Matrix4x4& m)
{
	
	Matrix4x8 augmented{
	0,0,0,0,1,0,0,0,
	0,0,0,0,0,1,0,0,
	0,0,0,0,0,0,1,0,
	0,0,0,0,0,0,0,1
	};
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			augmented.e[row][col] = m.m[row][col];
		}		
	}

	for (int row = 0; row < 4; row++)
	{
		float pivot = augmented.e[row][row];

		for (int col = 0; col < 8; col++)
		{
			augmented.e[row][col] /= pivot;
		}

		for (int k = 0; k < 4; k++)
		{
			if (k!=row)
			{
				float factor = augmented.e[k][row];
				for (int col = 0; col < 8; col++)
				{
					augmented.e[k][col] -= factor * augmented.e[row][col];
				}
			}
		}
	}

	return Matrix4x4({
		augmented.e[0][4],augmented.e[0][5],augmented.e[0][6],augmented.e[0][7],
		augmented.e[1][4],augmented.e[1][5],augmented.e[1][6],augmented.e[1][7],
		augmented.e[2][4],augmented.e[2][5],augmented.e[2][6],augmented.e[2][7],
		augmented.e[3][4],augmented.e[3][5],augmented.e[3][6],augmented.e[3][7],
		});
	
}

Matrix4x4 Transpose(const Matrix4x4& m)
{
	Matrix4x4 result{};

	for (int row = 0; row < 4; row++)
	{
		
		for (int col = 0; col < 4; col++)
		{
			result.m[row][col] = m.m[col][row];
			if (row==col)
			{
				result.m[row][col]= m.m[row][col];
			}
		}
	}
	return result;
}

Matrix4x4 MakeIdentity4x4()
{
	return Matrix4x4({
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
		});
}

Matrix4x4 MakeRotateXMatrix(float radian)
{
	return Matrix4x4({
		1,0,0,0,
		0,std::cosf(radian),std::sinf(radian),0,
		0,-std::sinf(radian),std::cosf(radian),0,
		0,0,0,1

		});
}

Matrix4x4 MakeRotateYMatrix(float radian)
{
	return Matrix4x4({
		std::cosf(radian),0,-std::sinf(radian),0,
		0,1,0,0,
		std::sinf(radian),0,std::cosf(radian),0,
		0,0,0,1
		});
}

Matrix4x4 MakeRotateZMatrix(float radian)
{
	return Matrix4x4({
		std::cosf(radian),std::sinf(radian),0,0,
		-std::sinf(radian),std::cosf(radian),0,0,
		0,0,1,0,
		0,0,0,1
		});
}

Matrix4x4 MakeRotateXYZMatrix(float radianX, float radianY, float radianZ)
{
	Matrix4x4 mX = MakeRotateXMatrix(radianX);
	Matrix4x4 mY = MakeRotateYMatrix(radianY);
	Matrix4x4 mZ = MakeRotateZMatrix(radianZ);
	Matrix4x4 mXYZ = Multiply(mX, Multiply(mY, mZ));
	return mXYZ;
}

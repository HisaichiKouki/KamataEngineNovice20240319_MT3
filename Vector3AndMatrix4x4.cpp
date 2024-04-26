#include "Vector3AndMatrix4x4.h"
#include <assert.h>
float cotf(float a)
{
	return cosf(a)/sinf(a);
}
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label)
{
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumWidth * 3, y, ":%s", label);
}

Vector3 Add(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vector3 Subtract(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vector3 Multiply(float scalar, const Vector3& v)
{
	return Vector3(v.x * scalar, v.y * scalar, v.z * scalar);
}

float Dot(const Vector3& v1, const Vector3& v2)
{
	float result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return result;
}

float Length(const Vector3& v)
{
	if (v.x == 0 && v.y == 0 && v.z == 0)
	{
		return 0;
	}
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

float Length(const Vector3& v1, const Vector3& v2)
{
	Vector3 result{ };
	result = Subtract(v1, v2);
	
	return sqrtf(result.x * result.x + result.y * result.y + result.z * result.z);
}

Vector3 Normalize(const Vector3& v)
{
	float length = Length(v);
	return Vector3(v.x / length, v.y / length, v.z / length);
}

Vector3 Cross(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.y*v2.z-v1.z*v2.y,v1.z*v2.x-v1.x*v2.z,v1.x*v2.y-v1.y*v2.x);
}

void Matrix4x4ScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label)
{
	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			Novice::ScreenPrintf(x + col * kColumWidth, y + (row + 1) * kRowHeight, "%6.02f", matrix.m[row][col]);
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
			if (k != row)
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
			if (row == col)
			{
				result.m[row][col] = m.m[row][col];
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
	if(w == 0)return Vector3(0,0,0);

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
	Matrix4x4 rotateMatrix = MakeRotateXYZMatrix(rotate);

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

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip)
{
	Matrix4x4 resultMatrix{};
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			resultMatrix.m[y][x] = 0.0f;
		}
	}
	//tanf/(-1)=cottangent
	resultMatrix.m[0][0] = (1.0f / aspectRatio) * cotf(fovY/2.0f);
	resultMatrix.m[1][1] = cotf(fovY/2.0f);
	resultMatrix.m[2][2] = farClip/(farClip-nearClip);
	resultMatrix.m[2][3] = 1;
	resultMatrix.m[3][2] = (-nearClip*farClip)/(farClip-nearClip);
	return resultMatrix;
}

Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip)
{
	Matrix4x4 resultMatrix{};
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			resultMatrix.m[y][x] = 0.0f;
		}
	}

	resultMatrix.m[0][0] = 2 / (right - left);
	resultMatrix.m[1][1] = 2 / (top - bottom);
	resultMatrix.m[2][2] = 1 / (farClip - nearClip);
	resultMatrix.m[3][0] = (left + right) / (left - right);
	resultMatrix.m[3][1] = (top + bottom) / (bottom - top);
	resultMatrix.m[3][2] = nearClip / (nearClip - farClip);
	resultMatrix.m[3][3] = 1.0f;

	return resultMatrix;
}

Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth)
{
	Matrix4x4 resultMatrix{};
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			resultMatrix.m[y][x] = 0.0f;
		}
	}
	resultMatrix.m[0][0] = width / 2.0f;
	resultMatrix.m[1][1] = -height / 2.0f;
	resultMatrix.m[2][2] = maxDepth-minDepth;
	resultMatrix.m[3][0] = left+width/2.0f;
	resultMatrix.m[3][1] = top+height/2.0f;
	resultMatrix.m[3][2] = minDepth;
	resultMatrix.m[3][3] = 1.0f;

	return resultMatrix;
}

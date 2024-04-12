#include "Vector3Math.h"
#include <math.h>

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label)
{
	Novice::ScreenPrintf(x, y, "%0.2f", vector.x);
	Novice::ScreenPrintf(x+kColumwidth, y, "%0.2f", vector.y);
	Novice::ScreenPrintf(x+kColumwidth*2, y, "%0.2f", vector.z);
	Novice::ScreenPrintf(x+kColumwidth*3, y, ":%s", label);
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
	if (v.x==0&&v.y==0&&v.z==0)
	{
		return 0;
	}
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector3 Normalize(const Vector3& v)
{
	float length = Length(v);
	return Vector3(v.x/ length,v.y/ length,v.z/ length);
}

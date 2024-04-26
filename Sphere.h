#pragma once
#include "Vector3AndMatrix4x4.h"
struct Sphere
{
	Matrix4x4 worldMatrix;
	Vector3 centor;
	Vector3 rotate;
	float radius;
};
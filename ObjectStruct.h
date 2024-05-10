#pragma once
#include "Vector3AndMatrix4x4.h"
struct Sphere
{
	Vector3 centor;
	float radius;
	Vector3 rotate;
	Matrix4x4 worldMatrix;

};

struct Line
{
	Vector3 origin;
	Vector3 diff;
};

struct Ray
{
	Vector3 origin;
	Vector3 diff;
};

struct Segment
{
	Vector3 origin;
	Vector3 diff;
};
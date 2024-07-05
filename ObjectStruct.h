#pragma once
#include "Vector3AndMatrix4x4.h"
#include <Vector2.h>
struct Sphere
{
	Vector3 center;
	float radius;
	//Vector3 rotate;
	//Matrix4x4 worldMatrix;

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

struct Plane
{
	Vector3 normal;
	float distance;
};
struct Triangle
{
	
	Vector3 vertices[3];

};

struct AABB
{
	Vector3 min;
	Vector3 max;

	
};

struct OBB
{
	Vector3 center;
	Vector3 orientations[3];
	Vector3 size;
};

struct Spring {
	Vector3 anchor;
	float naturalLength;
	float stiffness;
	float dampingCoefficient;
};

struct Ball
{
	Vector3 position;
	Vector3 velocity;
	Vector3 aceleration;
	float mass;
	float radius;
	unsigned int color;
};
#pragma once
#include <Novice.h>

#include "Vector3AndMatrix4x4.h"
#include "ObjectStruct.h"
#include "Glid.h"
#include <memory>

class SpringClas
{
public:
	SpringClas();
	void Init();
	void Update();
	void Draw(const Matrix4x4& viewProjectionMat, const Matrix4x4& viewportMat);
	void SetGravity(const Vector3& set) { gravity = set; }
private:


	Ball ball;
	Spring spring;
	Vector3
		diff,
		direction,
		restPosition,
		displacement,
		restoringForce,
		force,
		dampingForce;

	float length,
		deltatime;

	Vector3 gravity;
};


#pragma once

#include <Novice.h>

#include "Vector3AndMatrix4x4.h"
#include "ObjectStruct.h"
#include "Glid.h"
#include <memory>
#include <imgui.h>

class CircleMotion
{
public:
	CircleMotion();
	void Init();
	void Update();
	void Draw(const Matrix4x4& viewProjectionMat, const Matrix4x4& viewportMat);
	void Debug();
private:
	Sphere sphere;
	Vector3 pos,
		centerPos,
		radius,
		velocity,
		aceleration;
	float anglarVelocity,
		angle,
		deltatime;
};


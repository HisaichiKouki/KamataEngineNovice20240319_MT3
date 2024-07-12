#pragma once

#include <Novice.h>

#include "Vector3AndMatrix4x4.h"
#include "ObjectStruct.h"
#include "Glid.h"
#include <memory>
#include <imgui.h>
class PendulumClass
{
public :
	PendulumClass();
	void Init();
	void Update();
	void Draw(const Matrix4x4& viewProjectionMat, const Matrix4x4& viewportMat);
private:
	Pendulum pendlum;
	float deltaTime;
	Vector3 pos;

	Sphere sphere;
};


#pragma once
#include <Novice.h>

#include "Vector3AndMatrix4x4.h"
#include "ObjectStruct.h"
#include "Glid.h"
#include <memory>
#include <imgui.h>
class ConicalPendulumClass
{
public:
	ConicalPendulumClass();
	void Init();
	void Update();
	void Draw(const Matrix4x4& viewProjectionMat, const Matrix4x4& viewportMat);
	void Debug();

private:
	ConicalPendulum cp;
	float t;
	Sphere sphere;
	float radius;
	float height;
	float deltaTime = 1.0f / 60.0f;
	bool isStart;
};

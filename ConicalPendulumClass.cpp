#include "ConicalPendulumClass.h"

ConicalPendulumClass::ConicalPendulumClass()
{
	Init();
}

void ConicalPendulumClass::Init()
{
	cp = {
		.anchor{0,1,0},
		.length{0.8f},
		.halfApexAngle{0.7f},
		.angle{0},
		.anglarVelocity{0}
	};
	sphere.radius = 0.05f;
	radius = std::sin(cp.halfApexAngle) * cp.length;
	height = std::cos(cp.halfApexAngle) * cp.length;
	sphere.center.x = cp.anchor.x + std::cos(cp.angle) * radius;
	sphere.center.y = cp.anchor.y - height;
	sphere.center.z = cp.anchor.z - std::sin(cp.angle) * radius;
	isStart = false;
}

void ConicalPendulumClass::Update()
{
	if (isStart)
	{
		cp.anglarVelocity = std::sqrtf(9.8f / cp.length * std::cos(cp.halfApexAngle));
		cp.angle += cp.anglarVelocity * deltaTime;
		radius = std::sin(cp.halfApexAngle) * cp.length;
		height = std::cos(cp.halfApexAngle) * cp.length;
		sphere.center.x = cp.anchor.x + std::cos(cp.angle) * radius;
		sphere.center.y = cp.anchor.y - height;
		sphere.center.z = cp.anchor.z - std::sin(cp.angle) * radius;

	}

}

void ConicalPendulumClass::Draw(const Matrix4x4& viewProjectionMat, const Matrix4x4& viewportMat)
{
	DrawLine3D(cp.anchor, sphere.center, viewProjectionMat, viewportMat, WHITE);
	DrawGridSphere(sphere, 12, viewProjectionMat, viewportMat, WHITE);
}

void ConicalPendulumClass::Debug()
{
	ImGui::Begin("ConicalPendulum");
	if (ImGui::Button("start")) {
		isStart = true;

		//strcpy(text1, "button 1");
	}
	ImGui::Text("isStart=%d", isStart);
	ImGui::Text("angle=%f ball.Pos=%f %f %f", cp.angle, sphere.center.x, sphere.center.y, sphere.center.z);
	ImGui::End();
}

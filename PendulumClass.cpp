#include "PendulumClass.h"

PendulumClass::PendulumClass()
{
}

void PendulumClass::Init()
{
	pendlum = {
	.anchor={0,1,0},
	.length=0.8f,
	.angle=0.7f,
	.anglarVelocity=0,
	.anglarAcceleration=0
	};
	deltaTime = 1.0f / 60.0f;
	sphere = {
		.center = {},
		.radius = 0.1f
	};
}

void PendulumClass::Update()
{
	pendlum.anglarAcceleration =
		-(9.8f / pendlum.length) * std::sin(pendlum.angle);
	pendlum.anglarVelocity += pendlum.anglarAcceleration * deltaTime;
	pendlum.angle += pendlum.anglarVelocity * deltaTime;

	pos.x = pendlum.anchor.x + std::sin(pendlum.angle) * pendlum.length;
	pos.y = pendlum.anchor.y- std::cos(pendlum.angle) * pendlum.length;
	pos.z = pendlum.anchor.z;
	sphere.center = pos;
}

void PendulumClass::Draw(const Matrix4x4& viewProjectionMat, const Matrix4x4& viewportMat)
{
	DrawGridSphere(sphere, 12, viewProjectionMat, viewportMat, WHITE);

}

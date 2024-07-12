#include "CircleMotion.h"

CircleMotion::CircleMotion()
{
	Init();
}

void CircleMotion::Init()
{
	deltatime = 1.0f / 60.0f;
	angle = 0.0f;
	anglarVelocity = 3.14f;
	centerPos = { 0,0,0 };
	pos = { 0.8f,0,0 };
	radius = { 0.8f,0.8f,0 };
	velocity = { 0,0,0 };
	aceleration = { 0,0,0 };

	sphere = {
		.center = pos,
		.radius = 0.1f
	};
}

void CircleMotion::Update()
{
	angle += anglarVelocity * deltatime;
	//position移動(物理演算を使ってない)
	/*pos.x = centerPos.x + std::cos(angle) * radius.x;
	pos.y = centerPos.y + std::sin(angle) * radius.y;
	pos.z = centerPos.z;*/
	aceleration.x = -(anglarVelocity * anglarVelocity) * radius.x;
	aceleration.y = -(anglarVelocity * anglarVelocity) * radius.y;

	
	velocity.x = -radius.x * anglarVelocity * std::sin(angle);
	velocity.y = radius.y * anglarVelocity * std::cos(angle);
	//velocity += aceleration;
	pos += velocity * deltatime;
	sphere.center = pos;

}

void CircleMotion::Draw(const Matrix4x4& viewProjectionMat, const Matrix4x4& viewportMat)
{
	DrawGridSphere(sphere, 12, viewProjectionMat, viewportMat, WHITE);
}

void CircleMotion::Debug()
{
#ifdef _DEBUG

	ImGui::Begin("CircleMotion");
	ImGui::Text("pos={%f,%f,%f}", pos.x, pos.y, pos.z);
	ImGui::Text("velocity={%f,%f,%f}", velocity.x, velocity.y, velocity.z);
	ImGui::Text("aceleration={%f,%f,%f}", aceleration.x, aceleration.y, aceleration.z);
	ImGui::End();
#endif // _DEBUG

}

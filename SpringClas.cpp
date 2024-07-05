#include "SpringClas.h"

SpringClas::SpringClas()
{
	Init();
}

void SpringClas::Init()
{
	ball = {
		.position{1.2f,0.0f,0.0f},
		.mass{2.0f},
		.radius{0.05f},
		.color{BLUE}
	};
	spring = {
		.anchor = {0.0f,0.0f,0.0f},
		.naturalLength{1.0f},
		.stiffness{100.0f}
	};

	diff = { 0,0,0 };
	direction = { 0,0,0 };
	restPosition = { 0,0,0 };
	displacement = { 0,0,0 };
	restoringForce = { 0,0,0 };
	force = { 0,0,0 };

	length = 0;
	deltatime = 1.0f / 60.0f;

}

void SpringClas::Update()
{
	diff = ball.position - spring.anchor;
	length = Length(diff);
	if (length!=0)
	{
		direction = Normalize(diff);
		restPosition = spring.anchor + direction * spring.naturalLength;
		displacement = (ball.position - restPosition)* length;
		restoringForce =  displacement* -spring.stiffness;
		force = restoringForce;
		ball.aceleration = force / ball.mass;
	}
	ball.velocity += ball.aceleration * deltatime;
	ball.position += ball.velocity * deltatime;
}

void SpringClas::Draw(const Matrix4x4& viewProjectionMat, const Matrix4x4& viewportMat)
{
	Segment segment;
	segment.origin = spring.anchor;
	segment.diff = ball.position;

	DrawSegment(segment, viewProjectionMat, viewportMat,WHITE);
	Sphere ballSphere;
	ballSphere.center = ball.position;
	ballSphere.radius = ball.radius;
	
	DrawGridSphere(ballSphere, 8, viewProjectionMat, viewportMat, BLUE);
}

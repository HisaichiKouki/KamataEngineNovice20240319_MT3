#include "Camera.h"



Camera::Camera(const Vector3& scale, const Vector3& rotate, const Vector3& translate)
{
	Init(scale, rotate, translate);
}

Camera::~Camera()
{
}



void Camera::Init(const Vector3& scale, const Vector3& rotate, const Vector3& translate)
{
	scale_ = scale;
	rotate_ = rotate;
	translate_ = translate;
}

void Camera::Update()
{
	cameraMatrix_ = MakeAffineMatrix(scale_, rotate_, translate_);
	viewMatrix_ = Inverse(cameraMatrix_);
}

void Camera::Draw()
{
}

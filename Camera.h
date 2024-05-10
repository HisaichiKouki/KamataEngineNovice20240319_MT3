#pragma once

#include "Vector3AndMatrix4x4.h"
class Camera
{

public:
	Camera();
	void Init();
	void Update();

	Matrix4x4 GetviewProjection() { return projectionMatrix; }
	Matrix4x4 GetViewportMatrix() { return viewportMatrix; }

private:

	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;

	Vector3 cameraRotate_;
	Vector3 cameraPosition_;

	Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate_, cameraPosition_);
	Matrix4x4 viewMatrix = Inverse(cameraMatrix);
	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
	Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
	Matrix4x4 viewProjection = Multiply(viewMatrix, projectionMatrix);

};


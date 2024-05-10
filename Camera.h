#pragma once

#include "Vector3AndMatrix4x4.h"
#include "InputManager.h"
#include "ObjectStruct.h"
#include <ImGuiManager.h>

class Camera
{

public:
	Camera();
	void Init();
	void Update();
	void Move();

	void DebugDraw();
	Matrix4x4 GetviewProjection() { return viewProjection; }
	Matrix4x4 GetViewportMatrix() { return viewportMatrix; }
	bool GetIsDebugMode() { return isDebugMode_; }
private:

	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;
	const float kMoveSpeed = 0.02f;
	const float kBoostMoveSpeed = 2.0f;
	const float kRotateSpeed = 0.006f;

	float isRotateSpeed_;
	float isMoveSpeed_;

	bool isDebugMode_;
	bool isFPSMode_;

	int mx_;
	int my_;
	int preMx_;
	int preMy_;

	float mouceRotateSpeed = 0.001f;
	

	Vector3 cameraMoveVector_;

	Vector3 cameraRotate_;
	Vector3 cameraPosition_;
	Vector3 cameraRay_;
 

	//Matrix4x4 rayMatrix_;
	


	Matrix4x4 cameraMatrix;
	Matrix4x4 viewMatrix;
	Matrix4x4 projectionMatrix;
	Matrix4x4 viewportMatrix;
	Matrix4x4 viewProjection;

};


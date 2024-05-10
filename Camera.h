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
	const float kMoveSpeed = 0.03f;
	const float kBoostMoveSpeed = 2.5f;
	const float kRotateSpeed = 0.006f;
	const float kMouceRotateSpeed = 0.001f;

	float isRotateSpeed_;
	float isMoveSpeed_;
	float isMouceRotateSpeed_;

	bool isDebugMode_;
	bool isFPSMode_;

	int mx_;
	int my_;
	int preMx_;
	int preMy_;
	float smoothMx_;
	float smoothMy_;
	float easeT = 0.1f;

	

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


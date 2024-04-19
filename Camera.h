#pragma once
#include <Novice.h>
#include "Vector3AndMatrix4x4.h"
#include "WindowInit.h"


class Camera
{
public :
	Camera(const Vector3& scale, const Vector3& rotate, const Vector3& translate);
	~Camera();

	void Init(const Vector3& scale,const Vector3& rotate,const Vector3& translate);
	void Update();
	void Draw();

	void SetScale(const Vector3& scale) { scale_ = scale; }
	void SetRotate(const Vector3& rotate) { rotate_ = rotate; }
	void SetTranslate(const Vector3& translate) { translate_ = translate; }

	void SetCameraMatrix(const Matrix4x4& cameraMatrix) { cameraMatrix_ = cameraMatrix; }
	void SetViewMatrix(const Matrix4x4& viewMatrix) { viewMatrix_ = viewMatrix; }
	void SetProjectionMatrix(const Matrix4x4& projectionMatrix) { projectionMatrix_ = projectionMatrix; }


	Vector3 GetScale() { return scale_; }
	Vector3 GetRotate() { return rotate_; }
	Vector3 GetTranslate() { return translate_; }

	Matrix4x4 GetCameraMatrix() { return cameraMatrix_; }
	Matrix4x4 GetViewMatrix() { return viewMatrix_; }
	Matrix4x4 GetProjectionMatrix() { return projectionMatrix_; }

	
private:
	Vector3 scale_;
	Vector3 rotate_;
	Vector3 translate_;

	Matrix4x4 cameraMatrix_=MakeAffineMatrix(scale_,rotate_,translate_);
	Matrix4x4 viewMatrix_=Inverse(cameraMatrix_);
	Matrix4x4 projectionMatrix_=MakePerspectiveFovMatrix(0.45f,float(kWindowWidth)/float(kWindowHeight),0.1f,100.0f);
	
	Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

};


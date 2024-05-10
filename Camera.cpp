#include "Camera.h"

Camera::Camera()
{
	Init();
}

void Camera::Init()
{
	cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate_, cameraPosition_);
	viewMatrix = Inverse(cameraMatrix);
	projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
	viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
	viewProjection = Multiply(viewMatrix, projectionMatrix);
	cameraPosition_ = { 0.0f,1.9f,-6.49f };
	cameraRotate_ = { 0.26f,0.0f,0.0f };
	isDebugMode_ = false;
	isRotateSpeed_ = kRotateSpeed;
	isMoveSpeed_ = 1.0f;
	cameraRay_ = TransformNomal({ 0,0,1 }, cameraMatrix);
	isFPSMode_ = true;

}

void Camera::Update()
{
	if (InputManager::GetIsTriggerKey(DIK_T))isDebugMode_ = !isDebugMode_;
	Move();

	cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate_, cameraPosition_);
	viewMatrix = Inverse(cameraMatrix);
	projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
	viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
	viewProjection = Multiply(viewMatrix, projectionMatrix);


	//Matrix4x4ScreenPrintf(0, 0, rayMatrix_, "rayMatrix");

	
}

void Camera::Move()
{
	if (!isDebugMode_)
	{
		return;
	}

	if (isFPSMode_)
	{
		if (InputManager::GetIsTriggerKey(DIK_P))
		{
			isFPSMode_ = false;
		}
		preMx_ = mx_;
		preMy_ = my_;
		Novice::GetMousePosition(&mx_, &my_);

		if (Novice::IsPressMouse(0))
		{
			cameraRotate_.y += (mx_ - preMx_) * mouceRotateSpeed;
			cameraRotate_.x += (my_ - preMy_) * mouceRotateSpeed;
		}
		if (Novice::IsPressMouse(1))
		{
			cameraRotate_.y += (mx_ - preMx_) * mouceRotateSpeed*2;
			cameraRotate_.x += (my_ - preMy_) * mouceRotateSpeed*2;
		}
		cameraMoveVector_ = { 0,0,0 };

		if (InputManager::GetIsPressKey(DIK_LSHIFT))
		{
			isMoveSpeed_ = kBoostMoveSpeed;
		}
		else
		{
			isMoveSpeed_ = 1.0f;
		}

		if (InputManager::GetIsPressKey(DIK_Q) ) {
			cameraMoveVector_.y+= isMoveSpeed_;
		}
		if (InputManager::GetIsPressKey(DIK_E) ) {
			cameraMoveVector_.y-= isMoveSpeed_;
		}
		//押してない時は奥と手前
		if (InputManager::GetIsPressKey(DIK_W)) {
			cameraMoveVector_.z+= isMoveSpeed_;
		}
		if (InputManager::GetIsPressKey(DIK_S)) {
			cameraMoveVector_.z-= isMoveSpeed_;
		}

		//左右
		if (InputManager::GetIsPressKey(DIK_D)) {
			cameraMoveVector_.x+= isMoveSpeed_;
		}
		if (InputManager::GetIsPressKey(DIK_A)) {
			cameraMoveVector_.x-= isMoveSpeed_;
		}


	}
	else
	{
		if (InputManager::GetIsTriggerKey(DIK_P))
		{
			isFPSMode_ = true;
		}
		//視点移動を早くする時はシフトを押す
		if (InputManager::GetIsPressKey(DIK_LSHIFT)) {
			isRotateSpeed_ = kRotateSpeed * 2;
		}
		else
		{
			isRotateSpeed_ = kRotateSpeed;
		}
		if (InputManager::GetIsPressKey(DIK_D)) {
			cameraRotate_.y += isRotateSpeed_;
		}
		if (InputManager::GetIsPressKey(DIK_A)) {
			cameraRotate_.y -= isRotateSpeed_;
		}
		if (InputManager::GetIsPressKey(DIK_W)) {
			cameraRotate_.x -= isRotateSpeed_;
		}
		if (InputManager::GetIsPressKey(DIK_S)) {
			cameraRotate_.x += isRotateSpeed_;
		}
		cameraMoveVector_ = { 0,0,0 };
		//シフト押しながらで上下移動
		if (InputManager::GetIsPressKey(DIK_UP) &&
			InputManager::GetIsPressKey(DIK_RSHIFT)) {
			cameraMoveVector_.y++;
		}
		//押してない時は奥と手前
		else if (InputManager::GetIsPressKey(DIK_UP)) {
			cameraMoveVector_.z++;
		}

		if (InputManager::GetIsPressKey(DIK_DOWN) &&
			InputManager::GetIsPressKey(DIK_RSHIFT)) {
			cameraMoveVector_.y--;
		}
		else if (InputManager::GetIsPressKey(DIK_DOWN)) {
			cameraMoveVector_.z--;
		}

		//左右
		if (InputManager::GetIsPressKey(DIK_RIGHT)) {
			cameraMoveVector_.x++;
		}
		if (InputManager::GetIsPressKey(DIK_LEFT)) {
			cameraMoveVector_.x--;
		}

	}
	

	cameraRay_ = TransformNomal(cameraMoveVector_, cameraMatrix);

	cameraPosition_ += cameraRay_ * kMoveSpeed;



}

void Camera::DebugDraw()
{

	Novice::ScreenPrintf(1000, 700, "CameraDebugMode -T-");
	if (!isDebugMode_)
	{
		return;
	}
	cameraRay_ = TransformNomal({0,0,1}, cameraMatrix);
	ImGui::Begin("Debug");
	ImGui::DragFloat3("cameraPosition", &cameraPosition_.x, 0.1f);
	ImGui::DragFloat3("cameraRotate", &cameraRotate_.x, 0.005f);
	ImGui::DragFloat3("cameraRay", &cameraRay_.x, 0.005f);
	ImGui::End();

	if (isFPSMode_)
	{
		Novice::ScreenPrintf(1000, 590, "FPS MODE");

		Novice::ScreenPrintf(1000, 620, "MOVE -WASD- -QE-");
		Novice::ScreenPrintf(1000, 640, "DASH -LSHIFT-");
		Novice::ScreenPrintf(1000, 660, "VIEW -LorR- -MOUCECLICK-");
		Novice::ScreenPrintf(1000, 680, "MODECHANGE -P-");

	}
	else
	{
		Novice::ScreenPrintf(1000, 590, "KEYBORD MODE");
		Novice::ScreenPrintf(1000, 620, "MOVE -ARROWKEY-");
		Novice::ScreenPrintf(1000, 640, "UP DOWN -RSHFT&ARROWKEY-");
		Novice::ScreenPrintf(1000, 660, "VIEW -WASD-");
		Novice::ScreenPrintf(1000, 680, "MODECHANGE -P-");

	}
}

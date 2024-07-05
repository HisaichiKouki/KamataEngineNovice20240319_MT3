#include <Novice.h>
#include <imgui.h>
#include <stdlib.h>
#include <memory>

#include "Vector3AndMatrix4x4.h"
#include "Glid.h"
#include "ObjectStruct.h"
#include "ProjectFunction.h"
#include "Collision.h"
#include "InputManager.h"
#include "Camera.h"
#include "CatmullRomSpline.h"
#include "SpringClas.h"


const char kWindowTitle[] = "LD2A_01_ヒサイチ_コウキ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	Camera* camera = new Camera;
	std::unique_ptr<SpringClas>spring_;
	spring_ = std::make_unique<SpringClas>();
	const Vector3 kGravity = { 0,-9.8f,0 };
	spring_->SetGravity(kGravity);
	bool start=false;

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();
		InputManager::Update();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///------------------///
		/// ↓更新処理ここから
		///------------------///

		
		camera->Update();
		if (InputManager::GetIsPressKey(DIK_SPACE))
		{
			start = true;
		}
		if (start)
		{
			spring_->Update();

		}



		///------------------///
		/// ↑更新処理ここまで
		///------------------///

		///------------------///
		/// ↓描画処理ここから
		///------------------///
		DrawGridLine(camera->GetviewProjection(), camera->GetViewportMatrix());
		//DrawAABB(aabb1, camera->GetviewProjection(), camera->GetViewportMatrix(), WHITE);
		

		spring_->Draw(camera->GetviewProjection(), camera->GetViewportMatrix());
		camera->DebugDraw();
		Novice::ScreenPrintf(100, 100, "Space start");

		spring_->Debug();

		//DrawAxis(spher.worldMatrix, viewProjection, viewportMatrix);
		///------------------///
		/// ↑描画処理ここまで
		///------------------///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	delete camera;
	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

#include <Novice.h>
#include "Vector3AndMatrix4x4.h"
#include "Glid.h"
#include "ObjectStruct.h"
#include "ProjectFunction.h"
#include <imgui.h>
#include "Collision.h"
#include "InputManager.h"
#include "Camera.h"
#include <stdlib.h>

#include "CatmullRomSpline.h"
#include "Bezier.h"

const char kWindowTitle[] = "LD2A_01_ヒサイチ_コウキ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	Camera* camera = new Camera;
	
	//CatmullRomSpline* spline = new CatmullRomSpline();
	Vector3 controlPoint[3]{
		{-0.8f,0.58f,1.0f},
		{1.76f,1.0f,-0.3f},
		{0.94f,-0.7f,2.3f}
	};

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




		///------------------///
		/// ↑更新処理ここまで
		///------------------///

		///------------------///
		/// ↓描画処理ここから
		///------------------///
		DrawGridLine(camera->GetviewProjection(), camera->GetViewportMatrix());
		//DrawAABB(aabb1, camera->GetviewProjection(), camera->GetViewportMatrix(), WHITE);
		//spline->Debug(camera->GetviewProjection(), camera->GetViewportMatrix(), BLACK);
		DrawBezier(controlPoint[0], controlPoint[1], controlPoint[2], camera->GetviewProjection(), camera->GetViewportMatrix(), BLUE);
		DebugBezier(controlPoint[0], controlPoint[1], controlPoint[2], camera->GetviewProjection(), camera->GetViewportMatrix(), BLACK);
		//spline->NoviceDraw(camera->GetviewProjection(), camera->GetViewportMatrix(),BLACK);
		camera->DebugDraw();
		
		ImGui::Begin("Bezier");
		for (int i = 0; i < 3; i++)
		{
			
			std::string label = "Point [" + std::to_string(i) + "]";
			ImGui::DragFloat3(label.c_str(), &controlPoint[i].x, 0.03f);
			//ImGui::DragFloat3("controlPoint", &controlPoints_[i].x, 0.03f);

		}
		ImGui::End();

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

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

	Vector3 translates[3]{
		{0.2f,1.0f,0.0f},
		{0.4f,0.0f,0.0f},
		{0.3f,0.0f,0.0f}
	};
	Vector3 rotates[3]{
		{0.0f,0.0f,-6.8f},
		{0.0f,0.0f,-1.4f},
		{0.0f,0.0f,0.0f},
	};
	Vector3 scales[3]{
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f},
	};

	Matrix4x4 worldMatrixes[3];
	Matrix4x4 calculationMat;


	worldMatrixes[0] = MakeAffineMatrix(scales[0], rotates[0], translates[0]);

	calculationMat = MakeAffineMatrix(scales[1], rotates[1], translates[1]);
	worldMatrixes[1] = Multiply(calculationMat, worldMatrixes[0]);

	calculationMat = MakeAffineMatrix(scales[2], rotates[2], translates[2]);
	worldMatrixes[2] = Multiply(calculationMat, worldMatrixes[1]);

	Sphere sphere[3];

	for (int i = 0; i < 3; i++)
	{
		sphere[i].center.x = worldMatrixes[i].m[3][0];
		sphere[i].center.y = worldMatrixes[i].m[3][1];
		sphere[i].center.z = worldMatrixes[i].m[3][2];
		sphere[i].radius = 0.1f;
	}
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

		worldMatrixes[0] = MakeAffineMatrix(scales[0], rotates[0], translates[0]);

		calculationMat = MakeAffineMatrix(scales[1], rotates[1], translates[1]);
		worldMatrixes[1] = Multiply(calculationMat, worldMatrixes[0]);

		calculationMat = MakeAffineMatrix(scales[2], rotates[2], translates[2]);
		worldMatrixes[2] = Multiply(calculationMat, worldMatrixes[1]);
		for (int i = 0; i < 3; i++)
		{
			sphere[i].center.x = worldMatrixes[i].m[3][0];
			sphere[i].center.y = worldMatrixes[i].m[3][1];
			sphere[i].center.z = worldMatrixes[i].m[3][2];
		}
		camera->Update();




		///------------------///
		/// ↑更新処理ここまで
		///------------------///

		///------------------///
		/// ↓描画処理ここから
		///------------------///
		DrawGridLine(camera->GetviewProjection(), camera->GetViewportMatrix());

		DrawGridSphere(sphere[0], 8,camera->GetviewProjection(), camera->GetViewportMatrix(), RED);
		DrawGridSphere(sphere[1], 8, camera->GetviewProjection(), camera->GetViewportMatrix(), GREEN);
		DrawGridSphere(sphere[2], 8, camera->GetviewProjection(), camera->GetViewportMatrix(), BLUE);
		DrawLine3D(sphere[0].center, sphere[1].center, camera->GetviewProjection(), camera->GetViewportMatrix(), WHITE);
		DrawLine3D(sphere[1].center, sphere[2].center, camera->GetviewProjection(), camera->GetViewportMatrix(), WHITE);
		camera->DebugDraw();

		ImGui::Begin("Debug");
		for (int i = 0; i < 3; i++)
		{
			std::string scale = "scale [" + std::to_string(i) + "]";
			ImGui::DragFloat3(scale.c_str(), &scales[i].x, 0.03f);
			std::string rotata = "rotate [" + std::to_string(i) + "]";
			ImGui::DragFloat3(rotata.c_str(), &rotates[i].x, 0.03f);
			std::string translate = "translate [" + std::to_string(i) + "]";
			ImGui::DragFloat3(translate.c_str(), &translates[i].x, 0.03f);
		}
		ImGui::End();
		//ImGui::Begin("Bezier");
		//for (int i = 0; i < 3; i++)
		//{
		//	
		//	std::string label = "Point [" + std::to_string(i) + "]";
		//	ImGui::DragFloat3(label.c_str(), &controlPoint[i].x, 0.03f);
		//	//ImGui::DragFloat3("controlPoint", &controlPoints_[i].x, 0.03f);

		//}
		//ImGui::End();

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

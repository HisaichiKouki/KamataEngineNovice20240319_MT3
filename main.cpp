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
Matrix4x4 operator* (const Matrix4x4& m1, const Matrix4x4& m2) { return Multiply(m1, m2); }

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	Camera* camera = new Camera;

	Vector3 a{ 0.2f,1.0f,0.0f };
	Vector3 b{ 2.4f,3.1f,1.2f };
	Vector3 c = a + b;
	Vector3 d = a - b;
	Vector3 e = a * 2.4f;
	Vector3 rotate{ 0.4f,1.43f,-0.8f };
	Matrix4x4 rotateXMat = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMat = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMat = MakeRotateZMatrix(rotate.z);
	//Matrix4x4 rotateMat = Add(rotateXMat,rotateYMat);
	Matrix4x4 rotateMat = rotateXMat * rotateYMat * rotateZMat;

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


		camera->DebugDraw();

		ImGui::Begin("Window");
		ImGui::Text("c:%f,%f,%f,", c.x, c.y, c.z);
		ImGui::Text("d:%f,%f,%f,", d.x, d.y, d.z);
		ImGui::Text("e:%f,%f,%f,", e.x, e.y, e.z);
		ImGui::Text("matrix:\n%f,%f,%f,%f\n%f,%f,%f,%f\n%f,%f,%f,%f\n%f,%f,%f,%f",
			rotateMat.m[0][0], rotateMat.m[0][1], rotateMat.m[0][2], rotateMat.m[0][3],
			rotateMat.m[1][0], rotateMat.m[1][1], rotateMat.m[1][2], rotateMat.m[1][3],
			rotateMat.m[2][0], rotateMat.m[2][1], rotateMat.m[2][2], rotateMat.m[2][3],
			rotateMat.m[3][0], rotateMat.m[3][1], rotateMat.m[3][2], rotateMat.m[3][3]);
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

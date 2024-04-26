#include <Novice.h>
#include "Vector3AndMatrix4x4.h"
#include "Glid.h"

#include <imgui.h>
const char kWindowTitle[] = "LD2A_01_ヒサイチ_コウキ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	Vector3 v1{ 1.2f,-3.9f,2.5f };
	Vector3 v2{ 2.8f,0.4f,-1.3f };
	Vector3 cross = Cross(v1, v2);

	Vector3 kLocalVertices[3] = {
		{0.0f,1.0f,0.0f},
		{1.0f,0.0f,0.0f},
		{-1.0f,-1.0f,0.0f}
	};
	Vector3 kTraiangleVector[2]{
	Subtract(kLocalVertices[0],kLocalVertices[1]),
	Subtract(kLocalVertices[1],kLocalVertices[2])
	};

	Vector3 rotate{};
	Vector3 translate{};
	float kAddRotation = 0.05f;
	float kAddMove = 0.2f;

	Vector3 cameraPosition = { 0.0f,0.0f,-15.0f };
	Vector3 cameraVector = { 0,0,1 };

	Vector3 cameraRotate{};
	float twoFaces{};


	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///------------------///
		/// ↓更新処理ここから
		///------------------///

		if (keys[DIK_A])
		{
			translate.x -= kAddMove;
		}
		if (keys[DIK_D])
		{
			translate.x += kAddMove;
		}
		if (keys[DIK_S])
		{
			translate.y -= kAddMove;
		}
		if (keys[DIK_W])
		{
			translate.y += kAddMove;
		}


		rotate.y += kAddRotation;

		if (keys[DIK_SPACE])
		{
			rotate.y = 0;
		}

		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraPosition);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 worldviewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
		Vector3 screenVertices[3];
		Vector3 worldVertices[3];
		for (uint32_t i = 0; i < 3; i++)
		{
			Vector3 ndcVertex = Transform(kLocalVertices[i], worldviewProjectionMatrix);
			worldVertices[i] = ndcVertex;
			screenVertices[i] = Transform(ndcVertex, viewportMatrix);
		}
		kTraiangleVector[0] = Subtract(worldVertices[0], worldVertices[1]);
		kTraiangleVector[1] = Subtract(worldVertices[1], worldVertices[2]);


		ImGui::DragFloat3("cameraPosition", &cameraPosition.x, 0.1f);
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.005f);

		///------------------///
		/// ↑更新処理ここまで
		///------------------///

		///------------------///
		/// ↓描画処理ここから
		///------------------///

		VectorScreenPrintf(0, 0, cross, "cross");

		twoFaces = Dot(cameraVector, Cross(kTraiangleVector[0], kTraiangleVector[1]));
		Novice::ScreenPrintf(0, 20, "twoFaces=%f", twoFaces);
		Novice::ScreenPrintf(0, 40, "rotate.y=%f", rotate.y);
		if (twoFaces <= 0)
		{
			Novice::DrawTriangle(
				int(screenVertices[0].x), int(screenVertices[0].y),
				int(screenVertices[1].x), int(screenVertices[1].y),
				int(screenVertices[2].x), int(screenVertices[2].y),
				RED, kFillModeSolid
			);
		}
		else
		{

			Novice::DrawTriangle(
				int(screenVertices[0].x), int(screenVertices[0].y),
				int(screenVertices[1].x), int(screenVertices[1].y),
				int(screenVertices[2].x), int(screenVertices[2].y),
				RED, kFillModeWireFrame
			);
		}

		DrawGridLine(Matrix4x4(Multiply(viewMatrix, projectionMatrix)), viewportMatrix);
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

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

#include <Novice.h>
#include "Vector3AndMatrix4x4.h"
#include "Glid.h"
#include "ObjectStruct.h"
#include "ProjectFunction.h"
#include <imgui.h>
const char kWindowTitle[] = "LD2A_01_ヒサイチ_コウキ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	Vector3 cameraPosition = { 0.0f,1.9f,-6.49f };

	Vector3 cameraRotate{ 0.26f,0.0f,0.0f };
	Vector3 cameraVector = { 0,0,1 };
	cameraVector *= cameraRotate;

	Segment segment{ {-2.0f,-1.0f,0.0f},{3.0f,2.0f,2.0f} };
	Vector3 point{ -1.5f,0.6f,0.6f };

	Vector3 project = Project(Subtract(point, segment.origin), segment.diff);
	Vector3 clossestPoint = ClosestPoint(point, segment);

	
	//float twoFaces{};

	



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

		/*if (keys[DIK_A])
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
		kTraiangleVector[1] = Subtract(worldVertices[1], worldVertices[2]);*/

		Sphere pointSpher{ point,0.31f };
		Sphere closestPointSphere{ clossestPoint,0.31f };

		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraPosition);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
		pointSpher.worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, pointSpher.rotate, pointSpher.centor);
		closestPointSphere.worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, closestPointSphere.rotate, closestPointSphere.centor);

		ImGui::Begin("Debug");
		ImGui::DragFloat3("cameraPosition", &cameraPosition.x, 0.1f);
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.005f);
		ImGui::End();


		///------------------///
		/// ↑更新処理ここまで
		///------------------///

		///------------------///
		/// ↓描画処理ここから
		///------------------///
		Matrix4x4 viewProjection = Multiply(viewMatrix, projectionMatrix);

		Vector3 start = Transform(Transform(segment.origin, viewProjection), viewportMatrix);
		Vector3 end = Transform(Transform(Add(segment.origin, segment.diff), viewProjection), viewportMatrix);

		

		Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), WHITE);

		DrawGridLine(viewProjection, viewportMatrix);
		DrawGridSphere(pointSpher, viewProjection, viewportMatrix, RED);
		DrawGridSphere(closestPointSphere, viewProjection, viewportMatrix, BLACK);



		if (ImGui::TreeNode("debug"))
		{
			ImGui::DragFloat3("Point", &point.x, 0.01f);
			ImGui::DragFloat3("Segment.origin", &segment.origin.x, 0.01f);
			ImGui::DragFloat3("Segment.diff", &segment.diff.x, 0.01f);
			ImGui::DragFloat3("Project", &project.x, 0.01f);
			ImGui::DragFloat3("ClosesPoint", &clossestPoint.x, 0.01f);
			//ImGui::DragFloat3("spherePos", &spher.centor.x, 0.1f);
			//ImGui::SliderFloat("sphereRadius", &spher.radius, 0.01f, 100.0f);
			//ImGui::DragFloat3("sphereRotate", &spher.rotate.x, 0.1f);
			ImGui::TreePop();
		}
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

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

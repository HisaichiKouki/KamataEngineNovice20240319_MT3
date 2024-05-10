#include <Novice.h>
#include "Vector3AndMatrix4x4.h"
#include "Glid.h"
#include "ObjectStruct.h"
#include "ProjectFunction.h"
#include <imgui.h>
#include "Collision.h"
#include "InputManager.h"
#include "Camera.h"
const char kWindowTitle[] = "LD2A_01_ヒサイチ_コウキ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	Camera* camera = new Camera;
	//Vector3 cameraPosition = { 0.0f,1.9f,-6.49f };

	//Vector3 cameraRotate{ 0.26f,0.0f,0.0f };
	//Vector3 cameraVector = { 0,0,1 };
	//cameraVector *= cameraRotate;

	Sphere s1{ {1,0,0},0.5f };
	Sphere s2{ {-1,0,0},0.5f };
	int s2Color = WHITE;

	float kAddMove = 0.02f;


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


		if (!camera->GetIsDebugMode())
		{
			if (keys[DIK_A])
			{
				s2.centor.x -= kAddMove;
			}
			if (keys[DIK_D])
			{
				s2.centor.x += kAddMove;
			}
			if (keys[DIK_LSHIFT])
			{
				if (keys[DIK_S])
				{
					s2.centor.y -= kAddMove;
				}
				if (keys[DIK_W])
				{
					s2.centor.y += kAddMove;
				}
			}
			else
			{
				if (keys[DIK_S])
				{
					s2.centor.z -= kAddMove;
				}
				if (keys[DIK_W])
				{
					s2.centor.z += kAddMove;
				}
				
			}
			
		}
		

		if (SpherCollision(s1, s2))
		{
			s2Color = RED;
		}
		else
		{
			s2Color = WHITE;
		}
		
		

		/*Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraPosition);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);*/

		camera->Update();

		s1.worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, s1.rotate, s1.centor);
		s2.worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, s2.rotate, s2.centor);

		/*ImGui::Begin("Debug");
		ImGui::DragFloat3("cameraPosition", &cameraPosition.x, 0.1f);
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.005f);
		ImGui::End();*/


		///------------------///
		/// ↑更新処理ここまで
		///------------------///

		///------------------///
		/// ↓描画処理ここから
		///------------------///

		
		DrawGridSphere(s1, camera->GetviewProjection(), camera->GetViewportMatrix(), WHITE);
		
		DrawGridSphere(s2, camera->GetviewProjection(), camera->GetViewportMatrix(), s2Color);

		DrawGridLine(camera->GetviewProjection(), camera->GetViewportMatrix());

		ImGui::Begin("Sphere");
		ImGui::DragFloat("sphere1Radius", &s1.radius, 0.01f);
		ImGui::DragFloat3("sphere1Position", &s1.centor.x, 0.01f);
		ImGui::DragFloat("sphere2Radius", &s2.radius, 0.01f);
		ImGui::DragFloat3("sphere2Position", &s2.centor.x, 0.01f);

		ImGui::End();
		
		camera->DebugDraw();
		//if (ImGui::TreeNode("debug"))
		//{
		//	/*ImGui::DragFloat3("Point", &point.x, 0.01f);
		//	ImGui::DragFloat3("Segment.origin", &segment.origin.x, 0.01f);
		//	ImGui::DragFloat3("Segment.diff", &segment.diff.x, 0.01f);
		//	ImGui::DragFloat3("Project", &project.x, 0.01f);
		//	ImGui::DragFloat3("ClosesPoint", &clossestPoint.x, 0.01f);*/
		//	//ImGui::DragFloat3("spherePos", &spher.centor.x, 0.1f);
		//	//ImGui::SliderFloat("sphereRadius", &spher.radius, 0.01f, 100.0f);
		//	//ImGui::DragFloat3("sphereRotate", &spher.rotate.x, 0.1f);
		//	ImGui::TreePop();
		//}
		
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

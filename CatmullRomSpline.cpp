#include "CatmullRomSpline.h"

CatmullRomSpline::CatmullRomSpline(const ViewProjection& viewprojection)
{
	Init();
	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewprojection);
}

CatmullRomSpline::CatmullRomSpline()
{

	Init();

}

void CatmullRomSpline::Init()
{
	controlPoints_ = {
		{-1,0,0},
		{1,1,0},
		{1,1.5f,0},
		{2,1.5f,0},
		{2,0,0}
	
	};
}

void CatmullRomSpline::Draw()
{

	for (size_t i = 0; i < segmentCount_; i++)
	{
		float t = 1.0f / segmentCount_ * i;
		Vector3 pos = CatmullRomPosition(controlPoints_, t);
		pointsDrawing_.push_back(pos);
	}

	for (size_t i = 0; i < segmentCount_ - 1; i++)
	{
		PrimitiveDrawer::GetInstance()->DrawLine3d(pointsDrawing_[i], pointsDrawing_[i + 1], { 1.0f,1.0f,1.0f,1.0f });
	}

}

void CatmullRomSpline::NoviceDraw(const Matrix4x4& viewProjectionMat, const Matrix4x4& viewportMat, uint32_t color)
{
	

	for (size_t i = 0; i < segmentCount_; i++)
	{
		float t = 1.0f / segmentCount_ * i;
		Vector3 pos = CatmullRomPosition(controlPoints_, t);
		pointsDrawing_.push_back(pos);
	
	}

	for (size_t i = 0; i < segmentCount_ - 1; i++)
	{
		Vector3 start = pointsDrawing_[i];
		Vector3 end = pointsDrawing_[i + 1];

		start = Transform(Transform(start, viewProjectionMat), viewportMat);
		end = Transform(Transform(end, viewProjectionMat), viewportMat);

		Novice::DrawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y, color);
	}
	pointsDrawing_.clear();
}

void CatmullRomSpline::Debug(const Matrix4x4& viewProjectionMat, const Matrix4x4& viewportMat, uint32_t color)
{
	Sphere sphere = {
		   .center{0.0f,0.0f,0.0f},
		   .radius{0.1f}
	};
	if (InputManager::GetIsTriggerKey(DIK_P)) {
		controlPoints_.push_back({ 0,0,0 });
	}
	if (InputManager::GetIsTriggerKey(DIK_O)) {
		controlPoints_.pop_back();
	}

	ImGui::Begin("Spline");
	ImGui::Text("-P- Add controlPoint");
	ImGui::Text("-O- Delete controlPoint");

	for (int i = 0; i < controlPoints_.size(); i++)
	{
		sphere.center = controlPoints_[i];
		DrawGridSphere(sphere, 3, viewProjectionMat, viewportMat, color);
		
		std::string label = "Point [" + std::to_string(i) + "]";
		ImGui::DragFloat3(label.c_str(), &controlPoints_[i].x, 0.03f); 
		//ImGui::DragFloat3("controlPoint", &controlPoints_[i].x, 0.03f);
		
	}
	
	ImGui::End();
	
}


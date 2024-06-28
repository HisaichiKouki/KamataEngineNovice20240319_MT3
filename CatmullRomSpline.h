#pragma once
#include "CatmullRom.h"
#include "PrimitiveDrawer.h"
#include <ViewProjection.h>
#include <imgui.h>
#include "Vector3AndMatrix4x4.h"
#include "Glid.h"
#include "InputManager.h"
class CatmullRomSpline
{
public:
	CatmullRomSpline(const ViewProjection& viewprojection);
	CatmullRomSpline();
	void Init();
	void Update();
	void Draw();
	void NoviceDraw(const Matrix4x4& viewProjectionMat, const Matrix4x4& viewportMat, uint32_t color);
	void Debug(const Matrix4x4& viewProjectionMat, const Matrix4x4& viewportMat, uint32_t color);
private:
	std::vector<Vector3> controlPoints_;
	std::vector<Vector3> pointsDrawing_;
	const size_t segmentCount_ = 100;
};


#include "Glid.h"

void DrawGridLine(const Matrix4x4& viewProjectionMat, const Matrix4x4& viewportMat)
{
	const float kGridHalfWidth = 1.0f;
	const uint32_t kSubdivision = 10;
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);

	for (uint32_t x = 0; x <= kSubdivision * 2; x++)
	{
		Matrix4x4 fromWorldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, { float(kGridEvery) * (x)-float(kGridEvery * kSubdivision),0.0f,kGridHalfWidth*2 });
		Matrix4x4 toWorldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, { float(kGridEvery) * (x)-float(kGridEvery * kSubdivision) ,0.0f,-kGridHalfWidth *2});

		Matrix4x4 fromWorldviewProjectionMatrix = Multiply(fromWorldMatrix, viewProjectionMat);
		Matrix4x4 toWorldviewProjectionMatrix = Multiply(toWorldMatrix, viewProjectionMat);

		Vector3 screenVertices[2];
		Vector3 fromNdcVertex = Transform({ 0.0f,0.0f,0.0f }, fromWorldviewProjectionMatrix);
		Vector3 toNdcVertex = Transform({ 0.0f,0.0f,0.0f }, toWorldviewProjectionMatrix);

		screenVertices[0] = Transform(fromNdcVertex, viewportMat);
		screenVertices[1] = Transform(toNdcVertex, viewportMat);

		Novice::DrawLine(int(screenVertices[0].x), int(screenVertices[0].y), int(screenVertices[1].x), int(screenVertices[1].y), 0xAAAAAAFF);

	}
	for (uint32_t x = 0; x <= kSubdivision * 2; x++)
	{
		Matrix4x4 fromWorldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, { -kGridHalfWidth*2 ,0.0f,float(kGridEvery) * (x)-float(kGridEvery * kSubdivision) });
		Matrix4x4 toWorldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, { kGridHalfWidth*2 ,0.0f,float(kGridEvery) * (x)-float(kGridEvery * kSubdivision) });

		Matrix4x4 fromWorldviewProjectionMatrix = Multiply(fromWorldMatrix, viewProjectionMat);
		Matrix4x4 toWorldviewProjectionMatrix = Multiply(toWorldMatrix, viewProjectionMat);

		Vector3 screenVertices[2];
		Vector3 fromNdcVertex = Transform({ 0.0f,0.0f,0.0f }, fromWorldviewProjectionMatrix);
		Vector3 toNdcVertex = Transform({ 0.0f,0.0f,0.0f }, toWorldviewProjectionMatrix);

		screenVertices[0] = Transform(fromNdcVertex, viewportMat);
		screenVertices[1] = Transform(toNdcVertex, viewportMat);

		Novice::DrawLine(int(screenVertices[0].x), int(screenVertices[0].y), int(screenVertices[1].x), int(screenVertices[1].y), 0x777777FF);

	}

	Matrix4x4 originMat = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f });
	Matrix4x4 originWorldviewProjectMat = Multiply(originMat, viewProjectionMat);

	Vector3 originNdcVertex = Transform({ 0.0f,0.0f,0.0f }, originWorldviewProjectMat);
	Vector3 originScreen = Transform(originNdcVertex, viewportMat);


	Novice::DrawEllipse(
		int(originScreen.x), int(originScreen.y),
		int(10), int(10), 0.0f, 0xffff00ff, kFillModeSolid);


}



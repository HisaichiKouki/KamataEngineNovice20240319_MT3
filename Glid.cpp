#include "Glid.h"
#include <cmath>
void DrawGridLine(const Matrix4x4& viewProjectionMat, const Matrix4x4& viewportMat)
{
	const float kGridHalfWidth = 1.0f;
	const uint32_t kSubdivision = 10;
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);

	for (uint32_t x = 0; x <= kSubdivision * 2; x++)
	{
		Matrix4x4 fromWorldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, { float(kGridEvery) * (x)-float(kGridEvery * kSubdivision),0.0f,kGridHalfWidth * 2 });
		Matrix4x4 toWorldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, { float(kGridEvery) * (x)-float(kGridEvery * kSubdivision) ,0.0f,-kGridHalfWidth * 2 });

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
		Matrix4x4 fromWorldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, { -kGridHalfWidth * 2 ,0.0f,float(kGridEvery) * (x)-float(kGridEvery * kSubdivision) });
		Matrix4x4 toWorldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, { kGridHalfWidth * 2 ,0.0f,float(kGridEvery) * (x)-float(kGridEvery * kSubdivision) });

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

void DrawGridSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	float pi = 3.1415926535f;//
	const uint32_t kSubdivision = 20;
	const float kLonEvery = (kSubdivision / 180.0f) * pi;//緯度
	const float kLatEvery = (kSubdivision / 180.0f) * pi;//軽度

	float thetaD = pi / kSubdivision;
	float faiD = 2.0f*pi / kSubdivision;

		for (uint32_t latIndex = 0; latIndex < kSubdivision; latIndex++)
		{
			float lat = -pi / 2.0f + kLatEvery * latIndex;

			for (uint32_t lonIndex = 0; lonIndex < kSubdivision; lonIndex++)
			{
				float lon = lonIndex * kLonEvery;

				Vector3 a, b, c;
				a.x = cosf(lon) * cosf(lat);
				a.y = sinf(lon);
				a.z = cosf(lon) * sinf(lat);

				b.x = cosf(lon + thetaD) * cosf(lat);
				b.y = sinf(lon + thetaD);
				b.z = cosf(lon + thetaD) * sinf(lat);

				c.x = cosf(lon) * cosf(lat + faiD);
				c.y = sinf(lon);
				c.z = cosf(lon) * sinf(lat + faiD);

				a = Multiply( sphere.radius,a);
				b = Multiply( sphere.radius,b);
				c = Multiply( sphere.radius,c);

				Matrix4x4 aWorldMat = MakeTranslateMatrix(a);
				Matrix4x4 bWorldMat = MakeTranslateMatrix(b);
				Matrix4x4 cWorldMat = MakeTranslateMatrix(c);

				Matrix4x4 aWvPMat = Multiply(aWorldMat, viewProjectionMatrix);
				Matrix4x4 bWvPMat = Multiply(bWorldMat, viewProjectionMatrix);
				Matrix4x4 cWvPMat = Multiply(cWorldMat, viewProjectionMatrix);
		
				Vector3 aNdcVec = Transform({ 0.0f,0.0f,0.0f }, aWvPMat);
				Vector3 bNdcVec = Transform({ 0.0f,0.0f,0.0f }, bWvPMat);
				Vector3 cNdcVec = Transform({ 0.0f,0.0f,0.0f }, cWvPMat);

				Vector3 aScreen= Transform(aNdcVec, viewportMatrix);
				Vector3 bScreen= Transform(bNdcVec, viewportMatrix);
				Vector3 cScreen= Transform(cNdcVec, viewportMatrix);

				Novice::DrawLine(
					int(aScreen.x), int(aScreen.y),
					int(bScreen.x), int(bScreen.y), color);
				Novice::DrawLine(
					int(aScreen.x), int(aScreen.y),
					int(cScreen.x), int(cScreen.y), RED);

			}

		}
}



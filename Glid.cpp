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
	const uint32_t kSubdivision = 12;
	float kLatD = pi / kSubdivision;
	float kLonD = (2.0f * pi) / kSubdivision;
	//const float kLatEvery = thetaD;//緯度
	//const float kLonEvery = faiD;//経度


	for (uint32_t latIndex = 0; latIndex < kSubdivision; latIndex++)
	{
		float lat = -pi / 2.0f + kLatD * latIndex;//緯度

		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; lonIndex++)
		{
			float lon = lonIndex * kLonD;//経度

			Vector3 a, b, c;
			a.x = cosf(lat) * cosf(lon);
			a.y = sinf(lat);
			a.z = cosf(lat) * sinf(lon);

			b.x = cosf(lat + kLatD) * cosf(lon);
			b.y = sinf(lat + kLatD);
			b.z = cosf(lat + kLatD) * sinf(lon);

			c.x = cosf(lat) * cosf(lon + kLonD);
			c.y = sinf(lat);
			c.z = cosf(lat) * sinf(lon + kLonD);

			a = Multiply(sphere.radius, a);
			b = Multiply(sphere.radius, b);
			c = Multiply(sphere.radius, c);


			Matrix4x4 worldviewProjectionMatrix = Multiply(sphere.worldMatrix, viewProjectionMatrix);
			Vector3 aNdcVec = Transform(a, worldviewProjectionMatrix);
			Vector3 bNdcVec = Transform(b, worldviewProjectionMatrix);
			Vector3 cNdcVec = Transform(c, worldviewProjectionMatrix);
			Vector3 aScreen = Transform(aNdcVec, viewportMatrix);
			Vector3 bScreen = Transform(bNdcVec, viewportMatrix);
			Vector3 cScreen = Transform(cNdcVec, viewportMatrix);
			/*Matrix4x4 aWorldMat = Tra;
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
			Vector3 cScreen= Transform(cNdcVec, viewportMatrix);*/

			Novice::DrawLine(
				int(aScreen.x), int(aScreen.y),
				int(bScreen.x), int(bScreen.y), color);
			Novice::DrawLine(
				int(aScreen.x), int(aScreen.y),
				int(cScreen.x), int(cScreen.y), color);

		}

	}
}

void DrawAxis(const Matrix4x4& worldMatrix, const Matrix4x4& viewProjection, const Matrix4x4& viewportMatrix)
{

	Matrix4x4 worldviewProjectionMatrix = Multiply(worldMatrix, viewProjection);

	Vector3 kLocalPos[4]{};
	kLocalPos[0] = { 0.0f,0.0f,0.0f };//centor
	kLocalPos[1] = { 2.0f,0.0f,0.0f };//x
	kLocalPos[2] = { 0.0f,2.0f,0.0f };//y
	kLocalPos[3] = { 0.0f,0.0f,2.0f };//z

	uint32_t color[3]{ };
	color[0] = RED;
	color[1] = GREEN;
	color[2] = BLUE;

	Vector3 fromNdcVec = Transform(kLocalPos[0], worldviewProjectionMatrix);
	Vector3 fromScreen = Transform(fromNdcVec, viewportMatrix);
	for (int i = 1; i <= 3; i++)
	{
		Vector3 ndcVec = Transform(kLocalPos[i], worldviewProjectionMatrix);
		Vector3 screen = Transform(ndcVec, viewportMatrix);

		Novice::DrawLine(
			int(fromScreen.x), int(fromScreen.y),
			int(screen.x), int(screen.y), color[i - 1]
		);
	}
}

void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	Vector3 center = Multiply(plane.distance, plane.normal);
	Vector3 perpendiculars[4];
	perpendiculars[0] = Normalize(Perpendicular(plane.normal));
	perpendiculars[1] = { perpendiculars[0] * -1 };
	perpendiculars[2] = Cross(plane.normal, perpendiculars[0]);
	perpendiculars[3] = perpendiculars[2] * -1;

	Vector3 points[4];
	for (int32_t index = 0; index < 4; index++)
	{
		Vector3 extend = Multiply(2.0f, perpendiculars[index]);
		Vector3 point = Add(center, extend);
		points[index] = Transform(Transform(point, viewProjectionMatrix), viewportMatrix);

	}
	Vector3 normalVector = Add(center, plane.normal);
	center = Transform(Transform(center, viewProjectionMatrix), viewportMatrix);
	normalVector = Transform(Transform(normalVector, viewProjectionMatrix), viewportMatrix);
	Novice::DrawLine(int(points[0].x), int(points[0].y), int(points[2].x), int(points[2].y), RED);
	Novice::DrawLine(int(points[1].x), int(points[1].y), int(points[3].x), int(points[3].y), BLUE);
	Novice::DrawLine(int(points[2].x), int(points[2].y), int(points[1].x), int(points[1].y), BLACK);
	Novice::DrawLine(int(points[3].x), int(points[3].y), int(points[0].x), int(points[0].y), color);

	//デバッグ用法線を表示してるつもり(多分上手くいってない)
	//Novice::DrawLine(int(center.x), int(center.y), int(normalVector.x), int(normalVector.y), RED);

	Novice::DrawEllipse(int(center.x), int(center.y), 5, 5, 0, RED, kFillModeSolid);

}

void DrawSegment(const Segment& segment, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	Segment screenSeg{};
	screenSeg.origin = Transform(Transform(segment.origin, viewProjectionMatrix), viewportMatrix);
	screenSeg.diff = Add(segment.diff,segment.origin );
	screenSeg.diff = Transform(Transform(screenSeg.diff, viewProjectionMatrix), viewportMatrix);

	Novice::DrawLine(int(screenSeg.origin.x), int(screenSeg.origin.y), int(screenSeg.diff.x), int(screenSeg.diff.y), color);
	Novice::DrawEllipse(int(screenSeg.origin.x), int(screenSeg.origin.y), 5, 5, 0, RED, kFillModeSolid);

}





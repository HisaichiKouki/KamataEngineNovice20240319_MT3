﻿#include "Glid.h"
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
	//sphere.worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, sphere.rotate, sphere.centor);

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

			a = Multiply(sphere.radius, a) + sphere.centor;
			b = Multiply(sphere.radius, b) + sphere.centor;
			c = Multiply(sphere.radius, c) + sphere.centor;


			//Matrix4x4 worldviewProjectionMatrix = Multiply(sphere.worldMatrix, viewProjectionMatrix);
			//Vector3 aNdcVec = Transform(Transform(a,viewProjectionMatrix),viewportMatrix);
			//Vector3 bNdcVec = Transform(Transform(a, viewProjectionMatrix), viewportMatrix);
			//Vector3 cNdcVec = Transform(Transform(a, viewProjectionMatrix), viewportMatrix);
			Vector3 aScreen = Transform(Transform(a, viewProjectionMatrix), viewportMatrix);
			Vector3 bScreen = Transform(Transform(b, viewProjectionMatrix), viewportMatrix);
			Vector3 cScreen = Transform(Transform(c, viewProjectionMatrix), viewportMatrix);
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
	screenSeg.diff = Add(segment.diff, segment.origin);
	screenSeg.diff = Transform(Transform(screenSeg.diff, viewProjectionMatrix), viewportMatrix);

	Novice::DrawLine(int(screenSeg.origin.x), int(screenSeg.origin.y), int(screenSeg.diff.x), int(screenSeg.diff.y), color);
	Novice::DrawEllipse(int(screenSeg.origin.x), int(screenSeg.origin.y), 5, 5, 0, RED, kFillModeSolid);

}

void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	Vector3 screenVertex[3];

	for (int i = 0; i < 3; i++)
	{
		screenVertex[i] = Transform(Transform(triangle.vertices[i], viewProjectionMatrix), viewportMatrix);
	}

	for (int i = 0; i < 3; i++)
	{
		if (i == 2)
		{
			Novice::DrawLine(int(screenVertex[i].x), int(screenVertex[i].y), int(screenVertex[0].x), int(screenVertex[0].y), color);
		}
		else
		{
			Novice::DrawLine(int(screenVertex[i].x), int(screenVertex[i].y), int(screenVertex[i + 1].x), int(screenVertex[i + 1].y), color);

		}
	}

	Vector3 p1p2 = Subtract(triangle.vertices[1], triangle.vertices[0]);
	Vector3 p2p3 = Subtract(triangle.vertices[2], triangle.vertices[1]);
	Plane plane;
	plane.normal = Cross(p1p2, p2p3);
	plane.normal = Normalize(plane.normal);
	plane.distance = Dot(plane.normal, triangle.vertices[0]);

	Vector3 triangleCenter = Add(Add(triangle.vertices[0], triangle.vertices[1]), triangle.vertices[2]);

	triangleCenter /= 3;

	//VectorScreenPrintf(0, 20, triangleCenter, "triangleCenter");

	triangleCenter = Transform(Transform(triangleCenter, viewProjectionMatrix), viewportMatrix);
	Novice::DrawEllipse(int(triangleCenter.x), int(triangleCenter.y), 5, 5, 0, RED, kFillModeSolid);

	//DrawPlane(plane, viewProjectionMatrix, viewportMatrix, color);
}

void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{

	Vector3 point[8];
	point[0] = aabb.min;//左下手前
	point[1] = { aabb.max.x ,aabb.min.y,aabb.min.z };//右下手前
	point[2] = { aabb.min.x,aabb.max.y,aabb.min.z };//左上手前
	point[3] = { aabb.max.x ,aabb.max.y ,aabb.min.z };//右上手前

	point[4] = { aabb.min.x,aabb.min.y,aabb.max.z };//左下奥
	point[5] = { aabb.max.x ,aabb.min.y,aabb.max.z };//右下奥
	point[6] = { aabb.min.x ,aabb.max.y ,aabb.max.z };//左上奥
	point[7] = aabb.max;//右上奥

	for (int i = 0; i < 8; i++)
	{
		point[i] = Transform(Transform(point[i], viewProjectionMatrix), viewportMatrix);
	}

	Novice::DrawLine((int)point[0].x, (int)point[0].y, (int)point[1].x, (int)point[1].y, color);
	Novice::DrawLine((int)point[0].x, (int)point[0].y, (int)point[2].x, (int)point[2].y, color);
	Novice::DrawLine((int)point[0].x, (int)point[0].y, (int)point[4].x, (int)point[4].y, color);

	Novice::DrawLine((int)point[7].x, (int)point[7].y, (int)point[3].x, (int)point[3].y, color);
	Novice::DrawLine((int)point[7].x, (int)point[7].y, (int)point[5].x, (int)point[5].y, color);
	Novice::DrawLine((int)point[7].x, (int)point[7].y, (int)point[6].x, (int)point[6].y, color);

	Novice::DrawLine((int)point[2].x, (int)point[2].y, (int)point[6].x, (int)point[6].y, color);
	Novice::DrawLine((int)point[1].x, (int)point[1].y, (int)point[5].x, (int)point[5].y, color);

	Novice::DrawLine((int)point[2].x, (int)point[2].y, (int)point[3].x, (int)point[3].y, color);
	Novice::DrawLine((int)point[4].x, (int)point[4].y, (int)point[5].x, (int)point[5].y, color);

	Novice::DrawLine((int)point[1].x, (int)point[1].y, (int)point[3].x, (int)point[3].y, color);
	Novice::DrawLine((int)point[4].x, (int)point[4].y, (int)point[6].x, (int)point[6].y, color);


	Novice::DrawEllipse(int(point[7].x), int(point[7].y), 5, 5, 0, RED, kFillModeSolid);
	Novice::DrawEllipse(int(point[0].x), int(point[0].y), 5, 5, 0, BLUE, kFillModeSolid);



}

void ReAABB(AABB& aabb)
{


	aabb.min.x = (std::min)(aabb.min.x, aabb.max.x);
	aabb.max.x = (std::max)(aabb.min.x, aabb.max.x);
	aabb.min.y = (std::min)(aabb.min.y, aabb.max.y);
	aabb.max.y = (std::max)(aabb.min.y, aabb.max.y);
	aabb.min.z = (std::min)(aabb.min.z, aabb.max.z);
	aabb.max.z = (std::max)(aabb.min.z, aabb.max.z);

}

void DrawOBB(const OBB& obb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{

	Matrix4x4 worldMatrix;
	worldMatrix.m[0][0] = obb.orientations[0].x;
	worldMatrix.m[0][1] = obb.orientations[0].y;
	worldMatrix.m[0][2] = obb.orientations[0].z;
	worldMatrix.m[0][3] = 0;

	worldMatrix.m[1][0] = obb.orientations[1].x;
	worldMatrix.m[1][1] = obb.orientations[1].y;
	worldMatrix.m[1][2] = obb.orientations[1].z;
	worldMatrix.m[1][3] = 0;

	worldMatrix.m[2][0] = obb.orientations[2].x;
	worldMatrix.m[2][1] = obb.orientations[2].y;
	worldMatrix.m[2][2] = obb.orientations[2].z;
	worldMatrix.m[2][3] = 0;

	worldMatrix.m[3][0] = obb.center.x;
	worldMatrix.m[3][1] = obb.center.y;
	worldMatrix.m[3][2] = obb.center.z;
	worldMatrix.m[3][3] = 1;

	Vector3 point[8]{};

	//手前
	point[0] = Transform({ -obb.size.x,-obb.size.y,-obb.size.z }, worldMatrix);//左下
	point[1] = Transform({ obb.size.x,-obb.size.y,-obb.size.z }, worldMatrix);//右下
	point[2] = Transform({ -obb.size.x,obb.size.y,-obb.size.z }, worldMatrix);//左上
	point[3] = Transform({ obb.size.x,obb.size.y,-obb.size.z }, worldMatrix);//右上

	//奥
	point[4] = Transform({ -obb.size.x,-obb.size.y,+obb.size.z }, worldMatrix);//左下
	point[5] = Transform({ obb.size.x,-obb.size.y,+obb.size.z }, worldMatrix);//右下
	point[6] = Transform({ -obb.size.x,obb.size.y,+obb.size.z }, worldMatrix);//左上
	point[7] = Transform({ obb.size.x,obb.size.y,+obb.size.z }, worldMatrix);//右上


	for (int i = 0; i < 8; i++)
	{
		point[i] = Transform(Transform(point[i], viewProjectionMatrix), viewportMatrix);
	}

	Novice::DrawLine((int)point[0].x, (int)point[0].y, (int)point[1].x, (int)point[1].y, color);
	Novice::DrawLine((int)point[0].x, (int)point[0].y, (int)point[2].x, (int)point[2].y, color);
	Novice::DrawLine((int)point[0].x, (int)point[0].y, (int)point[4].x, (int)point[4].y, color);

	Novice::DrawLine((int)point[7].x, (int)point[7].y, (int)point[3].x, (int)point[3].y, color);
	Novice::DrawLine((int)point[7].x, (int)point[7].y, (int)point[5].x, (int)point[5].y, color);
	Novice::DrawLine((int)point[7].x, (int)point[7].y, (int)point[6].x, (int)point[6].y, color);

	Novice::DrawLine((int)point[2].x, (int)point[2].y, (int)point[6].x, (int)point[6].y, color);
	Novice::DrawLine((int)point[1].x, (int)point[1].y, (int)point[5].x, (int)point[5].y, color);

	Novice::DrawLine((int)point[2].x, (int)point[2].y, (int)point[3].x, (int)point[3].y, color);
	Novice::DrawLine((int)point[4].x, (int)point[4].y, (int)point[5].x, (int)point[5].y, color);

	Novice::DrawLine((int)point[1].x, (int)point[1].y, (int)point[3].x, (int)point[3].y, color);
	Novice::DrawLine((int)point[4].x, (int)point[4].y, (int)point[6].x, (int)point[6].y, color);


}



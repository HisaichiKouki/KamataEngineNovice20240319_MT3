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
		int(10), int(10), 0.0f, 0x000000ff, kFillModeSolid);


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

			a = Multiply(sphere.radius, a) + sphere.center;
			b = Multiply(sphere.radius, b) + sphere.center;
			c = Multiply(sphere.radius, c) + sphere.center;


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

void OBBPointDraw(const OBB& obb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix)
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
	
	for (int i = 0; i < 8; i++)
	{		
		
		if (i<4)
		{
			Novice::DrawEllipse(int(point[i].x), int(point[i].y), 10, 10, 0, 0xffff00ff, kFillModeSolid);
		}
		else
		{
			Novice::DrawEllipse(int(point[i].x), int(point[i].y), 10, 10, 0, 0x00ffffff, kFillModeSolid);
		}
	}


}

void Obb2NormalPlaneDraw(const OBB& obb1, const OBB& obb2, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, int planeNum)
{
	//obb1
	Matrix4x4 worldMatrix[2];
	worldMatrix[0].m[0][0] = obb1.orientations[0].x;
	worldMatrix[0].m[0][1] = obb1.orientations[0].y;
	worldMatrix[0].m[0][2] = obb1.orientations[0].z;
	worldMatrix[0].m[0][3] = 0;

	worldMatrix[0].m[1][0] = obb1.orientations[1].x;
	worldMatrix[0].m[1][1] = obb1.orientations[1].y;
	worldMatrix[0].m[1][2] = obb1.orientations[1].z;
	worldMatrix[0].m[1][3] = 0;

	worldMatrix[0].m[2][0] = obb1.orientations[2].x;
	worldMatrix[0].m[2][1] = obb1.orientations[2].y;
	worldMatrix[0].m[2][2] = obb1.orientations[2].z;
	worldMatrix[0].m[2][3] = 0;

	worldMatrix[0].m[3][0] = obb1.center.x;
	worldMatrix[0].m[3][1] = obb1.center.y;
	worldMatrix[0].m[3][2] = obb1.center.z;
	worldMatrix[0].m[3][3] = 1;

	Vector3 point1[8]{};

	//ローカルからワールド座標に変換
	//手前
	point1[0] = Transform({ -obb1.size.x,-obb1.size.y,-obb1.size.z }, worldMatrix[0]);//左下
	point1[1] = Transform({ obb1.size.x,-obb1.size.y,-obb1.size.z }, worldMatrix[0]);//右下
	point1[2] = Transform({ -obb1.size.x,obb1.size.y,-obb1.size.z }, worldMatrix[0]);//左上
	point1[3] = Transform({ obb1.size.x,obb1.size.y,-obb1.size.z }, worldMatrix[0]);//右上

	//奥
	point1[4] = Transform({ -obb1.size.x,-obb1.size.y,+obb1.size.z }, worldMatrix[0]);//左下
	point1[5] = Transform({ obb1.size.x,-obb1.size.y,+obb1.size.z }, worldMatrix[0]);//右下
	point1[6] = Transform({ -obb1.size.x,obb1.size.y,+obb1.size.z }, worldMatrix[0]);//左上
	point1[7] = Transform({ obb1.size.x,obb1.size.y,+obb1.size.z }, worldMatrix[0]);//右上
	//ここまではきちんと、OBBの角に描画される事を確認
	
	//obb2
	worldMatrix[1].m[0][0] = obb2.orientations[0].x;
	worldMatrix[1].m[0][1] = obb2.orientations[0].y;
	worldMatrix[1].m[0][2] = obb2.orientations[0].z;
	worldMatrix[1].m[0][3] = 0;

	worldMatrix[1].m[1][0] = obb2.orientations[1].x;
	worldMatrix[1].m[1][1] = obb2.orientations[1].y;
	worldMatrix[1].m[1][2] = obb2.orientations[1].z;
	worldMatrix[1].m[1][3] = 0;

	worldMatrix[1].m[2][0] = obb2.orientations[2].x;
	worldMatrix[1].m[2][1] = obb2.orientations[2].y;
	worldMatrix[1].m[2][2] = obb2.orientations[2].z;
	worldMatrix[1].m[2][3] = 0;

	worldMatrix[1].m[3][0] = obb2.center.x;
	worldMatrix[1].m[3][1] = obb2.center.y;
	worldMatrix[1].m[3][2] = obb2.center.z;
	worldMatrix[1].m[3][3] = 1;

	Vector3 point2[8]{};

	//ローカルからワールド座標に変換
	//手前
	point2[0] = Transform({ -obb2.size.x,-obb2.size.y,-obb2.size.z }, worldMatrix[1]);//左下
	point2[1] = Transform({ obb2.size.x,-obb2.size.y,-obb2.size.z }, worldMatrix[1]);//右下
	point2[2] = Transform({ -obb2.size.x,obb2.size.y,-obb2.size.z }, worldMatrix[1]);//左上
	point2[3] = Transform({ obb2.size.x,obb2.size.y,-obb2.size.z }, worldMatrix[1]);//右上

	//奥
	point2[4] = Transform({ -obb2.size.x,-obb2.size.y,+obb2.size.z }, worldMatrix[1]);//左下
	point2[5] = Transform({ obb2.size.x,-obb2.size.y,+obb2.size.z }, worldMatrix[1]);//右下
	point2[6] = Transform({ -obb2.size.x,obb2.size.y,+obb2.size.z }, worldMatrix[1]);//左上
	point2[7] = Transform({ obb2.size.x,obb2.size.y,+obb2.size.z }, worldMatrix[1]);//右上
	//ここまではきちんと、OBBの角に描画される事を確認




	Vector3 nomalPlan[6];
	nomalPlan[0] = obb1.orientations[0];
	nomalPlan[1] = obb1.orientations[1];
	nomalPlan[2] = obb1.orientations[2];
	nomalPlan[3] = obb2.orientations[0];
	nomalPlan[4] = obb2.orientations[1];
	nomalPlan[5] = obb2.orientations[2];
	

	Vector3 projectionPoint1[8];
	Vector3 projectionPoint2[8];

	//面法線に射影してる
	for (int i = 0; i < 8; i++)
	{
		//Dot(各頂点,面法線の単位ベクトル)*面法線を単位ベクトルで射影ベクトルを出している
		//演算子オーバーロードの関係で順番が入れ替わってるけど、掛け算なので問題ないはず
		projectionPoint1[i] = Project(point1[i], nomalPlan[planeNum]);
		projectionPoint2[i] = Project(point2[i], nomalPlan[planeNum]);
	}
	//スクリーン座標に変換
	for (int i = 0; i < 8; i++)
	{
		projectionPoint1[i] = Transform(Transform(projectionPoint1[i], viewProjectionMatrix), viewportMatrix);
		point1[i] = Transform(Transform(point1[i], viewProjectionMatrix), viewportMatrix);
		projectionPoint2[i] = Transform(Transform(projectionPoint2[i], viewProjectionMatrix), viewportMatrix);
		point2[i] = Transform(Transform(point2[i], viewProjectionMatrix), viewportMatrix);
	}

	

	for (int i = 0; i < 4; i++)
	{
		Novice::DrawEllipse(int(projectionPoint1[i].x), int(projectionPoint1[i].y), 10, 10, 0, 0xff000033, kFillModeSolid);
		//Novice::DrawEllipse(int(projectionPoint2[i].x), int(projectionPoint2[i].y), 10, 10, 0, 0x0000ff33, kFillModeSolid);

		Novice::DrawLine(int(projectionPoint1[i].x), int(projectionPoint1[i].y), int(point1[i].x), int(point1[i].y), 0xff000033);
		//Novice::DrawLine(int(projectionPoint2[i].x), int(projectionPoint2[i].y), int(point2[i].x), int(point2[i].y), 0x0000ff33);
	}
	for (int i = 4; i < 8; i++)
	{
		Novice::DrawEllipse(int(projectionPoint1[i].x), int(projectionPoint1[i].y), 10, 10, 0, 0xffff0033, kFillModeSolid);
		//Novice::DrawEllipse(int(projectionPoint2[i].x), int(projectionPoint2[i].y), 10, 10, 0, 0xff00ff33, kFillModeSolid);

		Novice::DrawLine(int(projectionPoint1[i].x), int(projectionPoint1[i].y), int(point1[i].x), int(point1[i].y), 0xffff0033);
		//Novice::DrawLine(int(projectionPoint2[i].x), int(projectionPoint2[i].y), int(point2[i].x), int(point2[i].y), 0xff00ff33);
	}
}



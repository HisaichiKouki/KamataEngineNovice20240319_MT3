#include "Collision.h"

bool SpherCollision(const Sphere& s1, const Sphere& s2)
{
	float distance = Length(Subtract(s2.center, s1.center));
	if (distance <= s1.radius + s2.radius)
	{
		return true;
	}
	return false;
}

bool Speher2PlaneCollision(const Sphere& s1, const Plane& p1)
{
	float k = Dot(p1.normal, s1.center) - p1.distance;
	k = fabsf(k);

	if (k <= s1.radius)
	{
		return true;
	}
	return false;
}

bool Segment2PlaneCollision(const Segment& s1, const Plane& p1)
{
	float dot = Dot(p1.normal, s1.diff);
	//float length = Length(s1.origin, s1.diff);
	if (dot == 0) {
		return false;
	}

	float t = (p1.distance - Dot(s1.origin, p1.normal)) / dot;
	Novice::ScreenPrintf(0, 0, "t=%f", t);
	if (t >= 0 && t <= 1.0f)
	{
		return true;

	}
	return false;
}

bool Triangle2SegmentCollision(const Triangle& triangle, const Segment& segment)
{
	Vector3 p1p2 = Subtract(triangle.vertices[1], triangle.vertices[0]);
	Vector3 p2p3 = Subtract(triangle.vertices[2], triangle.vertices[1]);
	Vector3 p3p1 = Subtract(triangle.vertices[0], triangle.vertices[2]);
	Plane plane;
	plane.normal = Cross(p1p2, p2p3);
	plane.normal = Normalize(plane.normal);
	plane.distance = Dot(plane.normal, triangle.vertices[0]);

	if (Segment2PlaneCollision(segment, plane))
	{
		float dot = Dot(plane.normal, segment.diff);
		float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;

		Vector3 collisionPoint = segment.diff * t + segment.origin;

		Vector3 cross01 = Cross(p1p2, Subtract(collisionPoint, triangle.vertices[1]));
		Vector3 cross02 = Cross(p2p3, Subtract(collisionPoint, triangle.vertices[2]));
		Vector3 cross03 = Cross(p3p1, Subtract(collisionPoint, triangle.vertices[0]));

		if (Dot(cross01, plane.normal) >= 0 &&
			Dot(cross02, plane.normal) >= 0 &&
			Dot(cross03, plane.normal) >= 0) {
			return true;
		}

	}

	return false;
}

bool AABB2AABBCollision(const AABB& aabb1, const AABB& aabb2)
{
	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) &&
		(aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) &&
		(aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z))
	{
		return true;
	}
	return false;
}

bool AABB2SphereCollision(const AABB& aabb, const Sphere& sphere)
{
	Vector3 colossetPoint;
	colossetPoint.x = std::clamp(sphere.center.x, aabb.min.x, aabb.max.x);
	colossetPoint.y = std::clamp(sphere.center.y, aabb.min.y, aabb.max.y);
	colossetPoint.z = std::clamp(sphere.center.z, aabb.min.z, aabb.max.z);

	float distance = Length(colossetPoint - sphere.center);
	if (distance <= sphere.radius)
	{
		return true;
	}
	return false;
}

bool IntersectsAABB(const AABB& aabb, const Segment& seg, float& tmin, float& tmax)
{
	float tMinX = (aabb.min.x - seg.origin.x) / seg.diff.x;
	float tMaxX = (aabb.max.x - seg.origin.x) / seg.diff.x;
	float tMinY = (aabb.min.y - seg.origin.y) / seg.diff.y;
	float tMaxY = (aabb.max.y - seg.origin.y) / seg.diff.y;
	float tMinZ = (aabb.min.z - seg.origin.z) / seg.diff.z;
	float tMaxZ = (aabb.max.z - seg.origin.z) / seg.diff.z;

	Vector3 tNear = { (std::min)(tMinX,tMaxX),(std::min)(tMinY,tMaxY),(std::min)(tMinZ,tMaxZ) };
	Vector3 tFar = { (std::max)(tMinX,tMaxX),(std::max)(tMinY,tMaxY),(std::max)(tMinZ,tMaxZ) };

	tmin = (std::max)({ tNear.x, tNear.y, tNear.z });
	tmax = (std::min)({ tFar.x, tFar.y, tFar.z });
	//tmin = max(max(tNear.x, tNear.y), tNear.z);
	//tmax = min(min(tFar.x, tFar.y), tFar.z);

	Novice::ScreenPrintf(0, 0, "tmin=%f", tmin);
	Novice::ScreenPrintf(0, 20, "tmax=%f", tmax);

	return tmin <= tmax;

}

bool AABB2Segment(const AABB& aabb, const Segment& seg)
{
	float tmin, tmax;
	if (!IntersectsAABB(aabb, seg, tmin, tmax)) {
		return false;
	}
	return (tmin <= 1.0f && tmax >= 0.0f);
}

bool AABB2Ray(const AABB& aabb, const Ray& ray)
{
	float tmin, tmax;
	Segment segment{};
	segment.origin = ray.origin;
	segment.diff = ray.diff;
	if (!IntersectsAABB(aabb, segment, tmin, tmax))
		return false;

	return tmax >= 0.0f;

}

bool AABB2Line(const AABB& aabb, const Line& line)
{
	Segment segment{};
	segment.origin = line.origin;
	segment.diff = line.diff;
	float tmin, tmax;
	return IntersectsAABB(aabb, segment, tmin, tmax);
}

bool OBB2Sphere(const OBB& obb, const Sphere& sphere)
{

	Matrix4x4 oBBworldMatrix;
	oBBworldMatrix.m[0][0] = obb.orientations[0].x;
	oBBworldMatrix.m[0][1] = obb.orientations[0].y;
	oBBworldMatrix.m[0][2] = obb.orientations[0].z;
	oBBworldMatrix.m[0][3] = 0;

	oBBworldMatrix.m[1][0] = obb.orientations[1].x;
	oBBworldMatrix.m[1][1] = obb.orientations[1].y;
	oBBworldMatrix.m[1][2] = obb.orientations[1].z;
	oBBworldMatrix.m[1][3] = 0;

	oBBworldMatrix.m[2][0] = obb.orientations[2].x;
	oBBworldMatrix.m[2][1] = obb.orientations[2].y;
	oBBworldMatrix.m[2][2] = obb.orientations[2].z;
	oBBworldMatrix.m[2][3] = 0;

	oBBworldMatrix.m[3][0] = obb.center.x;
	oBBworldMatrix.m[3][1] = obb.center.y;
	oBBworldMatrix.m[3][2] = obb.center.z;
	oBBworldMatrix.m[3][3] = 1;

	Matrix4x4 obbWorldMatrixInverce = Inverse(oBBworldMatrix);

	Vector3 centerInObbLocalSpace = Transform(sphere.center, obbWorldMatrixInverce);

	AABB aabbObbLocal{};
	aabbObbLocal.min = obb.size * -1;
	aabbObbLocal.max = obb.size;

	Sphere obbLocalSphere{ centerInObbLocalSpace,sphere.radius };
	if (AABB2SphereCollision(aabbObbLocal, obbLocalSphere))
	{
		return true;
	}

	return false;
}

bool OBB2Segment(const OBB& obb, const Segment& segment)
{
	Matrix4x4 oBBworldMatrix;
	oBBworldMatrix.m[0][0] = obb.orientations[0].x;
	oBBworldMatrix.m[0][1] = obb.orientations[0].y;
	oBBworldMatrix.m[0][2] = obb.orientations[0].z;
	oBBworldMatrix.m[0][3] = 0;

	oBBworldMatrix.m[1][0] = obb.orientations[1].x;
	oBBworldMatrix.m[1][1] = obb.orientations[1].y;
	oBBworldMatrix.m[1][2] = obb.orientations[1].z;
	oBBworldMatrix.m[1][3] = 0;

	oBBworldMatrix.m[2][0] = obb.orientations[2].x;
	oBBworldMatrix.m[2][1] = obb.orientations[2].y;
	oBBworldMatrix.m[2][2] = obb.orientations[2].z;
	oBBworldMatrix.m[2][3] = 0;

	oBBworldMatrix.m[3][0] = obb.center.x;
	oBBworldMatrix.m[3][1] = obb.center.y;
	oBBworldMatrix.m[3][2] = obb.center.z;
	oBBworldMatrix.m[3][3] = 1;

	Matrix4x4 obbWorldMatrixInverce = Inverse(oBBworldMatrix);


	Vector3 localOrigin = Transform(segment.origin, obbWorldMatrixInverce);
	Vector3 localEnd = Transform(Add(segment.origin, segment.diff), obbWorldMatrixInverce);

	AABB aabbObbLocal{};
	aabbObbLocal.min = obb.size * -1;
	aabbObbLocal.max = obb.size;

	Segment localSeg;
	localSeg.origin = localOrigin;
	localSeg.diff = localEnd - localOrigin;
	return AABB2Segment(aabbObbLocal, localSeg);


}

bool Obb2Obb(const OBB& obb1, const OBB& obb2)
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

	float length1[8];
	float length2[8];


	//面法線の当たり判定
	//面法線に射影してる

	for (int j = 0; j < 6; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			//Dot(各頂点,面法線の単位ベクトル)*面法線を単位ベクトルで射影ベクトルを出している
			//演算子オーバーロードの関係で順番が入れ替わってるけど、掛け算なので問題ないはず
			projectionPoint1[i] = Project(point1[i], nomalPlan[j]);
			projectionPoint2[i] = Project(point2[i], nomalPlan[j]);


			/*if (i==0||i==3)
			{
				length1[i] = projectionPoint1[i].x;
			}
			if (i == 1 || i == 4)
			{
				length1[i] = projectionPoint1[i].y;
			}
			if (i == 2 || i == 5)
			{
				length1[i] = projectionPoint1[i].z;
			}*/
			/*length1[i] = Length(projectionPoint1[i]);
			length2[i] = Length(projectionPoint2[i]);*/

		}
		if (j == 0 || j == 3)
		{
			length1[j] = projectionPoint1[j].x;
			length2[j] = projectionPoint2[j].x;
		}
		if (j == 1 || j == 4)
		{
			length1[j] = projectionPoint1[j].y;
			length2[j] = projectionPoint1[j].y;
		}
		if (j == 2 || j == 5)
		{
			length1[j] = projectionPoint1[j].z;
			length2[j] = projectionPoint2[j].z;
		}


		float max1 = -1000000;
		float min1 =1000000;
		float max2 = -10000000;
		float min2 = 100000000;

		//法線に向かってでた点からminmaxを出す
		/*for (int i = 1; i < 8; i++)
		{
			if (max1 < length1[i]) { max1 = length1[i]; }
			if (min1 > length1[i]) { min1 = length1[i]; }

			if (max2 < length2[i]) { max2 = length2[i]; }
			if (min2 > length2[i]) { min2 = length2[i]; }
		}*/
		for (int i = 0; i < 8; i++)
		{
			if (j == 0 || j == 3)
			{
				if (max1 < projectionPoint1[i].x) { max1 = projectionPoint1[i].x; }
				if (min1 > projectionPoint1[i].x) { min1 = projectionPoint1[i].x; }

				if (max2 < projectionPoint2[i].x) { max2 = projectionPoint2[i].x; }
				if (min2 > projectionPoint2[i].x) { min2 = projectionPoint2[i].x; }
			}
			if (j == 1 || j == 4)
			{
				if (max1 < projectionPoint1[i].y) { max1 = projectionPoint1[i].y; }
				if (min1 > projectionPoint1[i].y) { min1 = projectionPoint1[i].y; }

				if (max2 < projectionPoint2[i].y) { max2 = projectionPoint2[i].y; }
				if (min2 > projectionPoint2[i].y) { min2 = projectionPoint2[i].y; }
			}
			if (j == 2 || j == 5)
			{
				if (max1 < projectionPoint1[i].z) { max1 = projectionPoint1[i].z; }
				if (min1 > projectionPoint1[i].z) { min1 = projectionPoint1[i].z; }

				if (max2 < projectionPoint2[i].z) { max2 = projectionPoint2[i].z; }
				if (min2 > projectionPoint2[i].z) { min2 = projectionPoint2[i].z; }
			}
		}
		

		float sumSpan = (max1 - min1) + (max2 - min2);
		float longSpnan = (std::max)(max1, max2) - (std::min)(min1, min2);

		/*Novice::ScreenPrintf(0, j * 20, "%d min1=%f max1=%f", j, min1, max1);
		Novice::ScreenPrintf(400, j * 20, "%d min2=%f max2=%f", j, min2, max2);

		Novice::ScreenPrintf(0, 300 + j * 40, "%d sum=%f", j, sumSpan);
		Novice::ScreenPrintf(0, 320 + j * 40, "%d lon=%f", j, longSpnan);*/
		if (sumSpan < longSpnan)
		{
			return false;
		}



	}

	//Vector3 crossVector[9];

	//crossVector[0] = Cross(nomalPlan[0], nomalPlan[3]);
	//crossVector[1] = Cross(nomalPlan[0], nomalPlan[4]);
	//crossVector[2] = Cross(nomalPlan[0], nomalPlan[5]);
	//crossVector[3] = Cross(nomalPlan[1], nomalPlan[3]);
	//crossVector[4] = Cross(nomalPlan[1], nomalPlan[4]);
	//crossVector[5] = Cross(nomalPlan[1], nomalPlan[5]);
	//crossVector[6] = Cross(nomalPlan[2], nomalPlan[3]);
	//crossVector[7] = Cross(nomalPlan[2], nomalPlan[4]);
	//crossVector[8] = Cross(nomalPlan[2], nomalPlan[5]);
	//for (int j = 0; j < 9; j++)
	//{
	//	Novice::ScreenPrintf(0, j * 20, "crossVec%d= x%0.4f y%0.4f z%0.4f", j, crossVector[j].x, crossVector[j].y, crossVector[j].z);
	//	for (int i = 0; i < 8; i++)
	//	{
	//		//Dot(各頂点,面法線の単位ベクトル)*面法線を単位ベクトルで射影ベクトルを出している
	//		//演算子オーバーロードの関係で順番が入れ替わってるけど、掛け算なので問題ないはず
	//		projectionPoint1[i] = Project(point1[i], crossVector[j]);
	//		projectionPoint2[i] = Project(point2[i], crossVector[j]);
	//		length1[i] = Length(projectionPoint1[i]);
	//		length2[i] = Length(projectionPoint2[i]);

	//	}


	//	float max1 = length1[0];
	//	float min1 = length1[0];
	//	float max2 = length2[0];
	//	float min2 = length2[0];

	//	//法線に向かってでた点からminmaxを出す
	//	for (int i = 1; i < 8; i++)
	//	{
	//		if (max1 < length1[i]) { max1 = length1[i]; }
	//		if (min1 > length1[i]) { min1 = length1[i]; }

	//		if (max2 < length2[i]) { max2 = length2[i]; }
	//		if (min2 > length2[i]) { min2 = length2[i]; }
	//	}

	//	float sumSpan = (max1 - min1) + (max2 - min2);
	//	float longSpnan = (std::max)(max1, max2) - (std::min)(min1, min2);

	//	/*Novice::ScreenPrintf(0, j * 20, "%d min1=%f max1=%f", j, min1, max1);
	//	Novice::ScreenPrintf(400, j * 20, "%d min2=%f max2=%f", j, min2, max2);

	//	Novice::ScreenPrintf(0, 300 + j * 40, "%d sum=%f", j,sumSpan);
	//	Novice::ScreenPrintf(0, 320 + j * 40, "%d lon=%f", j,longSpnan);*/
	//	if (sumSpan < longSpnan)
	//	{
	//		return false;
	//	}



	//}

	return true;
}

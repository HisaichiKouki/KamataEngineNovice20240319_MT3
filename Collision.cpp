#include "Collision.h"

bool SpherCollision(const Sphere& s1, const Sphere& s2)
{
	float distance = Length(Subtract(s2.centor, s1.centor));
	if (distance <= s1.radius + s2.radius)
	{
		return true;
	}
	return false;
}

bool Speher2PlaneCollision(const Sphere& s1, const Plane& p1)
{
	float k = Dot(p1.normal, s1.centor) - p1.distance;
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
	colossetPoint.x = std::clamp(sphere.centor.x, aabb.min.x, aabb.max.x);
	colossetPoint.y = std::clamp(sphere.centor.y, aabb.min.y, aabb.max.y);
	colossetPoint.z = std::clamp(sphere.centor.z, aabb.min.z, aabb.max.z);

	float distance = Length(colossetPoint - sphere.centor);
	if (distance <= sphere.radius)
	{
		return true;
	}
	return false;
}

bool AABB2Segment(const AABB& aabb, const Segment& seg)
{
	float tMinX = (aabb.min.x - seg.origin.x) / seg.diff.x;
	float tMaxX = (aabb.max.x - seg.origin.x) / seg.diff.x;
	float tMinY = (aabb.min.y - seg.origin.y) / seg.diff.y;
	float tMaxY = (aabb.max.y - seg.origin.y) / seg.diff.y;
	float tMinZ = (aabb.min.z - seg.origin.z) / seg.diff.z;
	float tMaxZ = (aabb.max.z - seg.origin.z) / seg.diff.z;

	Vector3 tNear = { (std::min)(tMinX,tMaxX),(std::min)(tMinY,tMaxY),(std::min)(tMinZ,tMaxZ) };
	Vector3 tFar = { (std::max)(tMinX,tMaxX),(std::max)(tMinY,tMaxY),(std::max)(tMinZ,tMaxZ) };

	float tmin = max(max(tNear.x, tNear.y), tNear.z);
	float tmax = min(min(tFar.x, tFar.y), tFar.z);

	Novice::ScreenPrintf(0, 0, "tmin=%f", tmin);
	Novice::ScreenPrintf(0, 20, "tmax=%f", tmax);

	/*if (tmin<=1.0f&&tmin>=0.0f)
	{
		return true;
	}*/
	
	if (tmin <= tmax) {
		if (tmin>=0&&tmin<=1.0f||tmax>=0.0f&&tmax<=1.0f)
		{
			return true;

		}
	}


	return false;
}

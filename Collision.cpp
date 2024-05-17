#include "Collision.h"

bool SpherCollision(const Sphere& s1, const Sphere& s2)
{
    float distance = Length(Subtract(s2.centor , s1.centor));
	if (distance<=s1.radius+s2.radius)
	{
		return true;
	}
    return false;
}

bool Speher2PlaneCollision(const Sphere& s1, const Plane& p1)
{
	float k = Dot(p1.normal, s1.centor) - p1.distance;
	k = fabsf(k);

	if (k<=s1.radius)
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
	if (t>=0&&t<= 1.0f)
	{
		return true;

	}
	return false;
}

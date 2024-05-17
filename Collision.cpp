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

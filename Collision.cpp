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

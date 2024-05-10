#include "ProjectFunction.h"

Vector3 Project(const Vector3& v1, const Vector3& v2)
{
   // float vectorsize = Dot(v1, v2)/Normalize(v2);
    float t = Dot(v1,v2)/(Length(v2) * Length(v2));
    return Vector3(v2*t);
}

Vector3 ClosestPoint(const Vector3& point, const Segment& segment)
{
    Vector3 oc = Project(Subtract(point, segment.origin), segment.diff);
    return Vector3(Add(segment.origin,oc));
}

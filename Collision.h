#pragma once
#include "ObjectStruct.h"

bool SpherCollision(const Sphere& s1, const Sphere& s2);

bool Speher2PlaneCollision(const Sphere& s1, const Plane& p1);

bool Segment2PlaneCollision(const Segment& s1, const Plane& p1);

bool Triangle2SegmentCollision(const Triangle& triangle, const Segment& segment);
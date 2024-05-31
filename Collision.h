#pragma once
#include "ObjectStruct.h"
#include <stdlib.h>
#include <algorithm>

bool SpherCollision(const Sphere& s1, const Sphere& s2);

bool Speher2PlaneCollision(const Sphere& s1, const Plane& p1);

bool Segment2PlaneCollision(const Segment& s1, const Plane& p1);

bool Triangle2SegmentCollision(const Triangle& triangle, const Segment& segment);

bool AABB2AABBCollision(const AABB& aabb1, const AABB& aabb2);

bool AABB2SphereCollision(const AABB& aabb, const Sphere& sphere);

bool AABB2Segment(const AABB& aabb, const Segment& seg);
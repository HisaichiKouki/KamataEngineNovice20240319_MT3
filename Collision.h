#pragma once
#include "ObjectStruct.h"
#include <stdlib.h>
#include <algorithm>
#include "ProjectFunction.h"

bool SpherCollision(const Sphere& s1, const Sphere& s2);

bool Speher2PlaneCollision(const Sphere& s1, const Plane& p1);

bool Segment2PlaneCollision(const Segment& s1, const Plane& p1);

bool Triangle2SegmentCollision(const Triangle& triangle, const Segment& segment);

bool AABB2AABBCollision(const AABB& aabb1, const AABB& aabb2);

bool AABB2SphereCollision(const AABB& aabb, const Sphere& sphere);

bool IntersectsAABB(const AABB& aabb, const Segment& seg,float&tmin,float& tmax);

bool AABB2Segment(const AABB& aabb, const Segment& seg);

bool AABB2Ray(const AABB& aabb, const Ray& ray);

bool AABB2Line(const AABB& aabb, const Line& line);

bool OBB2Sphere(const OBB& obb, const Sphere& sphere);

bool OBB2Segment(const OBB& obb, const Segment& segment);

bool Obb2Obb(const OBB& obb1, const OBB& obb2);
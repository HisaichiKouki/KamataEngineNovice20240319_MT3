#pragma once
#include <Vector3.h>
#include <vector>
#include <assert.h>
#include <cmath>

#include <algorithm>
Vector3 CatmullRomInterpolation(
	const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3, float t
);

Vector3 CatmullRomPosition(const std::vector<Vector3>& points, float t);



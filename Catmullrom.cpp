#include "CatmullRom.h"

Vector3 CatmullRomInterpolation(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3, float t)
{
	const float s = 0.5f;
	float t2 = t * t;
	float t3 = t2 * t;

	Vector3 e3 = p0 * -1.0f + p1 * 3.0f + p2 * -3.0f + p3;
	Vector3 e2 = p0 * 2.0f + p1 * -5.0f + p2 * 4.0f + p3 * -1.0f;
	Vector3 e1 = p0 * -1.0f + p2;
	Vector3 e0 = p1 * 2.0f;

	return  (e3 * t3 + e2 * t2 + e1 * t + e0) * s;
}

Vector3 CatmullRomPosition(const std::vector<Vector3>& points, float t)
{
	assert(points.size() >= 4 && "制御点は4点以上です");

	//区画数は制御点の-1
	size_t division = points.size() - 1;
	//1区間の長さ
	float areaWidth = 1.0f / division;
	//区間内の始点を0.0f,終点を1.0fとしたときの現在位置
	float t_2 = std::fmod(t, areaWidth) * (division);
	t_2 = std::clamp(t_2, 0.0f, 1.0f);

	size_t index = static_cast<size_t>(t / areaWidth);
	//区画番号が上限を超えないようにする
	index = std::clamp(index, static_cast <size_t>(0), static_cast<size_t>(points.size() - 2));
	size_t index0 = index - 1;
	size_t index1 = index;
	size_t index2 = index + 1;
	size_t index3 = index + 2;

	if (index == 0) {
		index0 = index1;
	}
	if (index3 >= points.size())
	{
		index3 = index2;
	}

	const Vector3& p0 = points[index0];
	const Vector3& p1 = points[index1];
	const Vector3& p2 = points[index2];
	const Vector3& p3 = points[index3];

	return CatmullRomInterpolation(p0, p1, p2, p3, t_2);
}

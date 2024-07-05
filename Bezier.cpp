#include "Bezier.h"

Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t)
{

	return Vector3(v1 * (1.0f - t) + v2 * t);
}

void DrawBezier(const Vector3& c0, const Vector3& c1, const Vector3& c2, const Matrix4x4& viewProjectionMat, const Matrix4x4& viewportMat, uint32_t color)
{
	const int kDivision = 16;
	Vector3 p0 = c0;
	Vector3 preP0 = p0;

	float t = 0;
	float endT = 0;
	for (int i = 0; i <= kDivision; i++)
	{
		if (i != 0)
		{
			t = float(i) / kDivision;

		}
		endT = float(i + 1) / kDivision;
		//float t = (float)i / kDivision;
		Vector3 p0p1 = Lerp(c0, c1, t);
		Vector3 p1p2 = Lerp(c1, c2, t);
		preP0 = p0;
		p0 = Lerp(p0p1, p1p2, t);




		Vector3 screenP0 = Transform(Transform(p0, viewProjectionMat), viewportMat);
		Vector3 screenpreP0 = Transform(Transform(preP0, viewProjectionMat), viewportMat);
		Novice::DrawLine(int(screenpreP0.x), int(screenpreP0.y), int(screenP0.x), int(screenP0.y), color);

	}

}

void DebugBezier(const Vector3& c0, const Vector3& c1, const Vector3& c2, const Matrix4x4& viewProjectionMat, const Matrix4x4& viewportMat, uint32_t color)
{
	Sphere screenControlPoint[3];
	screenControlPoint[0].center = c0;
	screenControlPoint[1].center = c1;
	screenControlPoint[2].center = c2;

	for (int i = 0; i < 3; i++)
	{
		screenControlPoint[i].radius = 0.05f;
		DrawGridSphere(screenControlPoint[i], 8, viewProjectionMat, viewportMat, color);
	}



}



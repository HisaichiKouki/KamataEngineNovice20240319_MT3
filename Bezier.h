#pragma once
#include <Novice.h>
#include "Vector3AndMatrix4x4.h"
#include "ObjectStruct.h"
#include "Glid.h"
Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t);
void DrawBezier(const Vector3& c0, const Vector3& c1, const Vector3& c2, const Matrix4x4& viewProjectionMat, const Matrix4x4& viewportMat, uint32_t color);
void DebugBezier(const Vector3& c0, const Vector3& c1, const Vector3& c2, const Matrix4x4& viewProjectionMat, const Matrix4x4& viewportMat, uint32_t color);
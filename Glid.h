#pragma once
#include "Vector3AndMatrix4x4.h"
#include <Novice.h>
#include "ObjectStruct.h"
void DrawGridLine(const Matrix4x4& viewProjectionMat, const Matrix4x4& viewportMat);

void DrawGridSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

void DrawAxis(const Matrix4x4& worldMatrix,const Matrix4x4& viewProjection, const Matrix4x4& viewportMatrix);
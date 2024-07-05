#pragma once
#include "Vector3AndMatrix4x4.h"
#include <Novice.h>
#include "ObjectStruct.h"
#include <stdlib.h>
#include "ProjectFunction.h"

void DrawGridLine(const Matrix4x4& viewProjectionMat, const Matrix4x4& viewportMat);

void DrawGridSphere(const Sphere& sphere,int segment, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

void DrawAxis(const Matrix4x4& worldMatrix,const Matrix4x4& viewProjection, const Matrix4x4& viewportMatrix);

void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

void DrawSegment(const Segment& segment, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

void ReAABB( AABB &aabb);

void DrawOBB(const OBB& obb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

void OBBPointDraw(const OBB& obb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

void Obb2NormalPlaneDraw(const OBB& obb1, const OBB& obb2, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix,int planeNum);

void DrawLine3D(const Vector3& p1, const Vector3& p2, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, int color);
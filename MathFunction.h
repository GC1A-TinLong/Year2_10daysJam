#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include <algorithm>
#include <assert.h>
#include <cmath>

struct Vector2Int {
	int x, y;
};

Vector2& operator+=(Vector2& v1, const Vector2& v2);
Vector2 operator+(const Vector2& v1, const Vector2& v2);
Vector2 operator-(const Vector2& v1, const Vector2& v2);
Vector2 operator*(float scalar, const Vector2& v);
Vector2 operator*(const Vector2& v, float scalar);

Vector2Int operator-(const Vector2Int& v1, const Vector2Int& v2);
float Length(const Vector2Int& v);
Vector2 Normalize(const Vector2Int& v);

float Dot(const Vector3& v1, const Vector3& v2);
float Length(const Vector3& v);
Vector3 Normalize(const Vector3& v);
Vector3 Cross(const Vector3& v1, const Vector3& v2);

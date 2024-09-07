#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include <algorithm>
#include <assert.h>
#include <cmath>
class Player;
class Spike;

struct Size {
	int width;
	int height;
};

struct Vector2Int {
	int x, y;
};

struct Object {
	Vector2 pos;
	Size size;
};

Vector2& operator+=(Vector2& v1, const Vector2& v2);
Vector2 operator+(const Vector2& v1, const Vector2& v2);
Vector2 operator-(const Vector2& v1, const Vector2& v2);
Vector2 operator*(float scalar, const Vector2& v);
Vector2 operator*(const Vector2& v, float scalar);

Vector2Int operator-(const Vector2Int& v1, const Vector2Int& v2);
float Length(const Vector2& v);
float Length(const Vector2Int& v);
Vector2 Normalize(const Vector2Int& v);

bool isCollideObject(Object& a, Object& b);
Vector2 ScreenShakeRandDistance();



#include "MathFunction.h"

Vector2& operator+=(Vector2& v1, const Vector2& v2) {
	v1.x += v2.x;
	v1.y += v2.y;
	return v1;
}

Vector2 operator+(const Vector2& v1, const Vector2& v2) {
	Vector2 result{};
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	return result;
}

Vector2 operator-(const Vector2& v1, const Vector2& v2) {
	Vector2 result{};
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	return result;
}

Vector2 operator*(float scalar, const Vector2& v) {
	Vector2 result{};
	result.x = scalar * v.x;
	result.y = scalar * v.y;
	return result;
}

Vector2 operator*(const Vector2& v, float scalar) {
	Vector2 result{};
	result.x = scalar * v.x;
	result.y = scalar * v.y;
	return result;
}

Vector2Int operator-(const Vector2Int& v1, const Vector2Int& v2) { return { v1.x - v2.x, v1.y - v2.y }; }

float Length(const Vector2Int& v) { return sqrtf(float(v.x * v.x + v.y * v.y)); }

Vector2 Normalize(const Vector2Int& v) {
	assert(Length(v));
	return {
		v.x / Length(v),
		v.y / Length(v),
	};
}

float Dot(const Vector3& v1, const Vector3& v2) { return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z); }

float Length(const Vector3& v) { return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z); }

Vector3 Normalize(const Vector3& v) {
	assert(Length(v));
	return { v.x / Length(v), v.y / Length(v), v.z / Length(v) };
}

Vector3 Cross(const Vector3& v1, const Vector3& v2) { return { (v1.y * v2.z) - (v1.z * v2.y), (v1.z * v2.x) - (v1.x * v2.z), (v1.x * v2.y) - (v1.y * v2.x) }; }

Vector3 Project(const Vector3& v1, const Vector3& v2) {
	Vector3 normalV2 = Normalize(v2);
	return {
		(v1.x * v2.x * normalV2.x) / Length(v2),
		(v1.y * v2.y * normalV2.y) / Length(v2),
		(v1.z * v2.z * normalV2.z) / Length(v2),
	};
}
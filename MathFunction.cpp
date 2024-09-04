#include "MathFunction.h"
#include "Player.h"
#include "Spike.h"
#include <random>

std::random_device seed; // random device
std::default_random_engine eng(seed());
std::uniform_real_distribution<float> randOutput(-20.f, 20.f);

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

float Length(const Vector2& v)
{
	return sqrtf(v.x * v.x + v.y * v.y);
}

float Length(const Vector2Int& v) { return sqrtf(float(v.x * v.x + v.y * v.y)); }

Vector2 Normalize(const Vector2Int& v) {
	assert(Length(v));
	return {
		v.x / Length(v),
		v.y / Length(v),
	};
}

bool isCollideObject(Object& a, Object& b)
{
	if ((a.pos.x <= b.pos.x + b.size.width && a.pos.x + a.size.width >= b.pos.x) &&
		(a.pos.y <= b.pos.y + b.size.height && a.pos.y + a.size.height >= b.pos.y)) {
		return true;
	}
	return false;
}

Vector2 ScreenShakeRandDistance()
{
	//Vector2 result{};
	Vector2 randDistance = { randOutput(eng),randOutput(eng) };
	return randDistance;
}

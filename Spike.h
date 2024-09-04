#pragma once
#include <iostream>
#include "MathFunction.h"

class Spike
{
private:
	bool isHit = false;
	static inline const uint8_t kSpeed = 5;
	static inline const uint16_t height = 64;
	static inline const uint32_t width = 800;

	Vector2Int pos_;

public:
	void Initialize(Vector2Int pos);
	void Update();
	void Draw();
};


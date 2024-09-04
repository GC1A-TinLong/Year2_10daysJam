#pragma once
#include <iostream>
#include "MathFunction.h"

class Spike
{
private:
	bool isHit = false;
	bool isStart = false;

	static inline const uint8_t kSpeed = 5;
	static inline const uint16_t width = 48;
	static inline const uint16_t height = 48;
	Size size = { width,height };

	Vector2Int pos_;

	uint32_t plainTexture_;
	uint32_t bloodTexture_;

public:
	void Initialize(const Vector2Int& pos);
	void Update();
	void Draw();

	// Getter
	Vector2Int GetPos() const { return pos_; }
	Size GetSize() const { return size; }
};


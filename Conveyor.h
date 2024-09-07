#pragma once
#include "MathFunction.h"

class Player;

class Conveyor
{
public:
	void Initialize(Vector2 pos, Size size);
	void Update();
	void Draw();

	// Getter
	Object GetObject();
	Vector2 GetPos() const { return pos_; }
	Size GetSize() const { return size_; }

private:
	Vector2 pos_;
	Size size_;

	uint32_t texture_;
};


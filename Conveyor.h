#pragma once
#include "MathFunction.h"

class Player;

class Conveyor
{
public:
	void Initialize(Vector2 pos, Size size);
	void Update();
	void Draw();

	//void OnCollisionPlayer(Player* player);

	// Getter
	Object GetObject();
	Vector2 GetPos() const { return pos_; }
	Size GetSize() const { return size_; }

private:
	enum class LRDirection {
		left,
		right,
	};
	LRDirection direction = LRDirection::left;

	Vector2 pos_;
	Size size_;

	uint32_t texture_;
};


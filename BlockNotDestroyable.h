#pragma once
#include "MathFunction.h"

class Player;

class BlockNotDestroyable
{
public:
	~BlockNotDestroyable();

	void Initialize(Vector2 pos, bool isMoss, bool isWall);
	void Update();
	void DestroyIfOOB(); // out of bounds
	void OnCollision(Player* player);
	void LoopWall();

	bool GetIsAboveScreen() const { return isAboveScreen_; };

	void Draw();

private:

	Vector2 pos_ = {};
	Vector2 scale = { 1.f,1.f };
	Size size = { 48,48 };

	uint32_t blockHandle_;

	bool isMoss_ = false;

	bool isWall_ = false;

	float wallMinY = 0;

	float wallMaxY = float(size.height)*22;

	bool isAboveScreen_ = false;
};


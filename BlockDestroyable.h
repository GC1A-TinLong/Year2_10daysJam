#pragma once
#include "MathFunction.h"

class Player;

class BlockDestroyable
{
public:

	~BlockDestroyable();
	void Initialize(Vector2 pos);
	void Update();
	void DestroyIfOOB(); // out of bounds
	void OnCollision(Player* player);
	bool GetIsAboveScreen() const { return isAboveScreen_; };
	Vector2 GetPos() { return pos_; };
	Size GetSize() { return size; };

	void Draw();


private:

	Vector2 pos_ = {};
	Vector2 scale = { 1.f,1.f };
	Size size = { 48,48 };

	uint32_t blockHandle_;

	bool isDestroyed = false;

	bool isTouched = false;

	bool isAboveScreen_ = false;
};


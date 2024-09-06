#pragma once
#include "MathFunction.h"
#include "Shake.h"

class Player;

class BlockNotDestroyable
{
public:

	~BlockNotDestroyable();
	void Initialize(Vector2 pos, bool isMoss, bool isWall);
	void Update();
	void DestroyIfOOB(); // out of bounds
	void HP();
	void OnCollision(Player* player);
	void LoopWall();
	Vector2 GetPos() const { return pos_; };
	Size GetSize() const { return size; };
	const Object GetObject_() const;
	bool GetIsAboveScreen() const { return isAboveScreen_; };
	void SetIsTouched(bool isTouched) { isTouched_ = isTouched; };
	int GetHp() { return hp; };

	void Draw();

private:

	Vector2 pos_ = {};
	Vector2 scale = { 1.f,1.f };
	Size size = { 48,48 };

	uint32_t blockHandle_;

	bool isTouched_ = false;

	bool isMoss_ = false;

	bool isWall_ = false;

	float wallMinY = 0;

	float wallMaxY = float(size.height) * 22;

	bool isAboveScreen_ = false;

	Shake* shake_ = nullptr;

	int hp = 100;

	int hpHalf = 50;
};


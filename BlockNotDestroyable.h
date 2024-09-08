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
	void Draw();

	void DestroyIfOOB(); // out of bounds
	void HP();
	void Shakeing();
	void OnCollision(Player* player);
	void LoopWall();

	// Setter
	void SetIsTouched(bool isTouched) { isTouched_ = isTouched; };
	void SetTakenDamage(int takenDamage) { takenDamage_ = takenDamage; };
	void SetStartShake(bool startShake) { startShake_ = startShake; };

	// Getter
	Vector2 GetPos() const { return pos_; };
	Size GetSize() const { return size; };
	const Object GetObject_() const;
	bool GetIsAboveScreen() const { return isAboveScreen_; };
	int GetHp() const { return hp; };
	bool IsDestroyed() const { return hp <= 0; }

private:

	Vector2 pos_ = {};
	Vector2 scale = { 1.f,1.f };
	Size size = { 48,48 };

	float wallMinY = 0;
	float wallMaxY = float(size.height) * 22;

	uint32_t blockHandle_;

	bool isAboveScreen_ = false;
	bool isTouched_ = false;

	bool isMoss_ = false;
	bool isWall_ = false;

	int hpMax = 150;
	int hp = hpMax;
	int hpHalf = 75;
	int takenDamage_ = 0;
	int hpLow = 90;
	bool startShake_ = false;

	Shake* shake_ = nullptr;
};


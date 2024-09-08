#pragma once
#include "MathFunction.h"
#include "Shake.h"

class Player;

class BlockExplodingTrap
{

public:

	~BlockExplodingTrap();
	void Initialize(Vector2 pos, bool isMoss);
	void Update();
	void DestroyIfOOB(); // out of bounds
	void HP();
	void Shakeing();
	void OnCollision(Player* player);
	void Draw();

	//Getter
	bool GetIsAboveScreen() const { return isAboveScreen_; };
	Vector2 GetPos() { return pos_; };
	Size GetSize() { return size; };
	const Object GetObject_() const;
	int GetHp() const { return hp; };
	bool IsDestroyed() const { return hp <= 0; }

	//Setter
	void SetIsTouched(bool isTouched) { isTouched_ = isTouched; };
	void SetTakenDamage(int takenDamage) { takenDamage_ = takenDamage; };
	void SetStartShake(bool startShake) { startShake_ = startShake; };

private:

	Vector2 pos_ = {};
	Vector2 scale = { 1.f,1.f };
	Size size = { 48,48 };

	uint32_t blockHandle_;

	bool isMoss_ = false;

	bool isDestroyed = false;

	bool isTouched_ = false;

	bool isAboveScreen_ = false;

	int hpMax = 150;
	int hp = hpMax;
	int takenDamage_ = 0;
	int hpLow = 90;
	bool startShake_ = false;

	Shake* shake_ = nullptr;

};


#pragma once
#include "MathFunction.h"
#include "Shake.h"

class Player;

class BlockDestroyable
{
public:
	~BlockDestroyable();
	void Initialize(Vector2 pos);
	void Update(float scrollSpeed);
	void DestroyIfOOB(); // out of bounds
	void HP();
	void Shakeing();
	void OnCollision(Player* player);

	void Respawn();

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

	void Draw();

private:

	Vector2 pos_ = {};
	Vector2 scale = { 1.f,1.f };
	Size size = { 48,48 };

	uint32_t blockHandle_;

	bool isDestroyed = false;

	bool isTouched_ = false;

	bool isAboveScreen_ = false;

	static inline const int kHpMax = 50;
	int hp = kHpMax;
	int takenDamage_ = 1;
	int hpLow = 990;
	bool startShake_ = false;

	Shake* shake_ = nullptr;

	uint8_t respawnTimer = 0;
};


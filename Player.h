#pragma once
#include "MathFunction.h"
#include "Input.h"

class Player
{
private:
	enum class LRDirection {
		left,
		right,
	};

	// Left & Right Direction
	LRDirection direction = LRDirection::right;
	// Size
	static inline const int height = 32;
	static inline const int width = 32;
	// HP
	static inline const uint8_t kMaxHp = 10;
	uint8_t hp = kMaxHp;
	// Collide with enemy
	uint16_t collideBuffer = 0;

	// Movement Flag
	bool isJump = false;
	// IsHit Flag
	bool isHit = false;
	bool isDead = false;

	// Player Status
	Vector2 pos_{};
	Vector2 velocity_{};
	// OnGround
	static inline const float kAcceleration = 0.5f;
	static inline const float kAttenuation = 0.1f;
	static inline const float kMaxVelocity = 10.f;

	// Sprite Handle
	uint32_t texture_;
	
public:
	void Initialize(const Vector2& pos, const uint32_t &texture);
	void Update();
	void Draw();

	void MovementInput();

	// Getter
	bool IsHit() const { return isHit; }
	bool IsDead() const { return isDead; }
};


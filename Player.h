#pragma once
#include "MathFunction.h"

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
	static inline const int height = 72;
	static inline const int width = 48;
	Size size = { width,height };
	// HP
	static inline const uint8_t kMaxHp = 10;
	uint8_t hp = kMaxHp;
	// Collide with enemy
	uint16_t collideBuffer = 0;

	// Movement Flag
	bool isPressingSpace = false;
	bool isReleasedSpace = false;
	bool isJump = false;
	bool isHitGround = true;
	// OnGround
	bool onGround = true;
	static inline const float kAcceleration = 0.8f;
	static inline const float kAttenuation = 0.1f;
	static inline const float kMaxVelocity = 12.5f;
	/// Airborne ///
	// Gravity
	//static inline const float kGravityAcceleration  = 2.f;
	static inline const float kFreeFallAcceleration = 1.8f;
	static inline const float kMaxFallSpeed = 14.f;
	// Jump Acceleration
	static inline const float kInitJumpAcceleration = 14.f;
	static inline const float kContinuousJumpAcceleration = 7.f;
	static inline const float kMaxJumpSpeed = -22.f;
	bool isMaxSpeed = false;
	static inline const float kMinInitHeight = 18.f;
	/////////////////////////////////////////////
	// IsHit Flag
	bool isHit = false;
	bool isDead = false;

	// Player Status
	Vector2 pos_{};
	Vector2 prevPos_{};
	Vector2 velocity_{};

	// Sprite Handle
	uint32_t texture_;
	
public:
	void Initialize(const Vector2& pos);
	void Update();
	void Draw();

	void MovementInput();

	void OnCollision();

	Vector2 CameraOffset();

	// Getter
	bool IsHit() const { return isHit; }
	bool IsDead() const { return isDead; }
	Vector2 GetPos() const { return pos_; }
	Size GetSize() const { return size; }
	const Object GetObject_() const;
};


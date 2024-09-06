#pragma once
#include "MathFunction.h"
#include "BlockNotDestroyable.h"

class Player
{
private:
	enum class LRDirection {
		left,
		right,
	};

	enum class PlayerAnimation 
	{
		Idle,
		Right,
		Left,
	};

	// Left & Right Direction
	LRDirection direction = LRDirection::right;
	// Size
	static inline const int height = 72;
	static inline const int width = 42;
	Size size = { width,height };
	// HP
	static inline const uint8_t kMaxHp = 10;
	uint8_t hp = kMaxHp;
	// Collide with enemy
	uint16_t collideBuffer = 0;

#pragma region Movement
	// Movement Flag
	bool isPressingSpace = false;
	bool isReleasedSpace = false;
	bool isFreeFalling = false;
	bool isJump = false;
	bool isHitGround = true;
	void InitializeFlag();
	// OnGround
	bool onGround = true;
	static inline const float kLRAcceleration = 0.8f;
	static inline const float kAttenuation = 0.1f;
	static inline const float kMaxVelocity = 12.5f;

	/// Airborne ///
	// Gravity
	static inline const float kFreeFallAcceleration = 1.8f;
	static inline const float kMaxFallSpeed = 14.f;
	// Jump Acceleration
	static inline const float kInitJumpAcceleration = 14.f;
	static inline const float kContinuousJumpAcceleration = 7.f;
	static inline const float kMaxJumpSpeed = -22.f;
	bool isMaxSpeed = false;
	static inline const float kMinInitHeight = 18.f;
	/////////////////////////////////////////////
#pragma endregion

	// Block Collision
	bool isOnTopOfBlock = true;
	static inline const float kCloseEnoughDistanceWithBlock = 5.f;
	bool isCloseEnoughToBlock = false;
	bool isWithinBlockWidth = false;

	// IsHit Flag
	bool isHit = false;
	bool isDead = false;

	// Player Status
	Vector2 pos_{};
	Vector2 prevPos_{};
	Vector2 velocity_{};

	// Sprite Handle
	uint32_t texture_;

	// Block
	BlockNotDestroyable* notDesBlock;


	#pragma region Animation

	int playerHandleHolder_;
	int playerIdleHandle_;
	int playerMovingRightHandle_;
	int playerMovingLeftHandle_;
	Vector2 animationPos_ = { 0.f, 0.f };
	int animationTimer_ = 0;
	float currentAnimationFrames = 504.f;
	PlayerAnimation playerAnimation_ = PlayerAnimation::Idle;
	PlayerAnimation previousPlayerAnimation_ = PlayerAnimation::Idle;

	#pragma endregion

	//Audio
	int jumpAudioHandle;
	int jumpPlayHandle = -1;
	static inline const float kJumpAudioVolume = 0.05f;
	
public:
	void Initialize(const Vector2& pos);
	void Update();
	void Draw();

	void AnimationHolder();
	void SwitchPlayerAnimationState();

	void MovementInput();

	void OnCollision();
	void CollisionWithBlock(BlockNotDestroyable* nonDesBlock);
	void SwitchToAirborne(BlockNotDestroyable* nonDesBlock);

	Vector2 CameraOffset();

	void Audio();

	// Getter
	bool IsHit() const { return isHit; }
	bool IsDead() const { return isDead; }
	Vector2 GetPos() const { return pos_; }
	Size GetSize() const { return size; }
	const Object GetObject_() const;
};


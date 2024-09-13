#pragma once
#include "MathFunction.h"
#include "BlockNotDestroyable.h"
#include "Conveyor.h"
#include "Shake.h"
#include <vector>
#include "BlockExplodingTrap.h"
#include "Conveyor.h"
#include "Goal.h"
#include "BlockDestroyable.h"
#include "BlockSteel.h"
#include "Goal.h"

class SpikeTrap;

class Player
{

public:
	~Player();

	void Initialize(const Vector2& pos);
	void Update(float scrollSpeed, bool isStageSelect, float goalY);
	void Draw();
	void Audio();

	void AnimationHolder();
	void SwitchPlayerAnimationState();
	void DeathAnimation();
	void Drilling();
	void DrillingSparks();
	void Scrolling(float scrollSpeed);
	void Exploded();
	void OnConveyor();

	void MovementInput();
	void OnCollision();
	void OnCollision(BlockExplodingTrap* explodingblock);
	void CollisionWithBlock(std::vector<BlockNotDestroyable*>& nonDesBlocks);
	void CollisionWithExplodingBlock(std::vector<BlockExplodingTrap*>& explodingBlocks);
	void CollisiontWithConveyor(std::vector<Conveyor*>& conveyor);
	void CollisionWithGoal(Goal* goal);
	void CollisionWithDestroyableBlock(std::vector<BlockDestroyable*>& desBlocks);
	void CollisionWithMetalBlock(std::vector<BlockSteel*>& steelBlocks);

	Vector2 CameraOffset();
	void Shakeing();
	void TakingDamage();
	void ClampPlayer(float goalY);

	// Getter
	bool IsHit() const { return isHit; }
	bool IsDead() const { return isDead; }
	bool IsOnGround() const { return onGround; }
	bool GetHP() const { return hp; };
	int GetUIHP()const { return hp; };

	Vector2 GetPos() const { return pos_; }
	Size GetSize() const { return size; }
	Object GetObject_() const;
	Object GetDrillPointObject_() const;
	bool GetIsDrilling() const { return isDrilling; };
	bool GetIsTakingDamage() const { return isTakingDamage_; };
	bool GetHasExploded() const { return isExploding_; };
	float GetDrillPower() const { return drillPower; };
	bool GetHasTouchedGoal() const { return hasTouchedGoal; };
	bool GetDeathAnimationDone()const { return deathAnimationDone; };

	// Setter
	void SetVelocity(Vector2 velocity) { velocity_ = velocity; };
	void SetHasExploded(bool isExploding) { isExploding_ = isExploding; };
	void SetIsDrilling(bool drilling) { isDrilling = drilling; };
	void SetIsDead(bool dead) { isDead = dead; };

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
	static inline const int width = 20;
	static inline const int spriteWidth = 44;
	static inline const int widthOffset = 11;
	Size size = { width,height };
	Vector2 drillPosOffset = { 11,65 };
	Size drillSize = { 20, size.height - 65 };
	// HP
	static inline const uint8_t kMaxHp = 4;
	uint8_t hp = kMaxHp;
	// Collide with enemy
	uint16_t collideBuffer = 0;

#pragma region Movement
	// Movement Flag
	bool isPressingSpace = false;
	bool isJump = false;
	bool touchedGoal = false;
	// OnGround
	bool onGround = false;
	float kLRAcceleration = 0.8f;
	static inline const float kAttenuation = 0.15f; // reduce speed (sliding)
	static inline const float kOrignialMaxVelocity = 8.5f; // reduce speed (sliding)
	static inline float kMaxVelocity = kOrignialMaxVelocity;


	/// Airborne ///
	// Gravity
	static inline const float kFreeFallAcceleration = 1.8f;
	static inline float maxFallSpeed = 14.f;
	// Jump Acceleration
	static inline const float kInitJumpAcceleration = 14.f;
	static inline const float kContinuousJumpAcceleration = 3.f;
	static inline const float kMaxJumpSpeed = -22.f;
	bool isMaxSpeed = false;
	static inline const float kMinInitHeight = 18.f;
	/////////////////////////////////////////////
#pragma endregion

	// Block Collision
	static inline const float kCloseEnoughDistanceWithBlock = 1.f;
	
	bool isOnConveyor = false;
	bool isRightConveyor = false;
	bool isLeftConveyor = false;


	// IsHit Flag
	bool isHit = false;
	bool isDead = false;

	// Player Status
	Vector2 pos_{};
	Vector2 prevPos_{};
	Vector2 velocity_{};

	// Sprite Handle
	uint32_t texture_;


	#pragma region Animation

	//Player
	int playerHandleHolder_;
	int playerIdleHandle_;
	int playerMovingRightHandle_;
	int playerMovingLeftHandle_;
	Vector2 animationPos_ = { 0.f, 0.f };
	int animationTimer_ = 0;
	float currentAnimationFrames = 126.f;
	PlayerAnimation playerAnimation_ = PlayerAnimation::Idle;
	PlayerAnimation previousPlayerAnimation_ = PlayerAnimation::Idle;

	//Sparks
	int sparkHandle_;
	Vector2 sparkAnimationPos_ = { 0.f, 0.f };
	int sparkAnimationTimer_ = 0;
	float sparkAnimationFrames = 168.f;
	float sparkSize = 42.f;


	//Death
	int deathHandle_;
	Vector2 deathAnimationPos_ = { 0.f, 0.f };
	int deathAnimationTimer_ = 0;
	float deathAnimationFrames = 168.f;
	Vector2 deathSize = { 42.f, 72.f };
	bool deathAnimationDone = false;
	#pragma endregion

	//Audio
	int jumpAudioHandle;
	int jumpPlayHandle = -1;
	static inline const float kJumpAudioVolume = 0.05f;

	int drillAudioHandle;
	int drillPlayHandle = -1;
	static inline const float kDrillAudioVolume = 0.05f;


	//Shake
	Shake* shake_ = nullptr;
	bool isShaking_ = false;
	
	bool isDrilling = false;

	//Has Exploded
	bool isExploding_ = false;
	int explodedTimer = 0;
	int randX = 0;
	float explosionVelocityX = 0;
	unsigned int seed;
	int amplitude = 9;

	//dont go Out Of Bounds
	float minXPos = 196.f;
	float maxXPos = 1347.f;

	//Drill 
	float maxDrillPower = 510.f;
	float drillPower = maxDrillPower;
	bool drillFatigue = false;

	//Drill Meter
	float drillEnergyReductionSpeed = 8.f;
	float drillEnergyRestorationSpeed = 4.f;

	//Taking damage
	bool isTakingDamage_ = false;
	static inline const int kMaxIFrames = 60;
	int iFrames = 0;
	static inline const uint8_t kMaxDrawCount = 30;
	uint8_t drawCount = 0;
	uint32_t halfAlphaWhite = 0xFF4040FF;
	uint32_t color = 0xFFFFFFFF;

	//Conveyor speed
	float conveyerSpeed = 3.f;

	//Goal
	bool hasTouchedGoal = false;
	Goal* goal_ = nullptr;
};


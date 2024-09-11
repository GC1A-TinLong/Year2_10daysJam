#pragma once
#include "IScene.h"
#include "Input.h"
#include "Novice.h"
#include "Player.h"
#include "Fade.h"
#include "Spike.h"
#include <vector>
#include "BlockDestroyable.h"
#include "BlockNotDestroyable.h"
#include "Backgroud.h"
#include "SpikeTrap.h"
#include "UserInterface.h"
#include "BlockExplodingTrap.h"
#include "Conveyor.h"
#include "DepthMeter.h"
#include "Explosion.h"
#include "Goal.h"

class StageScene :public IScene
{
public:
	~StageScene();

	void Initialize() override;
	void Update() override;
	void Draw() override;

	void ChangePhase();
	void DeleteBlocks();
	void CheckAllCollision();
	void SetPlayerStatus();
	void UserInterfaceDepthMeter();

private:
	// Scroll
	float scrollSpeed = 1.f;

	enum class Phase
	{
		kFadeIn,
		kPlay,
		kDeath,
		kStageClear,
		kFadeOut,
	};
	// Phase
	Phase phase_;

	// Fade
	Fade* fade_ = nullptr;
	float duration_ = 1.0f;

	//Background
	Background* background_ = nullptr;
	int backgroundHandle_[MAXBACKGROUNDS] =
	{
		{Novice::LoadTexture("./Resources/Background/OneBg.png")},
		{Novice::LoadTexture("./Resources/Background/TwoBg.png")},
	};

	// UI
	UserInterface* UI = nullptr;

	// Player
	Player* player_ = nullptr;

	// Spike
	static inline const uint8_t kSpikeNum = 25;
	std::vector<Spike*>spike_;

	// Block Size
	static inline const float kBlockSize = 48.f;
	// Destroyable Block

	static inline const uint8_t kDestroyableBlockNum = 4;
	std::vector<BlockDestroyable*>destroyableBlocks_;
	Vector2 desBlockPos_[kDestroyableBlockNum]
	{
		{144, 300}, {192, 300},{672, 300},
		{1056, 300}
	};

#pragma region Normal Block
	// Normal Block
	static inline const uint8_t kBlockNum = 39;

	std::vector<BlockNotDestroyable*>blocks_;

	Vector2 BlockPos_[kBlockNum]
	{
		{kBlockSize * 6,  300},  {kBlockSize * 7,  300},  {kBlockSize * 8,  300},
		{kBlockSize * 9,  350},  {kBlockSize * 10, 350},  {kBlockSize * 11, 350},

		{kBlockSize * 4,  500},  {kBlockSize * 5,  500},  {kBlockSize * 6,  500},
		{kBlockSize * 7,  500},  {kBlockSize * 8,  500},  {kBlockSize * 9,  500},
		{kBlockSize * 10, 500},  {kBlockSize * 11, 500},  {kBlockSize * 12, 500},
		{kBlockSize * 13, 500},  {kBlockSize * 14, 500},  {kBlockSize * 15, 500},
		{kBlockSize * 26, 500},  {kBlockSize * 27, 500},  {kBlockSize * 28, 500},

		{kBlockSize * 4,  548}, {kBlockSize * 4,  596}, {kBlockSize * 4,  644},

		{kBlockSize * 15, 700},  {kBlockSize * 16, 700},  {kBlockSize * 17, 700},
		{kBlockSize * 18, 700},  {kBlockSize * 19, 700},  {kBlockSize * 20, 700},

		{kBlockSize * 14, 900},  {kBlockSize * 15, 900},  {kBlockSize * 16, 900},
		{kBlockSize * 17, 900},  {kBlockSize * 18, 900},  {kBlockSize * 19, 900},

		{kBlockSize * 3, 1300},  {kBlockSize * 4, 1300},  {kBlockSize * 5, 1300},
	};

	bool isMoss[kBlockNum] =
	{
		0,1,0,1,1,0,0,0,1,0,
	};
#pragma endregion

	static inline const uint8_t kWallBlockNum = 22;
	std::vector<BlockNotDestroyable*>leftWallBlocks_;
	Vector2 leftWallPos_ = { 144.f,0 };
	std::vector<BlockNotDestroyable*>rightWallBlocks_;
	Vector2 rightWallPos_ = { 1392.f,0 };

	// Spike Trap
	static inline const uint8_t kSpikeTrapNum = 3;
	std::vector<SpikeTrap*>spikeTrap_;
	Vector2 spikeTrapPos_[kSpikeTrapNum] =
	{
		{kBlockSize * 16, 652}, {kBlockSize * 17, 652}, {kBlockSize * 18, 652}
	};

	//Exploding Block

	BlockExplodingTrap* blockExplodingTrap_ = nullptr;
	static inline const uint8_t kExplodingBlockNum = 6;
	std::vector< BlockExplodingTrap*> explodingBlocks_;
	Vector2 explodingBlockPos_[kExplodingBlockNum] =
	{
		{kBlockSize * 6,  948},  {kBlockSize * 7,  948}, {kBlockSize * 8,  948},
		{kBlockSize * 9,  948},  {kBlockSize * 10,  948}, {kBlockSize * 11,  948},
	};

	bool isExplodingBlockMoss[kExplodingBlockNum] =
	{
		{false}
	};

	//Conveyor
	static inline const uint8_t kConveyorNum = 1;
	std::vector<Conveyor*> conveyers_;
	Vector2 conveyerPos_[kConveyorNum] =
	{
		{500, 600},
	};

	bool isConveyorRight[kConveyorNum] =
	{
		0,
	};


	//Depth Meter
	DepthMeter* depthMeter_ = nullptr;

	//Explosion
	Explosion* explosion_ = nullptr;

	//Goal
	Goal* goal_ = nullptr;
	Vector2 goalPos_{ 192, 5000 };
};


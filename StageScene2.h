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
#include "BlockSteel.h"

class StageScene2 :public IScene
{
public:

	~StageScene2();
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
	float scrollSpeed = 2.f;

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
		{Novice::LoadTexture("./Resources/Background/OneBg.png")},
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

	static inline const uint8_t kDestroyableBlockNum = 13;
	std::vector<BlockDestroyable*>destroyableBlocks_;
	Vector2 desBlockPos_[kDestroyableBlockNum]
	{
		{kBlockSize * 12, 548}, {kBlockSize * 13, 548}, {kBlockSize * 14, 548},
		{kBlockSize * 18, 548}, {kBlockSize * 19, 548}, {kBlockSize * 20, 548},
		{kBlockSize * 21, 548}, {kBlockSize * 5, 1508}, {kBlockSize * 27, 1508},
		{kBlockSize * 28, 1508},

	};

#pragma region Normal Block
	// Normal Block
	static inline const uint8_t kBlockNum = 27;
	std::vector<BlockNotDestroyable*>blocks_;

	Vector2 BlockPos_[kBlockNum]
	{
		{kBlockSize * 5,  548}, {kBlockSize * 4,  548},
		{kBlockSize * 6,  548}, {kBlockSize * 7,  548}, {kBlockSize * 8,  548},  
		{kBlockSize * 9,  548}, {kBlockSize * 10, 548}, {kBlockSize * 11, 548},  
		{kBlockSize * 15, 548}, {kBlockSize * 16, 548}, {kBlockSize * 17, 548},
		
		{kBlockSize * 21, 548}, {kBlockSize * 22, 548}, {kBlockSize * 23, 548},
		{kBlockSize * 24, 548}, {kBlockSize * 25, 548}, {kBlockSize * 26, 548},
		{kBlockSize * 27, 548}, {kBlockSize * 28, 548},
	};

	bool isMoss[kBlockNum] =
	{
		0,1,0,1,1,0,0,0,1,0,1,1,1,0,0,1,0,1,1,1,0,0,0,
	};
#pragma endregion

	static inline const uint8_t kWallBlockNum = 22;
	std::vector<BlockNotDestroyable*>leftWallBlocks_;
	Vector2 leftWallPos_ = { 144.f,0.f };
	std::vector<BlockNotDestroyable*>rightWallBlocks_;
	Vector2 rightWallPos_ = { 1392.f,0.f };

	// Spike Trap
	static inline const uint8_t kSpikeTrapNum = 15;
	std::vector<SpikeTrap*>spikeTrap_;
	Vector2 spikeTrapPos_[kSpikeTrapNum] =
	{
		{kBlockSize * 12, 596}, {kBlockSize * 13, 596}, {kBlockSize * 14, 596},
		{kBlockSize * 18, 596}, {kBlockSize * 19, 596},

		{kBlockSize * 13, 1268},  {kBlockSize * 14, 1268},  {kBlockSize * 15, 1268},
		{kBlockSize * 13, 1604},  {kBlockSize * 14, 1604},  {kBlockSize * 15, 1604},
		{kBlockSize * 16, 1604},  {kBlockSize * 17, 1604},  {kBlockSize * 18, 1604},
		{kBlockSize * 19, 1604},
	};

	//Exploding Block


	//static inline const uint8_t kExplodingBlockNum = 6;
	//std::vector<BlockExplodingTrap*>explodingBlocks_;
	//Vector2 explodingBlockPos_[kExplodingBlockNum] =
	//{
	//	{kBlockSize * 6,  948},  {kBlockSize * 7,  948}, {kBlockSize * 8,  948},
	//	{kBlockSize * 9,  948},  {kBlockSize * 10,  948}, {kBlockSize * 11,  948},
	//};

	//bool isExplodingBlockMoss[kExplodingBlockNum] =
	//{
	//	{false}
	//};

	//Conveyor
	static inline const uint8_t kConveyorNum = 1;
	std::vector<Conveyor*> conveyers_;
	Vector2 conveyerPos_[kConveyorNum] =
	{
		{500, 600},
	};

	bool isConveyorRight[kConveyorNum] =
	{
		1,
	};


	//Depth Meter
	DepthMeter* depthMeter_ = nullptr;

	//Explosion
	Explosion* explosion_ = nullptr;

	//Goal
	Goal* goal_ = nullptr;
	Vector2 goalPos_{ 192, 1900 };
	bool isStageCleared = false;
	int waitForCollision = 0;


#pragma region Steel Block

	static inline const uint8_t kSteelBlockNum = 20;
	std::vector<BlockSteel*>blocksSteel_;
	Vector2 steelBlockPos_[kSteelBlockNum] =
	{
		
		{kBlockSize * 12,  644}, {kBlockSize * 13,  644},
		{kBlockSize * 14,  644}, {kBlockSize * 18,  644},
		{kBlockSize * 19,  644}, 
		

		
		{kBlockSize * 25, 644}, 
		{kBlockSize * 25, 692}, 
		{kBlockSize * 25, 740}, 
	};

#pragma endregion
};


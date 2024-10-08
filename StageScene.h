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

class StageScene : public IScene
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
	float scrollSpeed = 2.f;
	int clearTimer = 0;

	enum BlockType
	{
		None,
		Block,
		BrokenBlock,
		SteelBlock,
		ExplosionBlock,
		TrapSpike,
	};

	enum class Phase
	{
		kFadeIn,
		kCountdown,
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
	static inline const uint8_t kDestroyableBlockNum = 24;
	std::vector<BlockDestroyable*>destroyableBlocks_;


#pragma region Normal Block
	// Normal Block
	static inline const uint8_t kBlockNum = 107;
	std::vector<BlockNotDestroyable*>blocks_;

	//Mapchip
	int adjustPosForMapchipX = 192;
	int adjustPosForMapchipY = 480;
	int mapCountX = 25;
	int mapCountY = 23;
	int spriteSize = 48;
	int blockIndex = 0;
	int brokenBlockIndex = 0;
	int spikeIndex = 0;
	int steelIndex = 0;

	// 0 = nothing, 1 = block, 2 = broken block, 3 = steel block, 4 = exploding block, 5 = spike

	int map[23][25] =
	{
		
		2,2,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,
		2,2,1,1,1,1,1,1,1,1,1,1,5,5,5,0,0,0,0,0,0,0,0,0,0,
		2,2,1,1,1,1,1,1,1,1,1,1,3,3,3,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		3,3,3,3,3,3,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		1,2,2,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,2,2,
		1,2,2,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,2,2,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

	};

	bool isMoss[kBlockNum] =
	{
		0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 
		1, 0, 0, 1, 1, 1, 0, 0, 1, 0,
		1, 0, 0, 1, 0, 1, 1, 1, 1, 1,
		1, 1, 0, 1, 1, 0, 1, 0, 1, 1,
		0, 0, 0, 0, 0, 0, 1, 0, 0, 1,
		0, 1, 1, 1, 1, 0, 1, 1, 1, 0,
		1, 0, 1, 0, 0, 1, 0, 0, 0, 1,
		1, 1, 1, 0, 1, 1, 1, 1, 1, 0,
		1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
		0, 0, 0, 1, 0, 0, 0, 0, 1, 1,
		0, 0, 0, 0, 1, 0, 0,
	};
#pragma endregion

	static inline const uint8_t kWallBlockNum = 22;
	std::vector<BlockNotDestroyable*>leftWallBlocks_;
	Vector2 leftWallPos_ = { 144.f,0.f };
	std::vector<BlockNotDestroyable*>rightWallBlocks_;
	Vector2 rightWallPos_ = { 1392.f,0.f };

	// Spike Trap
	static inline const uint8_t kSpikeTrapNum = 6;
	std::vector<SpikeTrap*>spikeTrap_;
	
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
	Vector2 goalPos_{ 192, 1800 };
	bool isStageCleared = false;
	int waitForCollision = 0;


#pragma region Steel Block

	static inline const uint8_t kSteelBlockNum = 12;
	std::vector<BlockSteel*>blocksSteel_;
	

#pragma endregion

};



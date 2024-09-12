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
		{kBlockSize * 4,  500}, {kBlockSize * 4,  548},{kBlockSize * 4,  596},
		{kBlockSize * 5,  500}, {kBlockSize * 5,  548},{kBlockSize * 5,  596},

		{kBlockSize * 16, 1172},  {kBlockSize * 17, 1172},  {kBlockSize * 18, 1172},

		{kBlockSize * 4, 1508}, {kBlockSize * 5, 1508}, {kBlockSize * 27, 1508},
		{kBlockSize * 28, 1508},
		
	};

#pragma region Normal Block
	// Normal Block
	static inline const uint8_t kBlockNum = 128;
	std::vector<BlockNotDestroyable*>blocks_;

	Vector2 BlockPos_[kBlockNum]
	{

		{kBlockSize * 6,  500}, 
		{kBlockSize * 7,  500},  {kBlockSize * 8,  500},  {kBlockSize * 9,  500},
		{kBlockSize * 10, 500},  {kBlockSize * 11, 500},  {kBlockSize * 12, 500},
		{kBlockSize * 13, 500},  {kBlockSize * 14, 500},  {kBlockSize * 15, 500},

		{kBlockSize * 26, 500},  {kBlockSize * 27, 500},  {kBlockSize * 28, 500},

		{kBlockSize * 6, 548},  {kBlockSize * 7, 548},
		{kBlockSize * 8, 548},  {kBlockSize * 9, 548},  {kBlockSize * 10, 548},
		{kBlockSize * 11, 548},  {kBlockSize * 12, 548},  {kBlockSize * 13, 548},
		{kBlockSize * 13, 548},  {kBlockSize * 14, 548},  {kBlockSize * 15, 548},

		 {kBlockSize * 6, 596},   {kBlockSize * 7, 596},
		 {kBlockSize * 8, 596},   {kBlockSize * 9, 596},  {kBlockSize * 10, 596},
		{kBlockSize * 11, 596},  {kBlockSize * 12, 596},  {kBlockSize * 13, 596},
		{kBlockSize * 13, 596},  {kBlockSize * 14, 596},  {kBlockSize * 15, 596},
		
		{kBlockSize * 16, 644},  {kBlockSize * 17, 644},
		{kBlockSize * 18, 644},  {kBlockSize * 19, 644},  {kBlockSize * 20, 644},

		{kBlockSize * 13, 1172},  {kBlockSize * 14, 1172},  {kBlockSize * 15, 1172},
		

		 {kBlockSize * 5, 1316},   {kBlockSize * 6, 1316},   {kBlockSize * 7, 1316},
		{kBlockSize * 13, 1316},  {kBlockSize * 14, 1316},  {kBlockSize * 15, 1316},
		{kBlockSize * 16, 1316},  {kBlockSize * 17, 1316},  {kBlockSize * 18, 1316},
		{kBlockSize * 25, 1316},  {kBlockSize * 26, 1316},  {kBlockSize * 27, 1316},

		 {kBlockSize * 6, 1508},   {kBlockSize * 7, 1508},
		 {kBlockSize * 8, 1508},   {kBlockSize * 9, 1508},  {kBlockSize * 10, 1508},
		{kBlockSize * 11, 1508},  {kBlockSize * 12, 1508},  {kBlockSize * 13, 1508},
		{kBlockSize * 14, 1508},  {kBlockSize * 15, 1508},  {kBlockSize * 16, 1508},
		{kBlockSize * 17, 1508},  {kBlockSize * 18, 1508},  {kBlockSize * 19, 1508},
		{kBlockSize * 20, 1508},  {kBlockSize * 21, 1508},  {kBlockSize * 22, 1508},
		{kBlockSize * 23, 1508},  {kBlockSize * 24, 1508},  {kBlockSize * 25, 1508},
		{kBlockSize * 26, 1508},  

		 {kBlockSize * 4, 1556},  {kBlockSize * 5, 1556},   {kBlockSize * 6, 1556},   
		 {kBlockSize * 7, 1556},  {kBlockSize * 8, 1556},   {kBlockSize * 9, 1556},  
		{kBlockSize * 10, 1556}, {kBlockSize * 11, 1556},  {kBlockSize * 12, 1556},  
		{kBlockSize * 13, 1556}, {kBlockSize * 14, 1556},  {kBlockSize * 15, 1556}, 
		{kBlockSize * 16, 1556}, {kBlockSize * 17, 1556},  {kBlockSize * 18, 1556},  
		{kBlockSize * 19, 1556}, {kBlockSize * 20, 1556},  {kBlockSize * 21, 1556}, 
		{kBlockSize * 22, 1556}, {kBlockSize * 23, 1556},  {kBlockSize * 24, 1556},  
		{kBlockSize * 25, 1556}, {kBlockSize * 26, 1556},  {kBlockSize * 27, 1556}, 
		{kBlockSize * 28, 1556}, {kBlockSize * 29, 1556},

		 {kBlockSize * 4, 1652},  {kBlockSize * 5, 1652},   {kBlockSize * 6, 1652},
		 {kBlockSize * 7, 1652},  {kBlockSize * 8, 1652},   {kBlockSize * 9, 1652},
		{kBlockSize * 10, 1652}, {kBlockSize * 11, 1652},  {kBlockSize * 12, 1652},
		{kBlockSize * 13, 1652}, {kBlockSize * 14, 1652},  {kBlockSize * 15, 1652},
		{kBlockSize * 16, 1652}, {kBlockSize * 17, 1652},  {kBlockSize * 18, 1652},
		{kBlockSize * 19, 1652}, {kBlockSize * 20, 1652},  {kBlockSize * 21, 1652},
		{kBlockSize * 22, 1652}, {kBlockSize * 23, 1652},  {kBlockSize * 24, 1652},
		{kBlockSize * 25, 1652}, {kBlockSize * 26, 1652},  {kBlockSize * 27, 1652},
		{kBlockSize * 28, 1652}, {kBlockSize * 29, 1652}


	};

	bool isMoss[kBlockNum] =
	{
		0,1,0,1,1,0,0,0,1,0,1,1,1,0,0,1,0,1,1,1,0,0,0
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
		{kBlockSize * 16, 596}, {kBlockSize * 17, 596}, {kBlockSize * 18, 596},
		{kBlockSize * 19, 596}, {kBlockSize * 20, 596},

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

	static inline const uint8_t kSteelBlockNum = 12;
	std::vector<BlockSteel*>blocksSteel_;
	Vector2 steelBlockPos_[kSteelBlockNum] =
	{
		{kBlockSize * 4,  948},  {kBlockSize * 5,  948}, {kBlockSize * 6,  948},
		{kBlockSize * 7,  948},  {kBlockSize * 8,  948}, {kBlockSize * 9,  948},

		{kBlockSize * 21,  948},  {kBlockSize * 22,  948}, {kBlockSize * 23,  948},
		{kBlockSize * 24,  948},  {kBlockSize * 25,  948}, {kBlockSize * 26,  948},
	};
};
#pragma endregion


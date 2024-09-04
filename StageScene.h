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

class StageScene :public IScene
{
public:
	~StageScene();

	void Initialize() override;
	void Update() override;
	void ChangePhase();
	void Draw() override;

	void CheckAllCollision();

private:
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

	// Player
	Player* player_ = nullptr;
	uint32_t playerTexture = Novice::LoadTexture("./Resources/player.png");

	// Spike
	static inline const uint8_t kSpikeNum = 15;
	std::vector<Spike*>spike_;

	// Destroyable Block
	static inline const uint8_t kDestroyableBlockNum = 10;
	std::vector<BlockDestroyable*>destroyableBlocks_;
	Vector2Int desBlockPos_[kDestroyableBlockNum]
	{
		{0, 500}, {48, 500}, {96, 500},
		{144, 500}, {192, 500},
	};

	// Block
	static inline const uint8_t kBlockNum = 10;
	std::vector<BlockNotDestroyable*>blocks_;
	Vector2Int BlockPos_[kBlockNum]
	{
		{0, 300}, {48, 300}, {96, 300 },
		{144,300}, {192, 300}, {240, 300},
		{288, 300}
	};

	bool isMoss[kBlockNum] =
	{
		0,1,0,1,1,0,0,0,1,
	};

	static inline const uint8_t kWallBlockNum = 16;
	std::vector<BlockNotDestroyable*>leftWallBlocks_;
	std::vector<BlockNotDestroyable*>rightWallBlocks_;
};


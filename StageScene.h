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

class StageScene :public IScene
{
public:
	~StageScene();

	void Initialize() override;
	void Update() override;
	void ChangePhase();
	void Draw() override;
	void DeleteBlocks();
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

	// Spike
	static inline const uint8_t kSpikeNum = 15;
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

	// Block
	static inline const uint8_t kBlockNum = 30;
	std::vector<BlockNotDestroyable*>blocks_;
	Vector2 BlockPos_[kBlockNum]
	{
		{kBlockSize * 6,  300},  {kBlockSize * 7,  300},  {kBlockSize * 8,  300},
		{kBlockSize * 9,  350},  {kBlockSize * 10, 350},  {kBlockSize * 11, 350},

		{kBlockSize * 4,  500},  {kBlockSize * 5,  500},  {kBlockSize * 6,  500},
		{kBlockSize * 7,  500},  {kBlockSize * 8,  500},  {kBlockSize * 9,  500},
		{kBlockSize * 10, 500},  {kBlockSize * 11, 500},  {kBlockSize * 12, 500},
		{kBlockSize * 13, 500},  {kBlockSize * 14, 500},  {kBlockSize * 15, 500},

		{kBlockSize * 15, 700},  {kBlockSize * 16, 700},  {kBlockSize * 17, 700},
		{kBlockSize * 18, 700},  {kBlockSize * 19, 700},  {kBlockSize * 20, 700},

		{kBlockSize * 14, 900},  {kBlockSize * 15, 900},  {kBlockSize * 16, 900},
		{kBlockSize * 17, 900},  {kBlockSize * 18, 900},  {kBlockSize * 19, 900},
	};

	bool isMoss[kBlockNum] =
	{
		0,1,0,1,1,0,0,0,1,0,
	};

	static inline const uint8_t kWallBlockNum = 22;
	std::vector<BlockNotDestroyable*>leftWallBlocks_;
	Vector2 leftWallPos_ = { 144.f,0 };
	std::vector<BlockNotDestroyable*>rightWallBlocks_;
	Vector2 rightWallPos_ = { 1392.f,0 };

	//UI Handles
	int stageTextHandle = Novice::LoadTexture("./Resources/StageText/STAGE.png");
	int stage1Handle = Novice::LoadTexture("./Resources/StageText/1.png");
	int controlsHandle = Novice::LoadTexture("./Resources/StageText/CONTROLS.png");
	int letterDHandle = Novice::LoadTexture("./Resources/StageText/D.png");
	int letterAHandle = Novice::LoadTexture("./Resources/StageText/A.png");
	int rightPlayer = Novice::LoadTexture("./Resources/Player/digPlayer(R).gif");
	int leftPlayer = Novice::LoadTexture("./Resources/Player/digPlayer(L).gif");
	int spaceHandle = Novice::LoadTexture("./Resources/StageText/SPACE.png");

	//Background
	Background* background_ = nullptr;

};

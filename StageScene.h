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
	Vector2 desBlockPos_[kDestroyableBlockNum]
	{
		/*{0, 300}, {48, 300},*/ {96, 300},
		{144, 300}, {192, 300},{672, 300},
		{1056, 300}
	};

	// Block
	static inline const uint8_t kBlockNum = 28;
	std::vector<BlockNotDestroyable*>blocks_;
	Vector2 BlockPos_[kBlockNum]
	{
		/*{0, 300}, */ {48, 500},   {96, 500},
		  {144,500},  {192, 500},  {240, 500},
		 {288, 500},   {336,500},  {384, 500},
		 {432, 500},  {480, 500},  {528, 500},
		 {576, 500},  {624, 500},  {672, 500},
		 {720, 500},  {768, 500},  {816, 500},
		 {864, 500},  {912, 500},  {960, 700},
		{1008, 700}, {1056, 700}, {1104, 700},
		{1152, 700}, {1200, 700}, {912, 900},
		{864, 900} ,{816, 900},

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


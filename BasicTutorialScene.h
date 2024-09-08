#pragma once
#include "IScene.h"
#include "Input.h"
#include "Novice.h"
#include "Player.h"
#include "Fade.h"
#include "BlockDestroyable.h"
#include "BlockNotDestroyable.h"
#include "Backgroud.h"
#include "UserInterface.h"
#include "Spike.h"
#include <vector>

class BasicTutorialScene : public IScene
{
public:
	~BasicTutorialScene();

	void Initialize() override;
	void Update() override;
	void Draw() override;

	void DeleteBlocks();

	void CheckAllCollision();
	void ChangePhase();

private:
	enum class Phase
	{
		kFadeIn,
		kPlay,
		kDeath,
		kStageClear,
		kFadeOut,
	};
	Phase phase_;

	// Fade
	Fade* fade_ = nullptr;
	float duration_ = 1.0f;
	// Background
	Background* background_ = nullptr;
	int backgroundHandle_[MAXBACKGROUNDS] =
	{
		{Novice::LoadTexture("./Resources/Background/Bg1.png")},
		{Novice::LoadTexture("./Resources/Background/Bg2.png")},
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
	// Normal Block
	static inline const uint8_t kBlockNum = 45;
	std::vector<BlockNotDestroyable*>blocks_;
	std::vector<Vector2>blockPos_ = 
	{
		{kBlockSize *4, 500.f}, {kBlockSize * 5, 500.f},{kBlockSize * 6, 500.f},
		{kBlockSize *7, 500.f}, {kBlockSize * 8, 500.f},{kBlockSize * 9, 500.f},
		{kBlockSize * 10, 500.f}, {kBlockSize * 11, 500.f},{kBlockSize * 12, 500.f},
		{kBlockSize * 13, 500.f}, {kBlockSize * 14, 500.f},{kBlockSize * 15, 500.f},
		{kBlockSize * 16, 500.f}, {kBlockSize * 17, 500.f},{kBlockSize * 18, 500.f},
		{kBlockSize * 19, 500.f}, {kBlockSize * 20, 500.f},{kBlockSize * 21, 500.f},
		{kBlockSize * 22, 500.f}, {kBlockSize * 23, 500.f},{kBlockSize * 24, 500.f},
		{kBlockSize * 25, 500.f}, {kBlockSize * 26, 500.f},{kBlockSize * 27, 500.f},
		{kBlockSize * 28, 500.f},

		{kBlockSize * 14, 700.f}, {kBlockSize * 15, 700.f},{kBlockSize * 16, 700.f},
		{kBlockSize * 17, 700.f}, {kBlockSize * 18, 700.f},

		{kBlockSize * 21, 1000.f}, {kBlockSize * 22, 1000.f},{kBlockSize * 23, 1000.f},
		{kBlockSize * 24, 1000.f}, {kBlockSize * 25, 1000.f},

		{kBlockSize * 7, 1300.f}, {kBlockSize * 8, 1300.f},{kBlockSize * 9, 1300.f},
		{kBlockSize * 10, 1300.f}, {kBlockSize * 11, 1300.f},

		{kBlockSize * 12, 1600.f}, {kBlockSize * 13, 1600.f},{kBlockSize * 14, 1600.f},
		{kBlockSize * 15, 1600.f}, {kBlockSize * 16, 1600.f},
	};

	




	// Wall
	static inline const uint8_t kWallBlockNum = 22;
	std::vector<BlockNotDestroyable*>leftWallBlocks_;
	Vector2 leftWallPos_ = { 144.f,0 };
	std::vector<BlockNotDestroyable*>rightWallBlocks_;
	Vector2 rightWallPos_ = { 1392.f,0 };
};


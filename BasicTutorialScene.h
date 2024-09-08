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
		{kBlockSize * 4,  300.f}, {kBlockSize * 5,  300.f},{kBlockSize * 6,  300.f},
		{kBlockSize * 7,  300.f}, {kBlockSize * 8,  300.f},{kBlockSize * 9,  300.f},
		{kBlockSize * 10, 300.f}, {kBlockSize * 11, 300.f},{kBlockSize * 12, 300.f},
		{kBlockSize * 13, 300.f}, {kBlockSize * 14, 300.f},{kBlockSize * 15, 300.f},
		{kBlockSize * 16, 300.f}, {kBlockSize * 17, 300.f},{kBlockSize * 18, 300.f},
		{kBlockSize * 19, 300.f}, {kBlockSize * 20, 300.f},{kBlockSize * 21, 300.f},
		{kBlockSize * 22, 300.f}, {kBlockSize * 23, 300.f},{kBlockSize * 24, 300.f},
		{kBlockSize * 25, 300.f}, {kBlockSize * 26, 300.f},{kBlockSize * 27, 300.f},
		{kBlockSize * 28, 300.f},

		{kBlockSize * 14, 500.f}, {kBlockSize * 15, 500.f},{kBlockSize * 16, 500.f},
		{kBlockSize * 17, 500.f}, {kBlockSize * 18, 500.f},

		{kBlockSize * 21, 600.f}, {kBlockSize * 22, 600.f},{kBlockSize * 23, 600.f},
		{kBlockSize * 24, 600.f}, {kBlockSize * 25, 600.f},

		{kBlockSize * 7,  800.f}, {kBlockSize * 8,  800.f},{kBlockSize * 9, 800.f},
		{kBlockSize * 10, 800.f}, {kBlockSize * 11, 800.f},

		{kBlockSize * 16, 900.f}, {kBlockSize * 17, 900.f},{kBlockSize * 18, 900.f},
		{kBlockSize * 19, 900.f}, {kBlockSize * 20, 900.f},
	};






	// Wall
	static inline const uint8_t kWallBlockNum = 22;
	std::vector<BlockNotDestroyable*>leftWallBlocks_;
	Vector2 leftWallPos_ = { 144.f,0 };
	std::vector<BlockNotDestroyable*>rightWallBlocks_;
	Vector2 rightWallPos_ = { 1392.f,0 };
};


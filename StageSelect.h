#pragma once
#include "Novice.h"
#include "IScene.h"
#include "Backgroud.h"
#include "Fade.h"
#include "Player.h"
#include "BlockNotDestroyable.h"
#include "UserInterface.h"
#include <vector>

class StageSelect :public IScene
{
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;

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
		kFadeOut,
	};
	Phase phase_;

	// Fade
	Fade* fade_ = nullptr;
	float duration_ = 1.0f;

	//Background
	Background* background_ = nullptr;
	int backgroundHandle_[MAXBACKGROUNDS] =
	{
		{Novice::LoadTexture("./Resources/Background/TwoBg.png")},
		{Novice::LoadTexture("./Resources/Background/TwoBg.png")},
	};
	// UI
	UserInterface* UI = nullptr;

	// Player
	Player* player_ = nullptr;

	// Block Size
	static inline const float kBlockSize = 48.f;
#pragma region Normal Block
	// Normal Block
	static inline const uint8_t kBlockNum = 27;
	std::vector<BlockNotDestroyable*>blocks_;
#pragma endregion
	// Wall
	static inline const uint8_t kWallBlockNum = 22;
	std::vector<BlockNotDestroyable*>leftWallBlocks_;
	Vector2 leftWallPos_ = { 144.f,0.f };
	std::vector<BlockNotDestroyable*>rightWallBlocks_;
	Vector2 rightWallPos_ = { 1392.f,0.f };
};


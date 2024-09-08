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

	Background* background_ = nullptr;

	// UI
	UserInterface* UI = nullptr;

	// Player
	Player* player_ = nullptr;

	// Block Size
	static inline const float kBlockSize = 48.f;
	// Normal Block
	static inline const uint8_t kBlockNum = 15;
	std::vector<BlockNotDestroyable*>blocks_;
	std::vector<Vector2>blockPos_;
	// Destroyable Block
	static inline const uint8_t kDestroyableBlockNum = 4;
	std::vector<BlockDestroyable*>destroyableBlocks_;
	std::vector<Vector2> desBlockPos_;
	/*{
		{144, 300}, {192, 300},{672, 300},
		{1056, 300}
	};*/
	// Wall
	static inline const uint8_t kWallBlockNum = 22;
	std::vector<BlockNotDestroyable*>leftWallBlocks_;
	Vector2 leftWallPos_ = { 144.f,0 };
	std::vector<BlockNotDestroyable*>rightWallBlocks_;
	Vector2 rightWallPos_ = { 1392.f,0 };
};


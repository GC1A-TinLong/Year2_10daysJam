#pragma once
#include "Novice.h"
#include "IScene.h"
#include "Backgroud.h"
#include "Fade.h"
#include "Player.h"
#include "BlockNotDestroyable.h"
#include "BlockSteel.h"
#include "UserInterface.h"
#include "Input.h"
#include <vector>

class StageSelect :public IScene
{
public:
	~StageSelect();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void ChangePhase();

	void DeleteBlocks();
	void CheckAllCollision();
	void SetPlayerStatus();
private:
	// Scroll
	float scrollSpeed = 0.f;

	enum class Phase
	{
		kFadeIn,
		kPlay,
		kFadeOut,
	};
	Phase phase_;

	//Background
	Background* background_ = nullptr;
	int backgroundHandle_[MAXBACKGROUNDS] =
	{
		{Novice::LoadTexture("./Resources/Background/TwoBg.png")},
		{Novice::LoadTexture("./Resources/Background/TwoBg.png")},
	};
	// UI
	UserInterface* UI = nullptr;

	// Fade
	Fade* fade_ = nullptr;
	float duration_ = 1.0f;

	// Player
	Player* player_ = nullptr;


	enum class BlockType
	{
		None,
		Block,
		SteelBlock,
		BrokenBlock,
	};
	static inline const uint8_t mapCountX = 25;
	static inline const uint8_t mapCountY = 20;
	int map[mapCountY][mapCountX] =
	{
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
		0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
		1,1,2,2,1,1,1,1,1,2,2,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
		3,3,3,3,3,3,1,3,3,3,3,3,3,1,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
		1,1,2,2,1,1,1,1,1,2,2,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	};
	//Mapchip
	static inline const uint8_t adjustPosForMapchipX = 192;
	static inline const uint8_t adjustPosForMapchipY = 96;
	static inline const float kSpriteSize = 48.f;
	// Block Size
	static inline const float kBlockSize = 48.f;
	// Normal Block
	static inline const uint8_t kBlockNum = 46;
	static inline const uint8_t kRowBlockNum = 25;
	std::vector<BlockNotDestroyable*>blocks_;
	uint8_t blockIndex = 0;
	// Steel Block
	static inline const uint8_t kSteelBlockNum = 58;
	std::vector<BlockSteel*>steelBlocks_;
	uint8_t steelIndex = 0;
	// Wall
	static inline const uint8_t kWallBlockNum = 22;
	std::vector<BlockSteel*>leftWallBlocks_;
	Vector2 leftWallPos_ = { 144.f,0.f };
	std::vector<BlockSteel*>rightWallBlocks_;
	Vector2 rightWallPos_ = { 1392.f,0.f };
};

